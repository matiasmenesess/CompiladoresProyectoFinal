


#include <stdexcept>
#include "visitor.h"
#include <iostream>
#include "expression.h"
#include <unordered_map>
#include <algorithm>
#include <iterator>
using namespace std;


int GenCodeVisitor::calcular_stack_body(Body* body) {
    int stack = 0;
    for (auto elem : body->elements) {
        // Variables locales
        if (auto vardec = dynamic_cast<VarDec*>(elem)) {
            for (size_t i = 0; i < vardec->vars.size(); ++i) {
                int var_size = 8;  // Por defecto 64 bits
                std::string tname = vardec->types[i]->type_name;
                
                // Tamaños específicos para 64 bits
                if (vardec->types[i]->is_pointer) {
                    var_size = 8;  // Todos los punteros en 64 bits = 8 bytes
                }
                else if (tname == "char" || tname == "bool")
                    var_size = 1;
                else if (tname == "int")
                    var_size = 8;  // int en 64 bits = 8 bytes
                else if (tname.find("struct") == 0) {
                    std::string struct_name = tname.substr(7);
                    var_size = env->get_struct_size(struct_name);
                }
                
                // Asegurar alineación a 8 bytes para 64 bits
                if (var_size < 8) var_size = 8;
                stack += var_size;
            }
        }
        // ForStatement
        else if (auto forstm = dynamic_cast<ForStatement*>(elem)) {
            // Suma el stack de la inicialización del for (si es VarDec)
            if (forstm->init) {
                if (auto vardec = dynamic_cast<VarDec*>(forstm->init)) {
                    for (size_t i = 0; i < vardec->vars.size(); ++i) {
                        int var_size = 8;  // Por defecto 64 bits
                        std::string tname = vardec->types[i]->type_name;
                        
                        if (vardec->types[i]->is_pointer) {
                            var_size = 8;  // Punteros = 8 bytes en 64 bits
                        }
                        else if (tname == "char" || tname == "bool")
                            var_size = 1;
                        else if (tname == "int")
                            var_size = 8;  // int en 64 bits = 8 bytes
                        else if (tname.find("struct") == 0) {
                            std::string struct_name = tname.substr(7);
                            var_size = env->get_struct_size(struct_name);
                        }
                        
                        // Alineación a 8 bytes
                        if (var_size < 8) var_size = 8;
                        stack += var_size;
                    }
                }
            }
            // Suma el stack de todo el cuerpo del for
            if (forstm->b)
                stack += calcular_stack_body(forstm->b);
        }
        // IfStatement
        else if (auto ifstm = dynamic_cast<IfStatement*>(elem)) {
            if (ifstm->statements)
                stack += calcular_stack_body(ifstm->statements);
            if (ifstm->elsChain) {
                // Puede ser ElseIfStatement o IfStatement
                if (auto elseif = dynamic_cast<ElseIfStatement*>(ifstm->elsChain)) {
                    if (elseif->body)
                        stack += calcular_stack_body(elseif->body);
                    if (elseif->nextChain) {
                        // Recursivo para else-if en cadena
                        if (auto nextElseIf = dynamic_cast<ElseIfStatement*>(elseif->nextChain)) {
                            if (nextElseIf->body)
                                stack += calcular_stack_body(nextElseIf->body);
                        }
                    }
                }
            }
        }
        // WhileStatement
        else if (auto whilestm = dynamic_cast<WhileStatement*>(elem)) {
            if (whilestm->b)
                stack += calcular_stack_body(whilestm->b);
        }
        // Bloques anidados
        else if (auto body2 = dynamic_cast<Body*>(elem)) {
            stack += calcular_stack_body(body2);
        }
    }
    return stack;
}

void GenCodeVisitor::gencode(Program* program) {
    out << ".data" << endl;
    out << "print_fmt: .string \"%ld\\n\"" << endl;
    
    if(program->struct_declarations){
        program->struct_declarations->accept(this);
    }
    
    // Generar variables globales
    if (program->global_declarations) {
        for (auto dec : program->global_declarations->global_vardecs) {
            out << dec->var_name << ": .quad 0" << endl;
        }
    }
    
    out << ".text" << endl;
    out << ".globl main" << endl;
    
    // Generar funciones primero
    if (program->functions) {
        program->functions->accept(this);
    }
    
    // Generar main
    out << "main:" << endl;
    out << " pushq %rbp" << endl;
    out << " movq %rsp, %rbp" << endl;
    
    // CORREGIDO: Calcular espacio completo usando la función que ya tienes
    int stack_space = 0;
    if (program->main_function && program->main_function->body) {
        stack_space = calcular_stack_body(program->main_function->body);
    }
    
    // Alineación a 16 bytes (requerida por ABI x86-64)
    if (stack_space % 16 != 0) {
        stack_space = ((stack_space + 15) / 16) * 16;
    }
    
    if (stack_space > 0) {
        out << " subq $" << stack_space << ", %rsp" << endl;
    }
    
    // Inicialización de variables globales
    if (program->global_declarations) {
    for (auto dec : program->global_declarations->global_vardecs) {
        if (dec->type->is_array) {
            // Para arrays globales
            int array_size = 64; // valor por defecto
            if (dec->type->array_size) {
                // Evaluar el tamaño si es una expresión
                array_size = dec->type->array_size->accept(this);
            }
            out << dec->var_name << ": .space " << array_size << endl;
        } else {
            // Variables globales normales
            out << dec->var_name << ": .quad 0" << endl;
        }
    }
}
    
    env->add_level();
    if (program->main_function) {
        program->main_function->accept(this);
    }
    env->remove_level();
    
    out << ".section .note.GNU-stack,\"\",@progbits" << endl;
}


int GenCodeVisitor::visit(NumberExp* exp) {
    // NumberExp es int, usar movq para 64 bits
    out << " movq $" << exp->value << ", %rax" << endl;
    return exp->value;
}

int GenCodeVisitor::visit(CharExp* exp) {
    // Usar movq para todo, mantener consistencia
    out << " movq $" << (int)exp->value << ", %rax" << endl;
    return (int)exp->value;
}

int GenCodeVisitor::visit(BoolExp* exp) {
    // Usar movq para todo, mantener consistencia
    int bool_val = exp->value ? 1 : 0;
    out << " movq $" << bool_val << ", %rax" << endl;
    return bool_val;
}

int GenCodeVisitor::visit(StringExp* exp) {
    string label = "string_" + to_string(cantidad++);
    
    // Cambiar a sección de datos de solo lectura
    out << ".section .rodata" << endl;
    out << label << ": .string " << exp->value << endl;
    
    // Regresar a sección de texto
    out << ".text" << endl;
    
    // Cargar dirección del string en %rax
    out << " leaq " << label << "(%rip), %rax" << endl;
    
    return 0; // Los strings no tienen valor numérico directo
}

int GenCodeVisitor::visit(IdentifierExp* exp) {
    // CORREGIDO: Verificar existencia ANTES del lookup
    if (env->check(exp->name) == false) {
        cout << "Variable no declarada: " << exp->name << endl;
        exit(0);
    }
    
    // Ahora hacer lookup de manera segura
    VarInfo info = env->lookup(exp->name);
    
    const char* regs[] = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"};
    out << "# Cargando valor de " << exp->name << " " << info.is_reference << " " << info.reg_index << endl;
    
    if (info.is_reference && info.reg_index >= 0) {
        out << " movq (" << regs[info.reg_index] << "), %rax # Valor de* " << exp->name << endl;
    } else if (info.reg_index >= 0) {
        out << " movq " << regs[info.reg_index] << ", %rax # Valor de " << exp->name << endl;
    } else if (!info.is_global) {
        out << " movq " << info.offset << "(%rbp), %rax # " << exp->name << endl;
    } else {
        out << " movq " << exp->name << "(%rip), %rax # " << exp->name << endl;
    }
    
    return 0;
}

void GenCodeVisitor::get_member_address(MemberAccessExp* exp) {
    // Detectar si es acceso local (ej: p.nombre)
    int base_offset = 0;
    std::string struct_type;
    bool is_local_struct = false;
    
    if (auto id = dynamic_cast<IdentifierExp*>(exp->object)) {
        struct_type = env->lookup_type(id->name);
        if (struct_type.rfind("struct ", 0) == 0) {
            struct_type = struct_type.substr(7);
        }
        VarInfo info = env->lookup(id->name);
        base_offset = info.offset;
        is_local_struct = !info.is_global;
    }
    
    int member_offset = 0;
    if (env->has_struct(struct_type)) {
        member_offset = env->get_struct_member_offset(struct_type, exp->member_name);
    } else {
        member_offset = 8;
    }
    
    if (exp->is_pointer) {
        // p->campo: obtener dirección del campo
        exp->object->accept(this); // obtiene puntero en %rax
        out << " addq $" << member_offset << ", %rax # dirección de " << exp->member_name << endl;
    } else if (is_local_struct) {
        // p.campo: calcular dirección en el stack
        out << " leaq " << (base_offset + member_offset) << "(%rbp), %rax # dirección de " << exp->member_name << " en struct local" << endl;
    } else {
        // Caso general: obtener dirección del campo
        exp->object->accept(this);
        out << " addq $" << member_offset << ", %rax # dirección de " << exp->member_name << endl;
    }
}

int GenCodeVisitor::visit(AssignExp* exp) {
    if (exp->assign_op == ASSIGN_OP) {
        exp->right->accept(this);
        out << " pushq %rax" << endl;
        
        if (auto id = dynamic_cast<IdentifierExp*>(exp->left)) {
            // AGREGADO: Verificar existencia de variable
            if (env->check(id->name) == false) {
                cout << "Variable no declarada: " << id->name << endl;
                exit(0);
            }
            
            VarInfo info = env->lookup(id->name);
            out << " popq %rax" << endl;
            const char* regs[] = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"};
            
            // --- GUARDAR EL RESULTADO ---
            // CORREGIDO: Verificar rango de reg_index
            if (info.is_reference && info.reg_index >= 0 && info.reg_index < 6) {
                out << " movq %rax, (" << regs[info.reg_index] << ") # guardar en *" << id->name << endl;
            } else if (info.reg_index >= 0 && info.reg_index < 6) {
                out << " movq %rax, " << regs[info.reg_index] << " # guardar en parámetro " << id->name << endl;
            } else if (!info.is_global) {
                out << " movq %rax, " << info.offset << "(%rbp) # guardar en local " << id->name << endl;
            } else {
                out << " movq %rax, " << id->name << "(%rip) # guardar en global " << id->name << endl;
            }
        } else if (auto unary = dynamic_cast<UnaryExp*>(exp->left)) {
            // Manejar *ptr = valor
            if (unary->op == DEREFERENCE_OP) {
                unary->uexp->accept(this); // obtiene dirección del puntero en %rax
                out << " movq %rax, %rbx # guardar dirección" << endl;
                out << " popq %rax # recuperar valor a asignar" << endl;
                out << " movq %rax, (%rbx) # *ptr = valor" << endl;
            } else {
                cerr << "Error: Operador unario no soportado en asignación" << endl;
                exit(1);
            }
        } else if (auto member = dynamic_cast<MemberAccessExp*>(exp->left)) {
            // Manejar obj.field = valor o obj->field = valor
            out << " popq %rax # recuperar valor a asignar" << endl;
            out << " pushq %rax # guardar valor temporalmente" << endl;
            
            // Obtener dirección donde escribir
            get_member_address(member); // dirección en %rax
            out << " movq %rax, %rbx # guardar dirección" << endl;
            out << " popq %rax # recuperar valor" << endl;
            out << " movq %rax, (%rbx) # escribir valor en member" << endl;
        } else if (auto array = dynamic_cast<ArrayAccessExp*>(exp->left)) {
            // Manejar arr[index] = valor
            array->array->accept(this); // obtiene dirección del array en %rax
            out << " pushq %rax # guardar dirección array" << endl;
            array->index->accept(this); // obtiene índice en %rax
            out << " imulq $8, %rax # multiplicar por tamaño del elemento" << endl;
            out << " popq %rbx # recuperar dirección array" << endl;
            out << " addq %rbx, %rax # calcular dirección final" << endl;
            out << " movq %rax, %rbx # guardar dirección final" << endl;
            out << " popq %rax # recuperar valor a asignar" << endl;
            out << " movq %rax, (%rbx) # arr[index] = valor" << endl;
        } else {
            cerr << "Error: Tipo de expresión no soportado en asignación" << endl;
            exit(1);
        }
    } 
    else if (exp->assign_op == PLUS_EQUAL_OP ||
             exp->assign_op == MINUS_EQUAL_OP ||
             exp->assign_op == MULTIPLY_EQUAL_OP ||
             exp->assign_op == DIVIDE_EQUAL_OP ||
             exp->assign_op == MODULO_EQUAL_OP) {
        
        if (auto id = dynamic_cast<IdentifierExp*>(exp->left)) {
            // AGREGADO: Verificar existencia de variable
            if (env->check(id->name) == false) {
                cout << "Variable no declarada: " << id->name << endl;
                exit(0);
            }
            
            VarInfo info = env->lookup(id->name);
            
            // CORREGIDO: Evaluar right side y guardar en %rbx en lugar de %rcx
            exp->right->accept(this);
            out << " movq %rax, %rbx # guardar operando derecho" << endl;
            
            const char* regs[] = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"};
            
            // --- CARGAR EL VALOR DE LA IZQUIERDA ---
            // CORREGIDO: Verificar rango de reg_index
            if (info.is_reference && info.reg_index >= 0 && info.reg_index < 6) {
                out << " movq (" << regs[info.reg_index] << "), %rax # cargar *" << id->name << endl;
            } else if (info.reg_index >= 0 && info.reg_index < 6) {
                out << " movq " << regs[info.reg_index] << ", %rax # cargar parámetro " << id->name << endl;
            } else if (!info.is_global) {
                out << " movq " << info.offset << "(%rbp), %rax # cargar local " << id->name << endl;
            } else {
                out << " movq " << id->name << "(%rip), %rax # cargar global " << id->name << endl;
            }
            
            // --- OPERACIÓN ---
            switch (exp->assign_op) {
                case PLUS_EQUAL_OP:
                    out << " addq %rbx, %rax" << endl;
                    break;
                case MINUS_EQUAL_OP:
                    out << " subq %rbx, %rax" << endl;
                    break;
                case MULTIPLY_EQUAL_OP:
                    out << " imulq %rbx, %rax" << endl;
                    break;
                case DIVIDE_EQUAL_OP:
                    out << " cqo" << endl;
                    out << " idivq %rbx" << endl;
                    break;
                case MODULO_EQUAL_OP:
                    out << " cqo" << endl;
                    out << " idivq %rbx" << endl;
                    out << " movq %rdx, %rax" << endl;
                    break;
                default:
                    break;
            }
            
            // --- GUARDAR EL RESULTADO ---
            // CORREGIDO: Verificar rango de reg_index
            if (info.is_reference && info.reg_index >= 0 && info.reg_index < 6) {
                out << " movq %rax, (" << regs[info.reg_index] << ") # guardar en *" << id->name << endl;
            } else if (info.reg_index >= 0 && info.reg_index < 6) {
                out << " movq %rax, " << regs[info.reg_index] << " # guardar en parámetro " << id->name << endl;
            } else if (!info.is_global) {
                out << " movq %rax, " << info.offset << "(%rbp) # guardar en local " << id->name << endl;
            } else {
                out << " movq %rax, " << id->name << "(%rip) # guardar en global " << id->name << endl;
            }
        } else if (auto unary = dynamic_cast<UnaryExp*>(exp->left)) {
            // Manejar *ptr += valor (y otros operadores compuestos)
            if (unary->op == DEREFERENCE_OP) {
                // Evaluar right side y guardarlo
                exp->right->accept(this);
                out << " movq %rax, %rbx # guardar operando derecho" << endl;
                
                // Obtener dirección del puntero
                unary->uexp->accept(this);
                out << " movq %rax, %rcx # guardar dirección del puntero" << endl;
                
                // Cargar valor actual
                out << " movq (%rcx), %rax # cargar *ptr" << endl;
                
                // Realizar operación
                switch (exp->assign_op) {
                    case PLUS_EQUAL_OP:
                        out << " addq %rbx, %rax" << endl;
                        break;
                    case MINUS_EQUAL_OP:
                        out << " subq %rbx, %rax" << endl;
                        break;
                    case MULTIPLY_EQUAL_OP:
                        out << " imulq %rbx, %rax" << endl;
                        break;
                    case DIVIDE_EQUAL_OP:
                        out << " cqo" << endl;
                        out << " idivq %rbx" << endl;
                        break;
                    case MODULO_EQUAL_OP:
                        out << " cqo" << endl;
                        out << " idivq %rbx" << endl;
                        out << " movq %rdx, %rax" << endl;
                        break;
                    default:
                        break;
                }
                
                // Guardar resultado
                out << " movq %rax, (%rcx) # guardar resultado en *ptr" << endl;
            } else {
                cerr << "Error: Operador unario no soportado en asignación compuesta" << endl;
                exit(1);
            }
        } else if (auto member = dynamic_cast<MemberAccessExp*>(exp->left)) {
            // Manejar obj.field += valor o obj->field += valor
            // Evaluar right side y guardarlo
            exp->right->accept(this);
            out << " pushq %rax # guardar operando derecho" << endl;
            
            // Obtener dirección del member
            get_member_address(member); // dirección en %rax
            out << " pushq %rax # guardar dirección del member" << endl;
            
            // Cargar valor actual del member
            out << " movq (%rax), %rax # cargar valor actual del member" << endl;
            
            // Recuperar operando derecho
            out << " popq %rcx # recuperar dirección" << endl;
            out << " popq %rbx # recuperar operando derecho" << endl;
            
            // Realizar operación
            switch (exp->assign_op) {
                case PLUS_EQUAL_OP:
                    out << " addq %rbx, %rax" << endl;
                    break;
                case MINUS_EQUAL_OP:
                    out << " subq %rbx, %rax" << endl;
                    break;
                case MULTIPLY_EQUAL_OP:
                    out << " imulq %rbx, %rax" << endl;
                    break;
                case DIVIDE_EQUAL_OP:
                    out << " cqo" << endl;
                    out << " idivq %rbx" << endl;
                    break;
                case MODULO_EQUAL_OP:
                    out << " cqo" << endl;
                    out << " idivq %rbx" << endl;
                    out << " movq %rdx, %rax" << endl;
                    break;
                default:
                    break;
            }
            
            // Guardar resultado
            out << " movq %rax, (%rcx) # guardar resultado en member" << endl;
            
        } else if (auto array = dynamic_cast<ArrayAccessExp*>(exp->left)) {
            // Manejar arr[index] += valor
            // Evaluar right side y guardarlo
            exp->right->accept(this);
            out << " movq %rax, %rbx # guardar operando derecho" << endl;
            
            // Calcular dirección del elemento
            array->array->accept(this);
            out << " pushq %rax # guardar dirección array" << endl;
            array->index->accept(this);
            out << " imulq $8, %rax # multiplicar por tamaño del elemento" << endl;
            out << " popq %rcx # recuperar dirección array" << endl;
            out << " addq %rcx, %rax # calcular dirección final" << endl;
            out << " movq %rax, %rcx # guardar dirección final" << endl;
            
            // Cargar valor actual
            out << " movq (%rcx), %rax # cargar arr[index]" << endl;
            
            // Realizar operación
            switch (exp->assign_op) {
                case PLUS_EQUAL_OP:
                    out << " addq %rbx, %rax" << endl;
                    break;
                case MINUS_EQUAL_OP:
                    out << " subq %rbx, %rax" << endl;
                    break;
                case MULTIPLY_EQUAL_OP:
                    out << " imulq %rbx, %rax" << endl;
                    break;
                case DIVIDE_EQUAL_OP:
                    out << " cqo" << endl;
                    out << " idivq %rbx" << endl;
                    break;
                case MODULO_EQUAL_OP:
                    out << " cqo" << endl;
                    out << " idivq %rbx" << endl;
                    out << " movq %rdx, %rax" << endl;
                    break;
                default:
                    break;
            }
            
            // Guardar resultado
            out << " movq %rax, (%rcx) # guardar resultado en arr[index]" << endl;
        } else {
            cerr << "Error: Asignación compuesta solo soportada para identificadores, punteros, miembros y arrays" << endl;
            exit(1);
        }
    }
    return 0;
}


int GenCodeVisitor::visit(UnaryExp* exp) {
    exp->uexp->accept(this);

    switch (exp->op) {
        case NEGACION_OP:
            out << "    testq %rax, %rax" << endl;
            out << "    movq $0, %rcx" << endl;
            out << "    sete %cl" << endl;
            out << "    movzbq %cl, %rax" << endl;  // CORREGIDO: zero-extend a 64 bits
            break;
        case UNARY_MINUS_OP:
            out << "    negq %rax" << endl;
            break;
        case UNARY_PLUS_OP:
            break;
        
        case PLUS_PLUS_OP: {
            if (auto id = dynamic_cast<IdentifierExp*>(exp->uexp)) {
                // AGREGADO: Verificar existencia
                if (!env->check(id->name)) {
                    cerr << "Error: Variable no declarada: " << id->name << endl;
                    exit(1);
                }
                
                VarInfo info = env->lookup(id->name);
                const char* regs[] = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"};

                // CORREGIDO: Verificar bounds del array
                if (info.is_reference && info.reg_index >= 0 && info.reg_index < 6) {
                    if (exp->is_prefix) {
                        out << "    incq %rax" << endl;
                        out << "    movq %rax, (" << regs[info.reg_index] << ")  # ++*ref" << endl;
                    } else {
                        out << "    movq %rax, %rcx" << endl;
                        out << "    incq %rcx" << endl;
                        out << "    movq %rcx, (" << regs[info.reg_index] << ")  # *ref++" << endl;
                    }
                } else if (info.reg_index >= 0 && info.reg_index < 6) {
                    if (exp->is_prefix) {
                        out << "    incq %rax" << endl;
                        out << "    movq %rax, " << regs[info.reg_index] << "  # ++param" << endl;
                    } else {
                        out << "    movq %rax, %rcx" << endl;
                        out << "    incq %rcx" << endl;
                        out << "    movq %rcx, " << regs[info.reg_index] << "  # param++" << endl;
                    }
                } else if (!info.is_global) {
                    int offset = info.offset;
                    if (exp->is_prefix) {
                        out << "    incq %rax" << endl;
                        out << "    movq %rax, " << offset << "(%rbp)" << endl;
                    } else {
                        out << "    movq %rax, %rcx" << endl;
                        out << "    incq %rcx" << endl;
                        out << "    movq %rcx, " << offset << "(%rbp)" << endl;
                    }
                } else {
                    // global
                    if (exp->is_prefix) {
                        out << "    incq %rax" << endl;
                        out << "    movq %rax, " << id->name << "(%rip)" << endl;
                    } else {
                        out << "    movq %rax, %rcx" << endl;
                        out << "    incq %rcx" << endl;
                        out << "    movq %rcx, " << id->name << "(%rip)" << endl;
                    }
                }
            } else if (auto member = dynamic_cast<MemberAccessExp*>(exp->uexp)) {
                // AGREGADO: Soporte para ++obj->field y ++obj.field
                get_member_address(member); // dirección en %rax
                out << "    movq %rax, %rbx # guardar dirección" << endl;
                out << "    movq (%rbx), %rax # cargar valor actual" << endl;
                
                if (exp->is_prefix) {
                    out << "    incq %rax" << endl;
                    out << "    movq %rax, (%rbx) # ++member" << endl;
                } else {
                    out << "    movq %rax, %rcx # guardar valor original" << endl;
                    out << "    incq %rax" << endl;
                    out << "    movq %rax, (%rbx) # member++" << endl;
                    out << "    movq %rcx, %rax # retornar valor original" << endl;
                }
            } else if (auto unary = dynamic_cast<UnaryExp*>(exp->uexp)) {
                // AGREGADO: Soporte para ++(*ptr)
                if (unary->op == DEREFERENCE_OP) {
                    unary->uexp->accept(this); // obtiene dirección del puntero
                    out << "    movq %rax, %rbx # guardar dirección" << endl;
                    out << "    movq (%rbx), %rax # cargar *ptr" << endl;
                    
                    if (exp->is_prefix) {
                        out << "    incq %rax" << endl;
                        out << "    movq %rax, (%rbx) # ++(*ptr)" << endl;
                    } else {
                        out << "    movq %rax, %rcx # guardar valor original" << endl;
                        out << "    incq %rax" << endl;
                        out << "    movq %rax, (%rbx) # (*ptr)++" << endl;
                        out << "    movq %rcx, %rax # retornar valor original" << endl;
                    }
                } else {
                    cerr << "Error: Operador ++ no soportado para esta expresión unaria" << endl;
                    exit(1);
                }
            } else {
                cerr << "Error: Operador ++ solo soportado para identificadores, miembros y punteros" << endl;
                exit(1);
            }
            break;
        }
        
        case MINUS_MINUS_OP: {
            if (auto id = dynamic_cast<IdentifierExp*>(exp->uexp)) {
                // AGREGADO: Verificar existencia
                if (!env->check(id->name)) {
                    cerr << "Error: Variable no declarada: " << id->name << endl;
                    exit(1);
                }
                
                VarInfo info = env->lookup(id->name);
                const char* regs[] = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"};

                // CORREGIDO: Verificar bounds del array
                if (info.is_reference && info.reg_index >= 0 && info.reg_index < 6) {
                    if (exp->is_prefix) {
                        out << "    decq %rax" << endl;
                        out << "    movq %rax, (" << regs[info.reg_index] << ")  # --*ref" << endl;
                    } else {
                        out << "    movq %rax, %rcx" << endl;
                        out << "    decq %rcx" << endl;
                        out << "    movq %rcx, (" << regs[info.reg_index] << ")  # *ref--" << endl;
                    }
                } else if (info.reg_index >= 0 && info.reg_index < 6) {
                    if (exp->is_prefix) {
                        out << "    decq %rax" << endl;
                        out << "    movq %rax, " << regs[info.reg_index] << "  # --param" << endl;
                    } else {
                        out << "    movq %rax, %rcx" << endl;
                        out << "    decq %rcx" << endl;
                        out << "    movq %rcx, " << regs[info.reg_index] << "  # param--" << endl;
                    }
                } else if (!info.is_global) {
                    int offset = info.offset;
                    if (exp->is_prefix) {
                        out << "    decq %rax" << endl;
                        out << "    movq %rax, " << offset << "(%rbp)" << endl;
                    } else {
                        out << "    movq %rax, %rcx" << endl;
                        out << "    decq %rcx" << endl;
                        out << "    movq %rcx, " << offset << "(%rbp)" << endl;
                    }
                } else {
                    // global
                    if (exp->is_prefix) {
                        out << "    decq %rax" << endl;
                        out << "    movq %rax, " << id->name << "(%rip)" << endl;
                    } else {
                        out << "    movq %rax, %rcx" << endl;
                        out << "    decq %rcx" << endl;
                        out << "    movq %rcx, " << id->name << "(%rip)" << endl;
                    }
                }
            } else if (auto member = dynamic_cast<MemberAccessExp*>(exp->uexp)) {
                // AGREGADO: Soporte para --obj->field y --obj.field
                get_member_address(member); // dirección en %rax
                out << "    movq %rax, %rbx # guardar dirección" << endl;
                out << "    movq (%rbx), %rax # cargar valor actual" << endl;
                
                if (exp->is_prefix) {
                    out << "    decq %rax" << endl;
                    out << "    movq %rax, (%rbx) # --member" << endl;
                } else {
                    out << "    movq %rax, %rcx # guardar valor original" << endl;
                    out << "    decq %rax" << endl;
                    out << "    movq %rax, (%rbx) # member--" << endl;
                    out << "    movq %rcx, %rax # retornar valor original" << endl;
                }
            } else if (auto unary = dynamic_cast<UnaryExp*>(exp->uexp)) {
                // AGREGADO: Soporte para --(*ptr)
                if (unary->op == DEREFERENCE_OP) {
                    unary->uexp->accept(this); // obtiene dirección del puntero
                    out << "    movq %rax, %rbx # guardar dirección" << endl;
                    out << "    movq (%rbx), %rax # cargar *ptr" << endl;
                    
                    if (exp->is_prefix) {
                        out << "    decq %rax" << endl;
                        out << "    movq %rax, (%rbx) # --(*ptr)" << endl;
                    } else {
                        out << "    movq %rax, %rcx # guardar valor original" << endl;
                        out << "    decq %rax" << endl;
                        out << "    movq %rax, (%rbx) # (*ptr)--" << endl;
                        out << "    movq %rcx, %rax # retornar valor original" << endl;
                    }
                } else {
                    cerr << "Error: Operador -- no soportado para esta expresión unaria" << endl;
                    exit(1);
                }
            } else {
                cerr << "Error: Operador -- solo soportado para identificadores, miembros y punteros" << endl;
                exit(1);
            }
            break;
        }
        
        case ADDRESS_OF_OP: {
            if (auto id = dynamic_cast<IdentifierExp*>(exp->uexp)) {
                if (!env->check(id->name)) {
                    cerr << "Error: Variable no declarada: " << id->name << endl;
                    exit(1);
                }
                VarInfo info = env->lookup(id->name);
                if (!info.is_global) {
                    out << "    leaq " << info.offset << "(%rbp), %rax  # &" << id->name << endl;
                } else {
                    out << "    leaq " << id->name << "(%rip), %rax  # &" << id->name << endl;
                }
            } else if (auto member = dynamic_cast<MemberAccessExp*>(exp->uexp)) {
                // AGREGADO: Soporte para &(obj->field) y &(obj.field)
                get_member_address(member); // ya devuelve la dirección en %rax
                out << "    # &member (dirección ya calculada)" << endl;
            } else {
                cerr << "Error: Operador & solo soportado para identificadores y miembros" << endl;
                exit(1);
            }
            break;
        }
        case DEREFERENCE_OP:
            out << "    movq (%rax), %rax  # *ptr" << endl;
            break;
        default:
            out << "    # Operador unario no implementado: " << exp->op << endl;
            break;
    }
    return 0;
}


int GenCodeVisitor::visit(BinaryExp* exp) {
    switch (exp->op) {
        case PLUS_OP:
            exp->left->accept(this);    // %rax = left
            out << "    movq %rax, %rdx" << endl;
            exp->right->accept(this);   // %rax = right
            out << "    addq %rdx, %rax" << endl;
            break;
        case MINUS_OP:
            exp->left->accept(this);
            out << "    movq %rax, %rdx" << endl;
            exp->right->accept(this);
            out << "    subq %rax, %rdx" << endl;
            out << "    movq %rdx, %rax" << endl;
            break;
        case MULT_OP:
            exp->left->accept(this);
            out << "    movq %rax, %rdx" << endl;
            exp->right->accept(this);
            out << "    imulq %rdx, %rax" << endl;
            break;
        case DIV_OP:
            exp->left->accept(this);
            out << "    movq %rax, %rdx" << endl;
            exp->right->accept(this);
            out << "    movq %rax, %rcx" << endl;
            out << "    movq %rdx, %rax" << endl;
            out << "    cqo" << endl;
            out << "    idivq %rcx" << endl;
            break;
        case MOD_OP:
            exp->left->accept(this);
            out << "    movq %rax, %rdx" << endl;
            exp->right->accept(this);
            out << "    movq %rax, %rcx" << endl;
            out << "    movq %rdx, %rax" << endl;
            out << "    cqo" << endl;
            out << "    idivq %rcx" << endl;
            out << "    movq %rdx, %rax" << endl;
            break;
        case EQUAL_OP:
            exp->left->accept(this);
            out << "    movq %rax, %rdx" << endl;
            exp->right->accept(this);
            out << "    cmpq %rax, %rdx" << endl;  // CORREGIDO: usar cmpq consistentemente
            out << "    movq $0, %rax" << endl;
            out << "    sete %al" << endl;
            out << "    movzbq %al, %rax" << endl;
            break;
        case NOT_EQUAL_OP:
            exp->left->accept(this);
            out << "    movq %rax, %rdx" << endl;
            exp->right->accept(this);
            out << "    cmpq %rax, %rdx" << endl;
            out << "    movq $0, %rax" << endl;
            out << "    setne %al" << endl;
            out << "    movzbq %al, %rax" << endl;
            break;
        case LESS_THAN_OP:
            exp->left->accept(this);
            out << "    movq %rax, %rdx" << endl;
            exp->right->accept(this);
            out << "    cmpq %rax, %rdx" << endl;
            out << "    movq $0, %rax" << endl;
            out << "    setl %al" << endl;
            out << "    movzbq %al, %rax" << endl;
            break;
        case GREATER_THAN_OP:
            exp->left->accept(this);
            out << "    movq %rax, %rdx" << endl;
            exp->right->accept(this);
            out << "    cmpq %rax, %rdx" << endl;
            out << "    movq $0, %rax" << endl;
            out << "    setg %al" << endl;
            out << "    movzbq %al, %rax" << endl;
            break;
        case LESS_EQUAL_OP:
            exp->left->accept(this);
            out << "    movq %rax, %rdx" << endl;
            exp->right->accept(this);
            out << "    cmpq %rax, %rdx" << endl;
            out << "    movq $0, %rax" << endl;
            out << "    setle %al" << endl;
            out << "    movzbq %al, %rax" << endl;
            break;
        case GREATER_EQUAL_OP:
            exp->left->accept(this);
            out << "    movq %rax, %rdx" << endl;
            exp->right->accept(this);
            out << "    cmpq %rax, %rdx" << endl;
            out << "    movq $0, %rax" << endl;
            out << "    setge %al" << endl;
            out << "    movzbq %al, %rax" << endl;
            break;
        case LOGICAL_AND_OP: {
            int label_false = cantidad++;
            int label_end = cantidad++;
            exp->left->accept(this);
            out << "    testq %rax, %rax" << endl;
            out << "    jz .Lfalse" << label_false << endl;
            exp->right->accept(this);
            out << "    testq %rax, %rax" << endl;
            out << "    movq $1, %rax" << endl;
            out << "    jnz .Lend" << label_end << endl;
            out << ".Lfalse" << label_false << ":" << endl;
            out << "    movq $0, %rax" << endl;
            out << ".Lend" << label_end << ":" << endl;
            break;
        }
        case LOGICAL_OR_OP: {
            int label_true = cantidad++;
            int label_end = cantidad++;
            exp->left->accept(this);
            out << "    testq %rax, %rax" << endl;
            out << "    jnz .Ltrue" << label_true << endl;
            exp->right->accept(this);
            out << "    testq %rax, %rax" << endl;
            out << "    movq $0, %rax" << endl;
            out << "    jz .Lend" << label_end << endl;
            out << ".Ltrue" << label_true << ":" << endl;
            out << "    movq $1, %rax" << endl;
            out << ".Lend" << label_end << ":" << endl;
            break;
        }
        case ASSIGN_OP: {
            // ELIMINADO: Este caso no debería estar aquí
            // La asignación se maneja en AssignExp, no en BinaryExp
            cerr << "Error: ASSIGN_OP encontrado en BinaryExp - debería ser AssignExp" << endl;
            exit(1);
            break;
        }
        default:
            out << "    # Operador binario no implementado: " << exp->op << endl;
            break;
    }
    return 0;
}

int GenCodeVisitor::visit(ArrayAccessExp* exp) {
    // Evaluar array base primero
    exp->array->accept(this);
    out << " pushq %rax # guardar dirección base del array" << endl;
    
    // Evaluar índice
    exp->index->accept(this);
    out << " popq %rcx # recuperar dirección base" << endl;
    
    // Calcular offset: base + index * 8 (8 bytes por elemento en 64 bits)
    out << " leaq (%rcx,%rax,8), %rax # calcular dirección del elemento" << endl;
    out << " movq (%rax), %rax # cargar valor del elemento" << endl;
    return 0;
}

int GenCodeVisitor::visit(MemberAccessExp* exp) {
    // AGREGADO: Verificar existencia antes de lookup
    if (auto id = dynamic_cast<IdentifierExp*>(exp->object)) {
        if (!env->check(id->name)) {
            cerr << "Error: Variable no declarada: " << id->name << endl;
            exit(1);
        }
    }
    
    // Detectar si es acceso local (ej: p.nombre)
    int base_offset = 0;
    std::string struct_type;
    bool is_local_struct = false;
    
    if (auto id = dynamic_cast<IdentifierExp*>(exp->object)) {
        struct_type = env->lookup_type(id->name);
        if (struct_type.rfind("struct ", 0) == 0) {
            struct_type = struct_type.substr(7);
        }
        VarInfo info = env->lookup(id->name);
        base_offset = info.offset;
        is_local_struct = !info.is_global;
    }
    
    int member_offset = 0;
    if (env->has_struct(struct_type)) {
        member_offset = env->get_struct_member_offset(struct_type, exp->member_name);
    } else {
        member_offset = 8;
    }
    
    if (exp->is_pointer) {
        // p->campo: necesita evaluar el objeto primero
        exp->object->accept(this); // obtiene el puntero en %rax
        out << " addq $" << member_offset << ", %rax # offset del miembro " << exp->member_name << endl;
        out << " movq (%rax), %rax # cargar valor del miembro" << endl;
    } else if (is_local_struct) {
        // p.campo: acceso directo en el stack
        out << " movq " << (base_offset + member_offset) << "(%rbp), %rax # " << exp->member_name << " de struct local" << endl;
    } else {
        // Caso general: struct no local
        exp->object->accept(this); // obtiene dirección del objeto
        out << " addq $" << member_offset << ", %rax # offset del miembro " << exp->member_name << endl;
        out << " movq (%rax), %rax # cargar valor del miembro" << endl;
    }
    return 0;
}


int GenCodeVisitor::visit(ParenExp* exp) {
    return exp->inner->accept(this);
}

int GenCodeVisitor::visit(ArrayInitializerExp* exp) {
    // CORREGIDO: No generar labels aquí, solo inicializar elementos
    // Este método se llama desde VarDec cuando hay un inicializador
    
    // La dirección base del array debe estar en %rax cuando se llama esto
    out << "    pushq %rax # guardar dirección base del array" << endl;
    
    for (size_t i = 0; i < exp->elements.size(); ++i) {
        exp->elements[i]->accept(this); // evalúa elemento en %rax
        out << "    popq %rbx # recuperar dirección base" << endl;
        out << "    movq %rax, " << (i * 8) << "(%rbx) # array[" << i << "] = valor" << endl;
        out << "    pushq %rbx # guardar dirección base para siguiente iteración" << endl;
    }
    
    out << "    popq %rax # dirección base final en %rax" << endl;
    return 0;
}

void GenCodeVisitor::visit(VarDec* stm) {
    for (size_t i = 0; i < stm->vars.size(); ++i) {
        string var_name = stm->vars[i];
        Type* var_type = stm->types[i];
        bool is_char = (var_type->type_name == "char");
        bool is_bool = (var_type->type_name == "bool");
        bool is_int = (var_type->type_name == "int");
        bool is_ptr = var_type->is_pointer;
        bool is_array = var_type->is_array;
        bool is_reference = var_type->is_reference;
        bool is_struct = (var_type->type_name.find("struct") == 0);

        // CORREGIDO: Todo a 8 bytes para 64 bits
        int var_size = 8;
        if (is_struct && !is_ptr) {
            string struct_name = var_type->type_name.substr(7);
            var_size = env->get_struct_size(struct_name);
        }
        
        // CORREGIDO: Usar siempre movq para 64 bits
        string mov_inst = "movq";
        string reg = "%rax";
        
        // CORREGIDO: Obtener offset correctamente del environment
        int current_offset = env->lookup(var_name).offset;
        
        if (is_array && var_type->array_size) {
            // CORREGIDO: Manejo de arrays
            var_type->array_size->accept(this); // tamaño en %rax
            
            int element_size = 8; // Por defecto 8 bytes
            if (is_char && !is_ptr) {
                element_size = 1;
            }
            
            out << "    imulq $" << element_size << ", %rax # elementos * tamaño" << endl;
            out << "    movq %rax, %rcx # guardar tamaño total" << endl;
            out << "    subq %rcx, %rsp # reservar espacio en stack" << endl;
            out << "    movq %rsp, " << current_offset << "(%rbp) # guardar puntero al array" << endl;

            // Inicialización del array
            if (stm->initializers[i]) {
                if (auto array_init = dynamic_cast<ArrayInitializerExp*>(stm->initializers[i])) {
                    out << "    movq %rsp, %rax # dirección base del array" << endl;
                    array_init->accept(this);
                } else {
                    // Inicializador single para todos los elementos
                    stm->initializers[i]->accept(this); // valor en %rax
                    out << "    movq %rax, %rbx # guardar valor" << endl;
                    out << "    movq %rsp, %rdi # dirección base" << endl;
                    out << "    movq %rcx, %rcx # contador de bytes" << endl;
                    out << "    shrq $3, %rcx # convertir a número de elementos de 8 bytes" << endl;
                    // Loop para inicializar todos los elementos
                    string loop_label = "init_loop_" + to_string(cantidad++);
                    string end_label = "init_end_" + to_string(cantidad++);
                    out << loop_label << ":" << endl;
                    out << "    testq %rcx, %rcx" << endl;
                    out << "    jz " << end_label << endl;
                    out << "    movq %rbx, (%rdi)" << endl;
                    out << "    addq $8, %rdi" << endl;
                    out << "    decq %rcx" << endl;
                    out << "    jmp " << loop_label << endl;
                    out << end_label << ":" << endl;
                }
            } else {
                // Inicializar a cero
                out << "    movq %rsp, %rdi # dirección base" << endl;
                out << "    xorq %rax, %rax # valor 0" << endl;
                out << "    rep stosb # llenar con ceros" << endl;
            }
            continue;
        }

        // CORREGIDO: Agregar variable al environment antes de usarla
        env->add_var(var_name, current_offset, var_type->type_name, is_ptr, is_array, is_reference, -1, false);
        
        // Inicialización de variables normales
        if (auto struct_init = dynamic_cast<StructInitializerExp*>(stm->initializers[i])) {
            struct_init->accept(this, current_offset);
        }
        else if (stm->initializers[i]) {
            stm->initializers[i]->accept(this); // valor en %rax
            out << "    movq %rax, " << current_offset << "(%rbp) # " << var_name << endl;
            
            // CORREGIDO: Para bool, asegurar que solo sea 0 o 1
            if (is_bool) {
                out << "    andq $1, " << current_offset << "(%rbp) # asegurar 0/1 para bool" << endl;
            }
        } else {
            // Inicialización por defecto
            out << "    movq $0, " << current_offset << "(%rbp) # inicializar " << var_name << " a 0" << endl;
        }
    }
}

void GenCodeVisitor::visit(VarDecList* stm) {
    for (auto vardec : stm->vardecs) {
        vardec->accept(this);
    }
}

void GenCodeVisitor::visit(GlobalVarDec* dec) {
    bool is_ptr = dec->type->is_pointer;
    bool is_array = dec->type->is_array;
    bool is_reference = dec->type->is_reference;
    string type_name = dec->type->type_name;
    
    // SOLO agregar al environment, NO generar código assembly
    // El código assembly ya se genera en gencode()
    env->add_var(dec->var_name, 0, type_name, is_ptr, is_array, is_reference, -1, true);
}

void GenCodeVisitor::visit(GlobalVarDecList* decList) {
    for (auto dec : decList->global_vardecs) {
        dec->accept(this);
    }
}

void GenCodeVisitor::visit(PrintfStatement* stm) {
    // Generar string de formato
    static int fmt_count = 0;
    string fmt_label = "printf_fmt_" + to_string(fmt_count++);
    
    out << ".section .rodata" << endl;
    out << fmt_label << ": .string " << stm->format_string << endl;
    out << ".text" << endl;
    
    // CORREGIDO: Alinear stack antes de la llamada
    out << "    pushq %rbp # salvar frame pointer para alineación" << endl;
    
    // Cargar dirección del formato en %rdi (primer argumento)
    out << "    leaq " << fmt_label << "(%rip), %rdi" << endl;
    
    // Procesar argumentos
    const char* arg_regs[] = {"%rsi", "%rdx", "%rcx", "%r8", "%r9"};
    int reg_index = 0;
    int stack_args = 0;
    
    // CORREGIDO: Evaluar argumentos en orden reverso para la pila
    vector<string> arg_code;
    
    for (auto arg : stm->arguments) {
        arg->accept(this); // Resultado en %rax
        
        if (reg_index < 5) {
            out << "    movq %rax, " << arg_regs[reg_index] << endl;
            reg_index++;
        } else {
            out << "    pushq %rax" << endl;
            stack_args++;
        }
    }
    
    // CORREGIDO: Para funciones variádicas, %al = número de registros vectoriales usados (0)
    out << "    xorq %rax, %rax # 0 registros vectoriales usados" << endl;
    
    // CORREGIDO: Alinear stack a 16 bytes antes de call
    if (stack_args % 2 != 0) {
        out << "    subq $8, %rsp # alinear stack a 16 bytes" << endl;
        stack_args++; // contar padding para limpieza
    }
    
    // Llamar printf
    out << "    call printf@PLT" << endl;
    
    // Limpiar argumentos de pila y padding
    if (stack_args > 0) {
        out << "    addq $" << (stack_args * 8) << ", %rsp" << endl;
    }
    
    // CORREGIDO: Restaurar frame pointer
    out << "    popq %rbp # restaurar frame pointer" << endl;
}


void GenCodeVisitor::visit(IfStatement* stm) {
    if (!stm) return;
    
    // CORREGIDO: Usar contador global en lugar de stm->id para evitar conflictos
    int label_else = cantidad++;
    int label_end = cantidad++;
    
    // Generar código para la condición
    stm->condition->accept(this);
    out << "    testq %rax, %rax" << endl;
    out << "    jz .Lelse" << label_else << endl; // Saltar a "else" si la condición es falsa
    
    // Cuerpo del "if"
    if (stm->statements)
        stm->statements->accept(this);
    
    // Si hay "else/else if", saltar al final para evitar ejecutarlos
    if (stm->elsChain) {
        out << "    jmp .Lendif" << label_end << endl;
    }
    
    // Etiqueta para el "else" (compartida por else if/else)
    out << ".Lelse" << label_else << ":" << endl;
    
    // Generar código para la cadena else/else if
    if (stm->elsChain) {
        stm->elsChain->accept(this);
    }
    
    // Etiqueta de cierre (solo si hubo else/else if)
    if (stm->elsChain) {
        out << ".Lendif" << label_end << ":" << endl;
    }
}

void GenCodeVisitor::visit(ElseIfStatement* stm) {
    if (!stm) return;
    
    if (stm->tipo == ElseIfStatement::ELSE_IF) {
        // CORREGIDO: Generar etiquetas únicas para cada else-if
        int label_next_else = cantidad++;
        int label_end = cantidad++;
        
        // Generar código para la condición
        stm->condition->accept(this);
        out << "    testq %rax, %rax" << endl;
        out << "    jz .Lelse" << label_next_else << endl; // Saltar al siguiente "else" si es falso
        
        // Cuerpo del "else if"
        if (stm->body)
            stm->body->accept(this);
        
        // Si hay más condiciones, saltar al final
        if (stm->nextChain) {
            out << "    jmp .Lendif" << label_end << endl;
        }
        
        // Etiqueta para el siguiente "else"
        out << ".Lelse" << label_next_else << ":" << endl;
        
        // Procesar siguiente condición en la cadena (else if/else)
        if (stm->nextChain) {
            stm->nextChain->accept(this);
        }
        
        // Etiqueta de cierre (solo si había más condiciones)
        if (stm->nextChain) {
            out << ".Lendif" << label_end << ":" << endl;
        }
    }
    else { // ELSE simple
        if (stm->body) {
            stm->body->accept(this); // No necesita etiquetas, es el último caso
        }
    }
}


void GenCodeVisitor::visit(Body* b) {
    // CORREGIDO: Necesitamos declarar variables cuando se encuentren
    // pero usando el offset que ya fue calculado por calcular_stack_body()
    
    int current_offset = env->get_current_offset(); // offset actual del environment
    
    // Primera pasada: declarar todas las variables en el environment
    for (auto elem : b->elements) {
        if (auto vardec = dynamic_cast<VarDec*>(elem)) {
            for (size_t i = 0; i < vardec->vars.size(); ++i) {
                int var_size = 8; // Por defecto 8 bytes para 64 bits
                
                if (vardec->types[i]->is_pointer) {
                    var_size = 8;
                } else if (vardec->types[i]->type_name == "char" || vardec->types[i]->type_name == "bool") {
                    var_size = 1;
                    if (var_size < 8) var_size = 8; // alinear a 8 bytes
                } else if (vardec->types[i]->type_name == "int") {
                    var_size = 8;
                } else if (vardec->types[i]->type_name.find("struct") == 0) {
                    std::string struct_name = vardec->types[i]->type_name.substr(7);
                    var_size = env->get_struct_size(struct_name);
                    if (var_size < 8) var_size = 8; // alinear a 8 bytes
                }
                
                current_offset -= var_size;
                
                // CRUCIAL: Agregar variable al environment
                env->add_var(
                    vardec->vars[i],
                    current_offset,
                    vardec->types[i]->type_name,
                    vardec->types[i]->is_pointer,
                    vardec->types[i]->is_array,
                    vardec->types[i]->is_reference,
                    -1, // no es parámetro
                    false // no es global
                );
                
                out << "# Declarando variable: " << vardec->vars[i] 
                    << " en offset " << current_offset << endl;
            }
        }
        // AGREGADO: También manejar ForStatement que declara variables
        else if (auto forstm = dynamic_cast<ForStatement*>(elem)) {
            if (auto vardec = dynamic_cast<VarDec*>(forstm->init)) {
                for (size_t i = 0; i < vardec->vars.size(); ++i) {
                    int var_size = 8;
                    if (vardec->types[i]->type_name.find("struct") == 0) {
                        std::string struct_name = vardec->types[i]->type_name.substr(7);
                        var_size = env->get_struct_size(struct_name);
                    }
                    if (var_size < 8) var_size = 8;
                    
                    current_offset -= var_size;
                    
                    env->add_var(
                        vardec->vars[i],
                        current_offset,
                        vardec->types[i]->type_name,
                        vardec->types[i]->is_pointer,
                        vardec->types[i]->is_array,
                        vardec->types[i]->is_reference,
                        -1,
                        false
                    );
                    
                    out << "# Declarando variable de for: " << vardec->vars[i] 
                        << " en offset " << current_offset << endl;
                }
            }
        }
    }
    
    // Actualizar offset actual en el environment
    env->set_current_offset(current_offset);
    
    // Segunda pasada: generar código para todas las sentencias
    for (auto elem : b->elements) {
        elem->accept(this);
    }
}

void GenCodeVisitor::visit(WhileStatement* stm) {
    // Generar etiquetas únicas para este while
    int label_start = cantidad++;
    int label_end = cantidad++;
    
    // Etiqueta de inicio del bucle
    out << ".Lwhile" << label_start << ":" << endl;
    
    // Evaluar condición
    stm->condition->accept(this);
    out << "    testq %rax, %rax" << endl;
    out << "    jz .Lendwhile" << label_end << endl;
    
    // Cuerpo del while
    if (stm->b) {
        stm->b->accept(this);
    }
    
    // Saltar de vuelta al inicio
    out << "    jmp .Lwhile" << label_start << endl;
    
    // Etiqueta de fin del bucle
    out << ".Lendwhile" << label_end << ":" << endl;
}

void GenCodeVisitor::visit(ForStatement* stm) {
    // Generar etiquetas únicas
    int label_start = cantidad++;
    int label_end = cantidad++;
    
    // CORREGIDO: Crear nuevo scope para variables del for
    env->add_level();
    
    // ELIMINADO: La declaración de variables ya se hizo en visit(Body*)
    // Solo ejecutar la inicialización
    if (stm->init) {
        stm->init->accept(this);
    }
    
    // Etiqueta de inicio del bucle
    out << ".Lfor" << label_start << ":" << endl;
    
    // Condición (si existe)
    if (stm->condition) {
        stm->condition->accept(this);
        out << "    testq %rax, %rax" << endl;
        out << "    jz .Lendfor" << label_end << endl;
    }
    
    // Cuerpo del for
    if (stm->b) {
        stm->b->accept(this);
    }
    
    // Incremento/update
    if (stm->update) {
        stm->update->accept(this);
    }
    
    // Saltar de vuelta al inicio
    out << "    jmp .Lfor" << label_start << endl;
    
    // Etiqueta de fin del bucle
    out << ".Lendfor" << label_end << ":" << endl;
    
    // CORREGIDO: Remover scope del for
    env->remove_level();
}

void GenCodeVisitor::visit(ExpressionStatement* stm) {
    if (stm->expression)
        stm->expression->accept(this);
}

void GenCodeVisitor::visit(StatementList* stm) {
    for (auto s : stm->stms) {
        s->accept(this);
    }
}

void GenCodeVisitor::visit(Parameter* param) {
    // ELIMINADO: Los parámetros no se manejan aquí individualmente
    // Se manejan en visit(Function*) de manera completa
}

void GenCodeVisitor::visit(ParameterList* paramList) {
    // ELIMINADO: Los parámetros se manejan en visit(Function*)
    // Esta función puede estar vacía o solo para validación
}

void GenCodeVisitor::visit(Function* func) {
    // Prólogo de función
    out << ".globl " << func->name << endl;
    out << func->name << ":" << endl;
    out << "    pushq %rbp" << endl;
    out << "    movq %rsp, %rbp" << endl;

    // CORREGIDO: Calcular espacio completo usando calcular_stack_body
    int stack_space = 0;
    if (func->body) {
        stack_space = calcular_stack_body(func->body);
    }
    
    // Alineación a 16 bytes
    if (stack_space % 16 != 0) {
        stack_space = ((stack_space + 15) / 16) * 16;
    }
    
    if (stack_space > 0) {
        out << "    subq $" << stack_space << ", %rsp" << endl;
    }

    // CORREGIDO: Preparar información de función
    FunctionInfo func_info;
    func_info.return_type = func->return_type->type_name;
    func_info.stack_size = stack_space;

    // CORREGIDO: Manejar parámetros correctamente
    if (func->parameters) {
        for (size_t i = 0; i < func->parameters->parameters.size(); ++i) {
            auto param = func->parameters->parameters[i];
            FunctionParamInfo param_info;
            param_info.name = param->name;
            param_info.type = param->type->type_name;
            param_info.is_pointer = param->type->is_pointer;
            param_info.is_array = param->type->is_array;
            param_info.is_reference = param->is_reference;
            param_info.reg_index = (i < 6) ? i : -1;
            func_info.params.push_back(param_info);
            
            // CORREGIDO: Agregar al environment con reg_index correcto
            env->add_var(
                param->name, 
                0,  // offset 0 para parámetros en registros
                param->type->type_name, 
                param->type->is_pointer, 
                param->type->is_array, 
                param->is_reference,
                param_info.reg_index,  // índice del registro
                false  // no es global
            );
            
            out << "# Parámetro: " << param->name
                << " reg_index: " << param_info.reg_index
                << " is_reference: " << (param->is_reference ? "true" : "false")
                << endl;
        }
    }

    env->add_function(func->name, func_info);
    env->add_level();
    
    if (func->body) {
        func->body->accept(this);
    }
    
    env->remove_level();
    
    // AGREGADO: Epílogo automático si no hay return explícito
    out << "    leave" << endl;
    out << "    ret" << endl;
}

void GenCodeVisitor::visit(ReturnStatement* stm) {
    if (stm->return_value) {
        stm->return_value->accept(this);
    }
    
    out << "    leave" << endl;
    out << "    ret" << endl;
}

int GenCodeVisitor::visit(FunctionCallExp* exp) {
    // AGREGADO: Verificar existencia de función
    if (!env->has_function(exp->function_name)) {
        cerr << "Error: Función '" << exp->function_name << "' no declarada" << endl;
        exit(1);
    }
    
    auto func_info = env->get_function(exp->function_name);
    const char* regs[] = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"};
    int stack_args = 0;
    
    // CORREGIDO: Verificar número de argumentos
    if (exp->arguments.size() != func_info.params.size()) {
        cerr << "Error: Número incorrecto de argumentos para '" << exp->function_name 
             << "'. Esperados: " << func_info.params.size() 
             << ", dados: " << exp->arguments.size() << endl;
        exit(1);
    }
    
    // Evaluar argumentos y pasarlos
    for (size_t i = 0; i < exp->arguments.size(); ++i) {
        auto& param_info = func_info.params[i];
        
        if (param_info.is_reference) {
            // Parámetro por referencia - pasar dirección
            if (auto id = dynamic_cast<IdentifierExp*>(exp->arguments[i])) {
                // CORREGIDO: Verificar existencia antes del lookup
                if (!env->check(id->name)) {
                    cerr << "Error: Variable no declarada: " << id->name << endl;
                    exit(1);
                }
                VarInfo var_info = env->lookup(id->name);
                if (!var_info.is_global) {
                    out << "    leaq " << var_info.offset << "(%rbp), %rax # &" << id->name << endl;
                } else {
                    out << "    leaq " << id->name << "(%rip), %rax # &" << id->name << endl;
                }
            } else if (auto member = dynamic_cast<MemberAccessExp*>(exp->arguments[i])) {
                // AGREGADO: Soporte para &(obj->field)
                get_member_address(member);
            } else if (auto unary = dynamic_cast<UnaryExp*>(exp->arguments[i])) {
                if (unary->op == DEREFERENCE_OP) {
                    unary->uexp->accept(this); // ya es una dirección
                } else {
                    cerr << "Error: Argumento por referencia inválido" << endl;
                    exit(1);
                }
            } else {
                cerr << "Error: Argumento por referencia debe ser variable o member" << endl;
                exit(1);
            }
        } else {
            // Parámetro por valor - evaluar normalmente
            exp->arguments[i]->accept(this);
        }

        // Pasar argumento en registro o stack
        if (i < 6) {
            out << "    movq %rax, " << regs[i] << endl;
        } else {
            out << "    pushq %rax" << endl;
            stack_args++;
        }
    }

    // CORREGIDO: Alinear stack a 16 bytes antes de call
    bool needs_padding = (stack_args % 2) != 0;
    if (needs_padding) {
        out << "    subq $8, %rsp # alinear stack a 16 bytes" << endl;
        stack_args++; // contar padding para limpieza
    }

    // Llamar función
    out << "    call " << exp->function_name << endl;

    // Limpiar argumentos de la pila (incluyendo padding)
    if (stack_args > 0) {
        out << "    addq $" << (stack_args * 8) << ", %rsp" << endl;
    }

    return 0;
}

void GenCodeVisitor::visit(FunctionList* funcList) {
    for (auto func : funcList->functions) {
        func->accept(this);
    }
}

void GenCodeVisitor::visit(MainFunction* mainFunc) {
    if (mainFunc->body) {
        mainFunc->body->accept(this);
    }
  
}

void GenCodeVisitor::visit(StructDeclaration* structDecl) {
    StructInfo info;
    int offset = 0;
    
    if (structDecl->members) {
        for (auto member : structDecl->members->vardecs) {
            for (size_t i = 0; i < member->vars.size(); ++i) {
                // CORREGIDO: Determinar tamaño usando 64 bits
                int member_size = 8; // Por defecto 8 bytes para 64 bits
                
                if (member->types[i]->is_pointer) {
                    member_size = 8; // Punteros siempre 8 bytes en 64 bits
                } else if (member->types[i]->type_name == "char" || member->types[i]->type_name == "bool") {
                    member_size = 1; // char/bool siguen siendo 1 byte
                } else if (member->types[i]->type_name == "int") {
                    member_size = 8; // CORREGIDO: int es 8 bytes en 64 bits
                } else if (member->types[i]->type_name.find("struct") == 0) {
                    // CORREGIDO: Manejar structs anidados
                    string struct_name = member->types[i]->type_name.substr(7);
                    if (env->has_struct(struct_name)) {
                        member_size = env->get_struct_size(struct_name);
                    }
                }
                
                // CORREGIDO: Alineación más específica
                int alignment = 8; // Alinear a 8 bytes para 64 bits
                if (member_size == 1) {
                    alignment = 1; // char/bool no necesitan alineación especial
                }
                offset = (offset + alignment - 1) & ~(alignment - 1);
                
                // Registrar campo
                info.fields[member->vars[i]] = {
                    member->types[i]->type_name, 
                    member->types[i]->is_pointer, 
                    member->types[i]->is_array
                };
                info.offsets[member->vars[i]] = offset;
                
                out << "# Miembro: " << member->vars[i] 
                    << " tipo: " << member->types[i]->type_name
                    << " offset: " << offset 
                    << " tamaño: " << member_size << endl;
                
                // CORREGIDO: Manejo de arrays
                if (member->types[i]->is_array) {
                    if (member->types[i]->array_size) {
                        // Array con tamaño conocido
                        // TODO: Evaluar array_size si es una expresión
                        // Por ahora asumimos un tamaño fijo
                        int array_elements = 10; // valor por defecto
                        member_size = member_size * array_elements;
                    } else {
                        // Array sin tamaño - tratar como puntero
                        member_size = 8;
                    }
                }
                
                offset += member_size;
            }
        }
    }
    
    // CORREGIDO: Alinear el tamaño total a 8 bytes
    info.size = (offset + 7) & ~7;
    env->add_struct(structDecl->struct_name, info);
    
    out << "# Struct " << structDecl->struct_name << " tamaño total: " << info.size << endl;
    
    // Debug: mostrar todos los campos
    for (const auto& field : info.offsets) {
        out << "# Campo " << field.first << ": offset " << field.second << endl;
    }
}

void GenCodeVisitor::visit(StructDeclarationList* structList) {
    for (auto structDecl : structList->structs) {
        structDecl->accept(this);
    }
}

int GenCodeVisitor::visit(StructInitializerExp* exp, int base_offset) {
    out << "# Inicializando struct en offset " << base_offset << endl;
    
    if (!env->has_struct(exp->struct_name)) {
        cerr << "Error: Estructura '" << exp->struct_name << "' no declarada" << endl;
        exit(1);
    }
    
    StructInfo info = env->get_struct(exp->struct_name);
    
    // CORREGIDO: Ordenar campos por offset para inicialización correcta
    std::vector<std::string> field_names;
    for (const auto& kv : info.offsets) {
        field_names.push_back(kv.first);
    }
    std::sort(field_names.begin(), field_names.end(),
        [&](const std::string& a, const std::string& b) {
            return info.offsets.at(a) < info.offsets.at(b);
        });
    
    // CORREGIDO: Verificar que haya suficientes valores de inicialización
    if (exp->members.size() > field_names.size()) {
        cerr << "Error: Demasiados inicializadores para struct '" << exp->struct_name << "'" << endl;
        exit(1);
    }
    
    // Inicializar campos en orden
    for (size_t i = 0; i < exp->members.size() && i < field_names.size(); ++i) {
        int field_offset = info.offsets.at(field_names[i]);
        
        // Evaluar expresión de inicialización
        exp->members[i].second->accept(this); // valor en %rax
        
        // CORREGIDO: Usar movq consistentemente para 64 bits
        out << "    movq %rax, " << (base_offset + field_offset) 
            << "(%rbp) # " << field_names[i] << endl;
    }
    
    // AGREGADO: Inicializar campos restantes a 0
    for (size_t i = exp->members.size(); i < field_names.size(); ++i) {
        int field_offset = info.offsets.at(field_names[i]);
        out << "    movq $0, " << (base_offset + field_offset) 
            << "(%rbp) # " << field_names[i] << " = 0" << endl;
    }
    
    return 0;
}

int GenCodeVisitor::visit(StructInitializerExp* exp) {
    // CORREGIDO: Esta versión no debería usarse normalmente
    // Se llama cuando StructInitializerExp aparece como expresión independiente
    cerr << "Error: StructInitializerExp usado fuera de declaración de variable" << endl;
    exit(1);
    
    // Alternativa si quieres permitirlo:
    // return visit(exp, 0);
}

void GenCodeVisitor::visit(Include* inc) {
}

void GenCodeVisitor::visit(IncludeList* incList) {
}

void GenCodeVisitor::visit(Type* type) {
}

