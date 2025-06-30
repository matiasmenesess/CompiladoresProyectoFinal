
//
// Created by zamirlm on 6/21/25.
//
#include <stdexcept>
#include "visitor.h"
#include <iostream>
#include "expression.h"
#include <unordered_map>
#include <algorithm>
#include <iterator>
using namespace std;

// Accept methods implementations
int Include::accept(Visitor *visitor) {
    visitor->visit(this);
    return 0;
}

int IncludeList::accept(Visitor *visitor) {
    visitor->visit(this);
    return 0;
}

int Type::accept(Visitor *visitor) {
     visitor->visit(this);
    return 0;
}

int BinaryExp::accept(Visitor *visitor) {
    return visitor->visit(this);
}


int AssignExp::accept(Visitor *visitor) {
    return visitor->visit(this);
}

int UnaryExp::accept(Visitor *visitor) {
    return visitor->visit(this);
}

int NumberExp::accept(Visitor *visitor) {
    return visitor->visit(this);
}

int BoolExp::accept(Visitor *visitor) {
    return visitor->visit(this);
}

int CharExp::accept(Visitor *visitor) {
    return visitor->visit(this);
}

int StringExp::accept(Visitor *visitor) {
    return visitor->visit(this);
}

int IdentifierExp::accept(Visitor *visitor) {
    return visitor->visit(this);
}

int FunctionCallExp::accept(Visitor *visitor) {
    return visitor->visit(this);
}

int ArrayAccessExp::accept(Visitor *visitor) {
    return visitor->visit(this);
}

int MemberAccessExp::accept(Visitor *visitor) {
    return visitor->visit(this);
}

int ParenExp::accept(Visitor *visitor) {
    return visitor->visit(this);
}

int PrintfStatement::accept(Visitor *visitor) {
    visitor->visit(this);
    return 0;
}

int IfStatement::accept(Visitor *visitor) {
    visitor->visit(this);
    return 0;
}

int ElseIfStatement::accept(Visitor *visitor) {
    visitor->visit(this);
    return 0;
}

int WhileStatement::accept(Visitor *visitor) {
    visitor->visit(this);
    return 0;
}

int ForStatement::accept(Visitor *visitor) {
    visitor->visit(this);
    return 0;
}

int ExpressionStatement::accept(Visitor *visitor) {
    visitor->visit(this);
    return 0;
}
int ArrayInitializerExp::accept(Visitor *visitor) {
    return visitor->visit(this);
    
}

int ReturnStatement::accept(Visitor *visitor) {
    visitor->visit(this);
    return 0;
}

int VarDec::accept(Visitor *visitor) {
    visitor->visit(this);
    return 0;
}

int VarDecList::accept(Visitor *visitor) {
    visitor->visit(this);
    return 0;
}

int GlobalVarDec::accept(Visitor *visitor) {
    visitor->visit(this);
    return 0;
}

int GlobalVarDecList::accept(Visitor *visitor) {
    visitor->visit(this);
    return 0;
}


int Parameter::accept(Visitor *visitor) {
    visitor->visit(this);
    return 0;
}

int ParameterList::accept(Visitor *visitor) {
    visitor->visit(this);
    return 0;
}

int StatementList::accept(Visitor *visitor) {
    visitor->visit(this);
    return 0;
}

int Body::accept(Visitor *visitor) {
    visitor->visit(this);
    return 0;
}

int Function::accept(Visitor *visitor) {
    visitor->visit(this);
    return 0;
}

int FunctionList::accept(Visitor *visitor) {
    visitor->visit(this);
    return 0;
}

int MainFunction::accept(Visitor *visitor) {
    visitor->visit(this);
    return 0;
}


int StructDeclaration::accept(Visitor *visitor) {
    visitor->visit(this);
    return 0;
}

int StructDeclarationList::accept(Visitor *visitor) {
    visitor->visit(this);
    return 0;
}
int StructInitializerExp::accept(Visitor *visitor) {
    return visitor->visit(this);
}

//Print Visitor implementation
//Print Visitor implementation

void PrintVisitor::visit(Include* inc) {
    cout << "#include "
         << inc->header_name << endl;
}

void PrintVisitor::visit(IncludeList* inc_list) {
    for (auto& inc : inc_list->includes) {
        inc->accept(this);
    }
}



int PrintVisitor::visit(BinaryExp* exp) {
    exp->left->accept(this);
    cout << " " << Exp::binopToChar(exp->op) << " ";
    exp->right->accept(this);
    return 0;
}

int PrintVisitor::visit(ArrayInitializerExp* exp) {
    cout << "{";
    for (size_t i = 0; i < exp->elements.size(); ++i) {
        exp->elements[i]->accept(this);
        if (i < exp->elements.size() - 1) {
            cout << ", ";
        }
    }
    cout << "}";
    return 0;
}

int PrintVisitor::visit(StructInitializerExp* exp) {
    cout << "{";
    for (size_t i = 0; i < exp->members.size(); ++i) {
        exp->members[i].second->accept(this);
        if (i < exp->members.size() - 1) {
            cout << ", ";
        }
    }
    cout << "}";
    return 0;
}
int PrintVisitor::visit(AssignExp* exp) {
    exp->left->accept(this);
    cout << " " << Exp::binopToChar(exp->assign_op) << " ";
    exp->right->accept(this);
    return 0;
}

int PrintVisitor::visit(UnaryExp* exp) {
    if (exp->is_prefix) {
        cout << Exp::unaryToChar(exp->op);
        exp->uexp->accept(this);
    } else {
        exp->uexp->accept(this);
        cout << Exp::unaryToChar(exp->op);
    }
    return 0;
}

int PrintVisitor::visit(NumberExp* exp) {
    cout << exp->value;
    return 0;
}

int PrintVisitor::visit(BoolExp* exp) {
    cout << (exp->value ? "true" : "false");
    return 0;
}

int PrintVisitor::visit(CharExp* exp) {
    cout << "'" << exp->value << "'";
    return 0;
}

int PrintVisitor::visit(StringExp* exp) {
    cout  << exp->value;
    return 0;
}

int PrintVisitor::visit(IdentifierExp* exp) {
    cout << exp->name;
    return 0;
}

int PrintVisitor::visit(FunctionCallExp* exp) {
    cout << exp->function_name << "(";
    for (size_t i = 0; i < exp->arguments.size(); ++i) {
        exp->arguments[i]->accept(this);
        if (i < exp->arguments.size() - 1) {
            cout << ", ";
        }
    }
    cout << ")";
    return 0;
}

int PrintVisitor::visit(ArrayAccessExp* exp) {
    exp->array->accept(this);
    cout << "[";
    exp->index->accept(this);
    cout << "]";
    return 0;
}

int PrintVisitor::visit(MemberAccessExp* exp) {
    exp->object->accept(this);
    cout << (exp->is_pointer ? "->" : ".");
    cout << exp->member_name;
    return 0;
}


int PrintVisitor::visit(ParenExp* exp) {
    cout << "(";
    exp->inner->accept(this);
    cout << ")";
    return 0;
}

void PrintVisitor::visit(PrintfStatement* stm) {
    printIndent();
    cout << "printf(" << stm->format_string;
    if (!stm->arguments.empty()) {
        cout << ", ";
        for (size_t i = 0; i < stm->arguments.size(); ++i) {
            stm->arguments[i]->accept(this);
            if (i < stm->arguments.size() - 1) {
                cout << ", ";
            }
        }
    }
    cout << ");" << endl;
}
void PrintVisitor::visit(IfStatement* stm) {
    if (!stm) return;

    // Imprimir if
    printIndent();

    cout << "if (";
    if (stm->condition) stm->condition->accept(this);
    cout << ") {" << endl;

    indent_level++;
    if (stm->statements) stm->statements->accept(this);
    indent_level--;

    printIndent();

    cout << "}";
    if (stm->elsChain) {
        stm->elsChain->accept(this);
    }


    cout << endl;
}

void PrintVisitor::visit(ElseIfStatement* stm) {
    if (!stm) return;

    if (stm->tipo == ElseIfStatement::ELSE_IF) {
        cout << "else if (";
        if (stm->condition)
            stm->condition->accept(this);
        cout << ")";
        cout << " {" << endl;
        indent_level++;
        if (stm->body) stm->body->accept(this);
        indent_level--;
        printIndent();
        cout << "}";
        if (stm->nextChain) {
            stm->nextChain->accept(this);
        }
    }


    if (stm->tipo == ElseIfStatement::ELSE ) {
        cout << " else {" << endl;
        indent_level++;
        if (stm->body) stm->body->accept(this);
        indent_level--;
        printIndent();
        cout << "}";
    }
}

void PrintVisitor::visit(WhileStatement* stm) {
    printIndent();
    cout << "while (";
    stm->condition->accept(this);
    cout << ") {" << endl;
    indent_level++;
    stm->b->accept(this);
    indent_level--;
    printIndent();
    cout << "}" << endl;
}

void PrintVisitor::visit(ForStatement* stm) {
    printIndent();
    cout << "for (";
    if (stm->init) {
        stm->init->types[0]->accept(this);
        cout << " ";
        for (size_t i = 0; i < stm->init->vars.size(); ++i) {
            cout << stm->init->vars[i];
            if (!stm->init->initializers.empty() && i < stm->init->initializers.size()) {
                cout << " = ";
                stm->init->initializers[i]->accept(this);
            }
            if (i < stm->init->vars.size() - 1) {
                cout << ", ";
            }
        }
    }
    cout << "; ";
    if (stm->condition) {
        stm->condition->accept(this);
    }
    cout << "; ";
    if (stm->update) {
        stm->update->accept(this);
    }
    cout << ") {" << endl;
    indent_level++;
    stm->b->accept(this);
    indent_level--;
    printIndent();
    cout << "}" << endl;
}

void PrintVisitor::visit(ExpressionStatement* stm) {
    printIndent();
    stm->expression->accept(this);
    cout << ";" << endl;
}

void PrintVisitor::visit(ReturnStatement* stm) {
    printIndent();
    cout << "return";
    if (stm->return_value) {
        cout << " ";
        stm->return_value->accept(this);
    }
    cout << ";" << endl;
}

void PrintVisitor::visit(Type* type) {
    cout << type->type_name;
    if (type->is_pointer) {
        cout << "*";
    }
  
    if (type->is_reference) {
        cout << "&";
    }
}


void PrintVisitor::visit(VarDec* vardec) {
    printIndent();
    for (size_t i = 0; i < vardec->vars.size(); ++i) {
        if (i < vardec->types.size() && vardec->types[i]) {
            vardec->types[i]->accept(this); // <-- Esto imprime el tipo
          
        } else {
            cout << "/*tipo?*/";
        }
        cout << " " << vardec->vars[i];
        if(vardec->types[i]->is_array) {
            cout << "[";
            if (vardec->types[i]->array_size) {
                vardec->types[i]->array_size->accept(this);
            }
            cout << "]";
        }
        if (!vardec->initializers.empty() && i < vardec->initializers.size() && vardec->initializers[i]) {
            cout << " = ";
            vardec->initializers[i]->accept(this);
        }
        cout << ";" << endl;
    }
}

void PrintVisitor::visit(VarDecList* vardec_list) {
    for (auto& vardec : vardec_list->vardecs) {
        vardec->accept(this);
    }
}

void PrintVisitor::visit(GlobalVarDec* global_vardec) {
    printIndent();
    global_vardec->type->accept(this);
    cout << " " << global_vardec->var_name;
    if (global_vardec->initializer) {
        cout << " = ";
        global_vardec->initializer->accept(this);
    }
    cout << ";" << endl;
}

void PrintVisitor::visit(GlobalVarDecList* global_vardec_list) {
    for (auto& global_vardec : global_vardec_list->global_vardecs) {
        global_vardec->accept(this);
    }
}

void PrintVisitor::visit(Parameter* param) {
    param->type->accept(this);
    if(param->is_reference) {
        cout << "&";
    }
    cout << " " << param->name;
     if(param->type->is_array) {
        cout << "[]";
    }
}

void PrintVisitor::visit(ParameterList* param_list) {
    for (size_t i = 0; i < param_list->parameters.size(); ++i) {
        param_list->parameters[i]->accept(this);
        if (i < param_list->parameters.size() - 1) {
            cout << ", ";
        }
    }
}

void PrintVisitor::visit(StatementList* stm_list) {
    for (auto& stm : stm_list->stms) {
        stm->accept(this);
    }
}



void PrintVisitor::visit(Body* b) {
    if (b->elements.empty()) {
        cout << "/* Empty body */" << endl;
        return;
    }
    for (auto& elem : b->elements) {
        elem->accept(this);
    }
}

void PrintVisitor::visit(Function* func) {
    if (!func) return; 

    printIndent();
    if (func->return_type) {
        func->return_type->accept(this);
        cout << " ";
    }
    cout << func->name << "(";
    if (func->parameters) {
        func->parameters->accept(this);
    }
    cout << ") {" << endl;
    indent_level++;
    if (func->body) {
        func->body->accept(this);
    }
    indent_level--;

    printIndent();
    cout << "}" << endl << endl;
}

void PrintVisitor::visit(FunctionList* func_list) {
    for (auto& func : func_list->functions) {
        func->accept(this);
    }
}

void PrintVisitor::visit(MainFunction* main_func) {
    printIndent();
    cout << "int main() {" << endl;
    indent_level++;
    if (main_func->body) {
        main_func->body->accept(this);
    }
    indent_level--;
    printIndent();
    cout << "}" << endl;
}

void PrintVisitor::visit(StructDeclaration* struct_decl) {
    printIndent();
    cout << "struct " << struct_decl->struct_name << " {" << endl;
    indent_level++;
    if (struct_decl->members) {
        for (auto member : struct_decl->members->vardecs) {
            printIndent();
            member->types[0]->accept(this);
            cout << " ";
            for (size_t i = 0; i < member->vars.size(); ++i) {
                cout << member->vars[i];
                if (i < member->vars.size() - 1) {
                    cout << ", ";
                }
            }
            cout << ";" << endl;
        }
    }
    indent_level--;
    printIndent();
    cout << "};" << endl << endl;
}

void PrintVisitor::visit(StructDeclarationList* struct_list) {
    for (auto& struct_decl : struct_list->structs) {
        struct_decl->accept(this);
    }
}

void PrintVisitor::printIndent() {
    for (int i = 0; i < indent_level; ++i) {
        cout << "    ";  // 4 spaces per indent level
    }
}

void PrintVisitor::imprimir(Program* program) {
    // Print includes
    if (program->includes) {
        program->includes->accept(this);
        cout << endl;
    }

    // Print global declarations
    if (program->global_declarations) {
        program->global_declarations->accept(this);
        cout << endl;
    }

    // Print struct declarations
    if (program->struct_declarations) {
        program->struct_declarations->accept(this);
    }

    if (program->functions) {
        program->functions->accept(this);
    }

    if (program->main_function) {
        program->main_function->accept(this);
    }
}


//TypeChecker
/*
enum TypeEnum {
    INT_TYPE,
    BOOL_TYPE,
    CHAR_TYPE,
    STRING_TYPE,
    VOID_TYPE,
    STRUCT_TYPE,
    ARRAY_TYPE,
    POINTER_TYPE,
    UNDEFINED_TYPE
};

class TypeInfo {
public:
    TypeEnum type;
    string struct_name;
    TypeInfo* base_type;

    TypeInfo(TypeEnum t) : type(t), base_type(nullptr) {}
    TypeInfo(TypeEnum t, string name) : type(t), struct_name(name), base_type(nullptr) {}
    TypeInfo(TypeEnum t, TypeInfo* base) : type(t), base_type(base) {}
};


TypeChecker::TypeChecker() {
    env = new Environment();
}

TypeChecker::~TypeChecker() {
    delete env;
}
void TypeChecker::visit(PrintfStatement *stm) {

}
*/
// GenCodeVisitor completo con Environment integrado



void GenCodeVisitor::gencode(Program* program) {
    out << ".data" << endl;
    out << "print_fmt: .string \"%ld\\n\"" << endl;
    int stack_space = 0;
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
    out << "    pushq %rbp" << endl;
    out << "    movq %rsp, %rbp" << endl;

    // Espacio para variables locales
    if (program->main_function && program->main_function->body) {
        for (auto elem : program->main_function->body->elements) {
            if (auto vardec = dynamic_cast<VarDec*>(elem)) {
                for (size_t i = 0; i < vardec->vars.size(); ++i) {
                    int var_size = 8;
                    if (vardec->types[i]->type_name.find("struct") == 0) {
                        std::string struct_name = vardec->types[i]->type_name.substr(7);
                        var_size = env->get_struct_size(struct_name);
                    }
                    stack_space += var_size;
                }
            }
        }
    }
    if (stack_space % 16 != 0) stack_space += 8; // alineación
    if (stack_space > 0) {
        out << "    subq $" << stack_space << ", %rsp" << endl;
    }
    // *** Inicialización de variables globales ***
    if (program->global_declarations) {

        for (auto dec : program->global_declarations->global_vardecs) {
            if (dec->initializer) {
                dec->initializer->accept(this); // genera instrucciones para calcular el valor en %rax
                out << "    movq %rax, " << dec->var_name << "(%rip)" << endl;
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
    out << "    movq $" << exp->value << ", %rax" << endl;
    return exp->value;
}

int GenCodeVisitor::visit(CharExp* exp) {
    out << "    movq $" << (int)exp->value << ", %rax" << endl;
    return exp->value;
}

int GenCodeVisitor::visit(BoolExp* exp) {
    out << "    movq $" << (exp->value ? 1 : 0) << ", %rax" << endl;
    return exp->value;
}

int GenCodeVisitor::visit(StringExp* exp) {
    string label = "string_" + to_string(cantidad++);
    out << ".section .rodata" << endl;
    out << label << ": .string " << exp->value  << endl;
    out << ".text" << endl;
    out << "    leaq " << label << "(%rip), %rax" << endl;
    return 0;
}

int GenCodeVisitor::visit(IdentifierExp* exp) {
    VarInfo info = env->lookup(exp->name);
    if(env->check(exp->name) == false) {
        cout << "Variable no declarada: " << exp->name << endl;
        exit(0);
    }
    const char* regs[] = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"};
    out << "# Cargando valor de " << exp->name << " " << info.is_reference << " " << info.reg_index << endl;
    if (info.is_reference && info.reg_index >= 0) {
        out << "    movq (" << regs[info.reg_index] << "), %rax  # Valor de* " << exp->name << endl;
    } else if (info.reg_index >= 0) {
        out << "    movq " << regs[info.reg_index] << ", %rax  # Valor de " << exp->name << endl;
    } else if (!info.is_global) {
        out << "    movq " << info.offset << "(%rbp), %rax  # " << exp->name << endl;
    } else {
        out << "    movq " << exp->name << "(%rip), %rax  # " << exp->name << endl;
    }
    return 0;
}


int GenCodeVisitor::visit(AssignExp* exp) {

    if (exp->assign_op == ASSIGN_OP) {
        exp->right->accept(this);
        out << "    pushq %rax" << endl;
        if (auto id = dynamic_cast<IdentifierExp*>(exp->left)) {
            VarInfo info = env->lookup(id->name);
            out << "    popq %rax" << endl;
            const char* regs[] = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"};
            // --- GUARDAR EL RESULTADO ---
            if (info.is_reference ) {
                out << "    movq %rax, (" << regs[info.reg_index] << ")  # guardar en *" << id->name << endl;
            } else if (info.reg_index >= 0) {
                out << "    movq %rax, " << regs[info.reg_index] << "  # guardar en parámetro " << id->name << endl;
            } else if (!info.is_global) {
                out << "    movq %rax, " << info.offset << "(%rbp)  # guardar en local " << id->name << endl;
            } else {
                out << "    movq %rax, " << id->name << "(%rip)  # guardar en global " << id->name << endl;
            }
        }
    } else if (exp->assign_op == PLUS_EQUAL_OP ||
        exp->assign_op == MINUS_EQUAL_OP ||
               exp->assign_op == MULTIPLY_EQUAL_OP ||
               exp->assign_op == DIVIDE_EQUAL_OP ||
               exp->assign_op == MODULO_EQUAL_OP) {
        if (auto id = dynamic_cast<IdentifierExp*>(exp->left)) {
            VarInfo info = env->lookup(id->name);
            exp->right->accept(this);
            out << "    movq %rax, %rcx  # b\n";
            const char* regs[] = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"};
            // --- CARGAR EL VALOR DE LA IZQUIERDA ---

            if (info.is_reference && info.reg_index >= 0) {
                out << "    movq (" << regs[info.reg_index] << "), %rax  # cargar *" << id->name << endl;
            } else if (info.reg_index >= 0) {
                out << "    movq " << regs[info.reg_index] << ", %rax  # cargar parámetro " << id->name << endl;
            } else if (!info.is_global) {
                out << "    movq " << info.offset << "(%rbp), %rax  # cargar local " << id->name << endl;
            } else {
                out << "    movq " << id->name << "(%rip), %rax  # cargar global " << id->name << endl;
            }
            // --- OPERACIÓN ---
            switch (exp->assign_op) {
                case MINUS_EQUAL_OP:
                    out << "    subq %rcx, %rax\n";
                    break;
                case MULTIPLY_EQUAL_OP:
                    out << "    imulq %rcx, %rax\n";
                    break;
                case DIVIDE_EQUAL_OP:
                    out << "    cqo\n";
                    out << "    idivq %rcx\n";
                    break;
                case MODULO_EQUAL_OP:
                    out << "    cqo\n";
                    out << "    idivq %rcx\n";
                    out << "    movq %rdx, %rax\n";
                    break;
                case PLUS_EQUAL_OP:
                    out << "    addq %rcx, %rax\n";
                    break;
                default:
                    break;
            }
            // --- GUARDAR EL RESULTADO ---
            if (info.is_reference && info.reg_index >= 0) {
                out << "    movq %rax, (" << regs[info.reg_index] << ")  # guardar en *" << id->name << endl;
            } else if (info.reg_index >= 0) {
                out << "    movq %rax, " << regs[info.reg_index] << "  # guardar en parámetro " << id->name << endl;
            } else if (!info.is_global) {
                out << "    movq %rax, " << info.offset << "(%rbp)  # guardar en local " << id->name << endl;
            } else {
                out << "    movq %rax, " << id->name << "(%rip)  # guardar en global " << id->name << endl;
            }
        } else {
            cerr << "Error: Asignación compuesta solo soportada para identificadores" << endl;
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
            out << "    movl $0, %ecx" << endl;
            out << "    sete %cl" << endl;
            out << "    movq %rcx, %rax" << endl;
            break;
        case UNARY_MINUS_OP:
            out << "    negq %rax" << endl;
            break;
        case UNARY_PLUS_OP:
            break;
        case PLUS_PLUS_OP: {
            if (auto id = dynamic_cast<IdentifierExp*>(exp->uexp)) {
                 VarInfo info = env->lookup(id->name);
                const char* regs[] = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"};

                if (info.is_reference && info.reg_index >= 0) {
                if (exp->is_prefix) {
                    out << "    incq %rax" << endl;
                    out << "    movq %rax, (" << regs[info.reg_index] << ")  # ++*ref" << endl;
                } else {
                    out << "    movq %rax, %rcx" << endl;
                    out << "    incq %rcx" << endl;
                    out << "    movq %rcx, (" << regs[info.reg_index] << ")  # *ref++" << endl;
                }
            } else if (info.reg_index >= 0) {
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
            } else {
                cerr << "Error: Operador ++ solo soportado para identificadores" << endl;
                exit(1);
            }
            break;
        }
        case MINUS_MINUS_OP: {
            if (auto id = dynamic_cast<IdentifierExp*>(exp->uexp)) {
                VarInfo info = env->lookup(id->name);
                const char* regs[] = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"};

                if (info.is_reference && info.reg_index >= 0) {
                    if (exp->is_prefix) {
                        out << "    decq %rax" << endl;
                        out << "    movq %rax, (" << regs[info.reg_index] << ")  # --*ref" << endl;
                    } else {
                        out << "    movq %rax, %rcx" << endl;
                        out << "    decq %rcx" << endl;
                        out << "    movq %rcx, (" << regs[info.reg_index] << ")  # *ref--" << endl;
                    }
                } else if (info.reg_index >= 0) {
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
            } else {
                cerr << "Error: Operador -- solo soportado para identificadores" << endl;
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
                int offset = env->lookup(id->name).offset;
                out << "    leaq " << offset << "(%rbp), %rax  # &" << id->name << endl;
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
    // Evaluar operando izquierdo
    exp->left->accept(this);
    out << "    pushq %rax" << endl;

    // Evaluar operando derecho
    exp->right->accept(this);
    out << "    movq %rax, %rcx" << endl;
    out << "    popq %rax" << endl;
    out << "    # Operación binaria: " << Exp::binopToChar(exp->op) << endl;
    switch (exp->op) {
        case PLUS_OP:
            out << "    addq %rcx, %rax" << endl;
            break;
        case MINUS_OP:
            out << "    subq %rcx, %rax" << endl;
            break;
        case MULT_OP:
            out << "    imulq %rcx, %rax" << endl;
            break;
        case DIV_OP:
            out << "    cqo" << endl;
            out << "    idivq %rcx" << endl;
            break;
        case MOD_OP:
            out << "    cqo" << endl;
            out << "    idivq %rcx" << endl;
            out << "    movq %rdx, %rax" << endl;
            break;
        case EQUAL_OP:
            out << "    cmpq %rcx, %rax" << endl;
            out << "    movl $0, %eax" << endl;
            out << "    sete %al" << endl;
            out << "    movzbq %al, %rax" << endl;
            break;
        case NOT_EQUAL_OP:
            out << "    cmpq %rcx, %rax" << endl;
            out << "    movl $0, %eax" << endl;
            out << "    setne %al" << endl;
            out << "    movzbq %al, %rax" << endl;
            break;
        case LESS_THAN_OP:
            out << "    cmpq %rcx, %rax" << endl;
            out << "    movl $0, %eax" << endl;
            out << "    setl %al" << endl;
            out << "    movzbq %al, %rax" << endl;
            break;
        case GREATER_THAN_OP:
            out << "    cmpq %rcx, %rax" << endl;
            out << "    movl $0, %eax" << endl;
            out << "    setg %al" << endl;
            out << "    movzbq %al, %rax" << endl;
            break;
        case LESS_EQUAL_OP:
            out << "    cmpq %rcx, %rax" << endl;
            out << "    movl $0, %eax" << endl;
            out << "    setle %al" << endl;
            out << "    movzbq %al, %rax" << endl;
            break;
        case GREATER_EQUAL_OP:
            out << "    cmpq %rcx, %rax" << endl;
            out << "    movl $0, %eax" << endl;
            out << "    setge %al" << endl;
            out << "    movzbq %al, %rax" << endl;
            break;
        case LOGICAL_AND_OP: {
            int label_false = cantidad++;
            int label_end = cantidad++;
            out << "    testq %rax, %rax" << endl;
            out << "    jz .Lfalse" << label_false << endl;
            out << "    testq %rcx, %rcx" << endl;
            out << "    movl $1, %eax" << endl;
            out << "    jnz .Lend" << label_end << endl;
            out << ".Lfalse" << label_false << ":" << endl;
            out << "    movl $0, %eax" << endl;
            out << ".Lend" << label_end << ":" << endl;
            break;
        }
        case LOGICAL_OR_OP: {
            int label_true = cantidad++;
            int label_end = cantidad++;
            out << "    testq %rax, %rax" << endl;
            out << "    jnz .Ltrue" << label_true << endl;
            out << "    testq %rcx, %rcx" << endl;
            out << "    movl $0, %eax" << endl;
            out << "    jz .Lend" << label_end << endl;
            out << ".Ltrue" << label_true << ":" << endl;
            out << "    movl $1, %eax" << endl;
            out << ".Lend" << label_end << ":" << endl;
            break;
        }
        case ASSIGN_OP: {
            // Para asignación, necesitamos obtener la dirección del operando izquierdo
            if (auto id = dynamic_cast<IdentifierExp*>(exp->left)) {
                if (!env->check(id->name)) {
                    cerr << "Error: Variable no declarada: " << id->name << endl;
                    exit(1);
                }
                int offset = env->lookup(id->name).offset;
                out << "    movq %rcx, " << offset << "(%rbp)  # " << id->name << " = valor" << endl;
                out << "    movq %rcx, %rax" << endl;
            }
            break;
        }
        case PLUS_EQUAL_OP:
        case MINUS_EQUAL_OP:
        case MULTIPLY_EQUAL_OP:
        case DIVIDE_EQUAL_OP:
        case MODULO_EQUAL_OP: 
        
        default:
            out << "    # Operador binario no implementado: " << exp->op << endl;
            break;
    }

    return 0;
}


int GenCodeVisitor::visit(ArrayAccessExp* exp) {
    // Evaluar índice
    exp->index->accept(this);
    out << "    pushq %rax" << endl;

    // Evaluar array base
    exp->array->accept(this);
    out << "    popq %rcx" << endl;

    // Calcular offset: base + index * 8
    out << "    leaq (%rax,%rcx,8), %rax" << endl;
    out << "    movq (%rax), %rax" << endl;

    return 0;
}

int GenCodeVisitor::visit(MemberAccessExp* exp) {
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
        // p->campo: %rax ya tiene el puntero base
        out << "    addq $" << member_offset << ", %rax  # offset del miembro " << exp->member_name << endl;
        out << "    movq (%rax), %rax" << endl;
    } else if (is_local_struct) {
        // p.campo: acceso directo en el stack
               out << "    movq " << (base_offset + (member_offset)) << "(%rbp), %rax  # " << exp->member_name << " de struct local" << endl;
    } else {
        // Caso general
        out << "    addq $" << member_offset << ", %rax  # offset del miembro " << exp->member_name << endl;
        out << "    movq (%rax), %rax" << endl;
    }
    return 0;
}

int GenCodeVisitor::visit(ParenExp* exp) {
    return exp->inner->accept(this);
}

int GenCodeVisitor::visit(ArrayInitializerExp* exp) {
    // Asumimos que el array ya ha sido declarado y tiene un tamaño fijo
    out << "    leaq array_" << cantidad++ << "(%rip), %rax" << endl; // Label único para el array
    for (size_t i = 0; i < exp->elements.size(); ++i) {
        exp->elements[i]->accept(this);
        out << "    movq %rax, " << (i * 8) << "(%rbp)  # Inicializando elemento " << i << endl;
    }
    return 0;
}




void GenCodeVisitor::visit(PrintfStatement* stm) {
    // Generar string de formato
    static int fmt_count = 0;
    string fmt_label = "printf_fmt_" + to_string(fmt_count++);
    
    out << ".section .rodata" << endl;
    out << fmt_label << ": .string " << stm->format_string  << endl;
    out << ".text" << endl;
    
    // Cargar dirección del formato
    out << "    leaq " << fmt_label << "(%rip), %rdi" << endl;
    
    // Procesar argumentos
    const char* arg_regs[] = {"%rsi", "%rdx", "%rcx", "%r8", "%r9"};
    int reg_index = 0;
    int stack_args = 0;
    
    for (auto arg : stm->arguments) {
        arg->accept(this);  // Resultado en %rax
        
        if (reg_index < 5) {
            out << "    movq %rax, " << arg_regs[reg_index] << endl;
            reg_index++;
        } else {
            out << "    pushq %rax" << endl;
            stack_args++;
        }
    }
    
    // Para variádicas, RAX = número de registros vectoriales usados (0)
    out << "    movl $0, %eax" << endl;
    out << "    call printf" << endl;
    
    // Limpiar argumentos de pila
    if (stack_args > 0) {
        out << "    addq $" << (stack_args * 8) << ", %rsp" << endl;
    }
}

void GenCodeVisitor::visit(IfStatement* stm) {
    if (!stm) return;

    // 1. Generar etiquetas únicas para este if-else (usando stm->id)
    int label_else = stm->id * 2;      // Ej: .Lelse2
    int label_end = stm->id * 2 + 1;   // Ej: .Lendif3

    // 2. Generar código para la condición
    stm->condition->accept(this);
    out << "    testq %rax, %rax" << endl;
    out << "    jz .Lelse" << label_else << endl;  // Saltar a "else" si la condición es falsa

    // 3. Cuerpo del "if"
    if (stm->statements)
        stm->statements->accept(this);

    // 4. Si hay "else/else if", saltar al final para evitar ejecutarlos
    if (stm->elsChain) {
        out << "    jmp .Lendif" << label_end << endl;
    }

    // 5. Etiqueta para el "else" (compartida por else if/else)
    out << ".Lelse" << label_else << ":" << endl;

    // 6. Generar código para la cadena else/else if
    if (stm->elsChain) {
        stm->elsChain->accept(this);
    }

    // 7. Etiqueta de cierre (solo si hubo else/else if)
    if (stm->elsChain) {
        out << ".Lendif" << label_end << ":" << endl;
    }
}

void GenCodeVisitor::visit(ElseIfStatement* stm) {
    if (!stm) return;

    if (stm->tipo == ElseIfStatement::ELSE_IF) {
        // Obtener el id del IfStatement padre (asumimos que stm->parentIfId existe)
        int label_else = stm->parentId * 2;    // Misma etiqueta que el if padre
        int label_end = stm->parentId * 2 + 1;

        // 1. Generar código para la condición
        stm->condition->accept(this);
        out << "    testq %rax, %rax" << endl;
        out << "    jz .Lelse" << label_else << endl;  // Saltar al siguiente "else" si es falso

        // 2. Cuerpo del "else if"
        if (stm->body)
            stm->body->accept(this);

        // 3. Si hay más condiciones, saltar al final
        if (stm->nextChain) {
            out << "    jmp .Lendif" << label_end << endl;
        }

        // 4. Etiqueta compartida para el siguiente "else"
        out << ".Lelse" << label_else << ":" << endl;

        // 5. Procesar siguiente condición en la cadena (else if/else)
        if (stm->nextChain) {
            stm->nextChain->accept(this);
        }
    }
    else {  // ELSE simple
        if (stm->body) {
            stm->body->accept(this);  // No necesita etiquetas, es el último caso
        }
    }
}

void GenCodeVisitor::visit(WhileStatement* stm) {
    int label_start = cantidad++;
    int label_end = cantidad++;

    out << ".Lwhile" << label_start << ":" << endl;
    stm->condition->accept(this);
    out << "    testq %rax, %rax" << endl;
    out << "    jz .Lendwhile" << label_end << endl;

    if (stm->b)
        stm->b->accept(this);

    out << "    jmp .Lwhile" << label_start << endl;
    out << ".Lendwhile" << label_end << ":" << endl;
}

void GenCodeVisitor::visit(ForStatement* stm) {
    int label_start = cantidad++;
    int label_end = cantidad++;

    // Inicialización
    if (stm->init)
        stm->init->accept(this);

    out << ".Lfor" << label_start << ":" << endl;

    // Condición
    if (stm->condition) {
        stm->condition->accept(this);
        out << "    testq %rax, %rax" << endl;
        out << "    jz .Lendfor" << label_end << endl;
    }

    // Cuerpo
    if (stm->b)
        stm->b->accept(this);

    // Actualización
    if (stm->update)
        stm->update->accept(this);

    out << "    jmp .Lfor" << label_start << endl;
    out << ".Lendfor" << label_end << ":" << endl;
}

void GenCodeVisitor::visit(ExpressionStatement* stm) {
    if (stm->expression)
        stm->expression->accept(this);
}

void GenCodeVisitor::visit(VarDec* stm) {
    for (size_t i = 0; i < stm->vars.size(); ++i) {
        string var_name = stm->vars[i];
        Type* var_type = stm->types[i];
        bool is_char = (var_type->type_name == "char");
        bool is_bool = (var_type->type_name == "bool");
        bool is_ptr = var_type->is_pointer;
        bool is_array = var_type->is_array;
        bool is_reference = var_type->is_reference;

        int var_size = is_char || is_bool ? 1 : 8;
        string mov_inst = is_char || is_bool ? "movb" : "movq";
        string reg = is_char || is_bool ? "%al" : "%rax";
        int current_offset = env->lookup(var_name).offset;
        if (is_array && var_type->array_size) {
            var_type->array_size->accept(this);

            if (is_char) {
                out << "    # Reservando arreglo de char[" << var_type->array_size << "]\n";
            } else {
                out << "    imulq $8, %rax  # Elementos * 8 bytes\n";
            }

            out << "    movq %rax, %rcx  # Guardar tamaño total\n";
            out << "    subq %rcx, %rsp  # Reservar espacio en stack\n";
            out << "    movq %rsp, " << current_offset << "(%rbp)  # Guardar puntero al arreglo\n";

            if (stm->initializers[i]) {
                stm->initializers[i]->accept(this);
            } else {
                out << "    movq %rsp, %rdi\n";
                out << "    xorq %rax, %rax\n";
                out << "    rep stosb\n";
            }

            current_offset -= 16;
            continue;
        }

        env->add_var(var_name, current_offset, var_type->type_name, is_ptr, is_array,is_reference, -1,false);
        int current = env->lookup(var_name).offset;
        if (auto struct_init = dynamic_cast<StructInitializerExp*>(stm->initializers[i])) {
            struct_init->accept(this, current);
        }
        else if (stm->initializers[i]) {
            stm->initializers[i]->accept(this);
            out << "    " << mov_inst << " " << reg << ", " << current_offset << "(%rbp)  # " << var_name << "\n";

            if (is_bool) {
                out << "    andb $1, " << current_offset << "(%rbp)  # Asegurar 0/1\n";
            }
        } else {
            if (is_ptr) {
                out << "    movq $0, " << current_offset << "(%rbp)  # NULL para puntero\n";
            } else {
                out << "    " << mov_inst << " $0, " << current_offset << "(%rbp)  # Inicializar a 0\n";
            }
        }

        current_offset -= var_size;
        if (var_size < 8) {
            int padding = (8 - (abs(current_offset) % 8) % 8);
            if (padding > 0) {
                current_offset -= padding;
                out << "    # Padding de " << padding << " bytes para alineación\n";
            }
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
    env->add_var(dec->var_name, 0, dec->type->type_name, is_ptr, is_array, is_reference, -1, true); // offset 0 para globals
}

void GenCodeVisitor::visit(GlobalVarDecList* decList) {
    for (auto dec : decList->global_vardecs) {
        dec->accept(this);
    }
}

void GenCodeVisitor::visit(Parameter* param) {
    // Los parámetros se manejan en la función
    static int param_offset = 16; // Empezar desde 16(%rbp) para parámetros
    env->add_var(param->name, param_offset, param->type->type_name, param->type->is_pointer, param->type->is_array, -1);
    param_offset += 8;
}

void GenCodeVisitor::visit(ParameterList* paramList) {
    for (auto param : paramList->parameters) {
        param->accept(this);
    }
}

void GenCodeVisitor::visit(StatementList* stm) {
    for (auto s : stm->stms) {
        s->accept(this);
    }
}

void GenCodeVisitor::visit(Body* b) {
       int current_offset = 0;
    for (auto elem : b->elements) {
        if (auto vardec = dynamic_cast<VarDec*>(elem)) {
            for (size_t i = 0; i < vardec->vars.size(); ++i) {
                int var_size = 8;
                if (vardec->types[i]->type_name.find("struct") == 0) {
                    std::string struct_name = vardec->types[i]->type_name.substr(7);
                    var_size = env->get_struct_size(struct_name);
                }
                current_offset -= var_size;
                env->add_var(
                    vardec->vars[i],
                    current_offset,
                    vardec->types[i]->type_name,
                    vardec->types[i]->is_pointer,
                    vardec->types[i]->is_array
                );
                out<<"#offset calculado de "<<current_offset<<" para la variable "<<vardec->vars[i]<<endl;
            }
        }
    }
    // 2. Generar código para inicializaciones y sentencias en orden
    for (auto elem : b->elements) {
        elem->accept(this);
    }
}


void GenCodeVisitor::visit(Function* func) {
    // Prologo
    out << ".globl " << func->name << endl;
    out << func->name << ":" << endl;
    out << "    pushq %rbp" << endl;
    out << "    movq %rsp, %rbp" << endl;

    // Espacio para variables locales
    int stack_space = 0;
    if (func->body) {
        for (auto elem : func->body->elements) {
            if (auto vardec = dynamic_cast<VarDec*>(elem)) {
                stack_space += vardec->vars.size() * 8;
            }
        }
    }
    if (stack_space > 0) {
        out << "    subq $" << stack_space << ", %rsp" << endl;
    }

    // Registrar parámetros solo en el environment, NO en el stack
    FunctionInfo func_info;
    func_info.return_type = func->return_type->type_name;
    func_info.stack_size = stack_space;

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
            env->add_var(param->name, 0, param->type->type_name, param->type->is_pointer, param->type->is_array, param->is_reference, param_info.reg_index,false);
            out << "# Registrando variable: " << param->name
          << " reg_index: " << param_info.reg_index
          << " offset: " << 0
          << " is_global: false" 
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
}

void GenCodeVisitor::visit(ReturnStatement* stm) {
    if (stm->return_value)
        stm->return_value->accept(this);

    out << "    leave" << endl;
    out << "    ret" << endl;
}

int GenCodeVisitor::visit(FunctionCallExp* exp) {
    if (!env->has_function(exp->function_name)) {
        cerr << "Error: Función '" << exp->function_name << "' no declarada" << endl;
        exit(1);
    }
    auto func_info = env->get_function(exp->function_name);
    
    const char* regs[] = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"};
    int stack_args = 0;
    
    for (int i = 0; i < exp->arguments.size(); ++i) {
        auto& param_info = func_info.params[i];
        if (param_info.is_reference) {
            if (auto id = dynamic_cast<IdentifierExp*>(exp->arguments[i])) {
                int var_offset = env->lookup(id->name).offset;
                out << "    leaq " << var_offset << "(%rbp), %rax  # Dirección de " << id->name << endl;
            } else if (auto unary = dynamic_cast<UnaryExp*>(exp->arguments[i])) {
                if (unary->op == DEREFERENCE_OP) {
                    unary->uexp->accept(this);
                }
            } else {
                cerr << "Error: Argumento por referencia debe ser variable" << endl;
                exit(1);
            }
        } else {
            exp->arguments[i]->accept(this);
        }

        if (i < 6) {
            out << "    movq %rax, " << regs[i] << "\n";
        } else {
            out << "    pushq %rax\n";
            stack_args++;
        }
    }

    if ((stack_args % 2) != 0) {
        out << "    subq $8, %rsp" << endl;
    }

    out << "    call " << exp->function_name << endl;

    // Limpiar argumentos de la pila
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
            // Determinar el tamaño del tipo del miembro
            int member_size = 8; // Tamaño por defecto (64 bits)
            if (member->types[0]->type_name == "char" || member->types[0]->type_name == "bool") {
                member_size = 1;
            } else if (member->types[0]->type_name == "int") {
                member_size = 4;
            } else if (env->has_struct(member->types[0]->type_name)) {
                member_size = env->get_struct_size(member->types[0]->type_name);
            }

            // Aplicar alineación (normalmente al tamaño de palabra)
            int alignment = 8;
            offset = (offset + alignment - 1) & ~(alignment - 1);

            for (auto& var : member->vars) {
                info.fields[var] = {member->types[0]->type_name, member->types[0]->is_pointer, member->types[0]->is_array};
                info.offsets[var] = offset;
                out << "# Miembro de estructura: " << var << " (tipo: " << member->types[0]->type_name 
                    << ", offset: " << offset << ", tamaño: " << member_size << ")" << endl;

                // Para arrays, usar el tamaño especificado o marcarlo como array sin tamaño
                if (member->types[0]->is_array) {
                    if (member->types[0]->array_size) {
                        member->types[0]->array_size->accept(this);
                        out << "    imulq $" << member_size << ", %rax" << endl;
                        out << "    movq %rax, %rcx" << endl;
                        member_size = -1; // Marcador para array con tamaño dinámico
                    } else {
                        // Array sin tamaño (como parámetro)
                        member_size = 8; // Tratar como puntero
                    }
                }

                offset += member_size;
            }
        }
    }

    info.size = (offset + 7) & ~7;
    env->add_struct(structDecl->struct_name, info);

    // Generar información de debug (opcional)
    for (const auto& field : info.offsets) {
        out << "#   " << field.first << " : offset " << field.second << endl;
    }
}


void GenCodeVisitor::visit(StructDeclarationList* structList) {
    for (auto structDecl : structList->structs) {
        structDecl->accept(this);
    }
}

void GenCodeVisitor::visit(Include* inc) {
}

void GenCodeVisitor::visit(IncludeList* incList) {
}

void GenCodeVisitor::visit(Type* type) {
}


int GenCodeVisitor::visit(StructInitializerExp* exp, int base_offset) {
    out<<"#offset se paso con "<<base_offset<<endl;
    if (!env->has_struct(exp->struct_name)) {
        cerr << "Error: Estructura '" << exp->struct_name << "' no declarada" << endl;
        exit(1);
    }
    StructInfo info = env->get_struct(exp->struct_name);

    std::vector<std::string> field_names;
    for (const auto& kv : info.offsets) {
        field_names.push_back(kv.first);
    }
    std::sort(field_names.begin(), field_names.end(),
        [&](const std::string& a, const std::string& b) {
            return info.offsets[a] < info.offsets[b];
        });

   for (size_t i = 0; i < exp->members.size() && i < field_names.size(); ++i) {
        int field_offset = info.offsets[field_names[i]];
        exp->members[i].second->accept(this);
        out << "    movq %rax, " << (base_offset + field_offset) << "(%rbp)  # Inicializando miembro " << field_names[i] << endl;
    }
    return 0;
}

int GenCodeVisitor::visit(StructInitializerExp* exp) {
    // Si se llama esta versión, probablemente es un error de uso en generación de código.
    // Puedes dejarlo vacío, lanzar error, o delegar a la versión con offset base 0.
    out<<"#entra a este visitor"<<endl;
    return visit(exp, 0);
}