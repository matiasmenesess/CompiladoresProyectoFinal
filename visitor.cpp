
//
// Created by zamirlm on 6/21/25.
//
#include <stdexcept>
#include "visitor.h"
#include <iostream>
#include "expression.h"
#include <unordered_map>
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


void PrintVisitor::visit(Type* type) {
    cout << type->type_name;
    if (type->is_pointer) {
        cout << "*";
    }
    if (type->is_array && type->array_size) {
        cout << "[";
        type->array_size->accept(this);
        cout << "]";
    }
}

int PrintVisitor::visit(BinaryExp* exp) {
    exp->left->accept(this);
    cout << " " << Exp::binopToChar(exp->op) << " ";
    exp->right->accept(this);
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
    cout << "\"" << exp->value << "\"";
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
        stm->init->type->accept(this);
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

void PrintVisitor::visit(VarDec* vardec) {
    printIndent();
    vardec->type->accept(this);
    cout << " ";
    for (size_t i = 0; i < vardec->vars.size(); ++i) {
        cout << vardec->vars[i];
        if (!vardec->initializers.empty() && i < vardec->initializers.size()) {
            cout << " = ";
            vardec->initializers[i]->accept(this);
        }
        if (i < vardec->vars.size() - 1) {
            cout << ", ";
        }
    }
    cout << ";" << endl;
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
    cout << " " << param->name;
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
    if (b->vardecs) {
        b->vardecs->accept(this);
    }
    if (b->slist) {
        b->slist->accept(this);
    }
}

void PrintVisitor::visit(Function* func) {
    if (!func) return;  // Verificación de null

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
            member->type->accept(this);
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

// Haremos el gencode

GenCodeVisitor::GenCodeVisitor(Environment* env) : env(new Environment()){};
GenCodeVisitor::~GenCodeVisitor() {
    delete env;
}// ...existing code...

void GenCodeVisitor::gencode(Program* program) {
    cout << ".data" << endl;
    cout << "print_fmt: .string \"%ld \\n\" " << endl;
    cout << ".text " << endl;
    cout << ".globl main " << endl;
    cout << "main: " << endl;
    cout << " pushq %rbp" << endl;
    cout << " movq %rsp, %rbp" << endl;
    cout << " subq $" << program->countVars()*8 << ", %rsp" << endl;

    // Global variables
    if (program->global_declarations)
        program->global_declarations->accept(this);

    // Structs (no generan código, pero puedes registrar en env)
    if (program->struct_declarations)
        program->struct_declarations->accept(this);

    // Funciones
    if (program->functions)
        program->functions->accept(this);

    // Main
    if (program->main_function)
        program->main_function->accept(this);

    cout << " movl $0, %eax " << endl;
    cout << " leave" << endl;
    cout << " ret" << endl;
    cout << ".section .note.GNU-stack,\"\",@progbits" << endl;
}

// --- Expresiones ---

int GenCodeVisitor::visit(NumberExp* exp) {
    cout << " movl $" << exp->value << ", %eax" << endl;
    return exp->value;
}

int GenCodeVisitor::visit(CharExp* exp) {
    cout << " movb $" << (int)exp->value << ", %al" << endl;
    return exp->value;
}

int GenCodeVisitor::visit(BoolExp* exp) {
    cout << " movl $" << exp->value << ", %eax" << endl;
    return exp->value;
}

int GenCodeVisitor::visit(StringExp* exp) {
    // Asigna una etiqueta para el string y guárdala en .data si es necesario
    // Aquí solo ejemplo:
    cout << " lea string_label, %rax" << endl;
    return 0;
}

int GenCodeVisitor::visit(IdentifierExp* exp) {
    // Busca la variable en env y genera código para cargarla
    // Ejemplo: supón offset en stack
    // int offset = env->lookup(exp->name);
    // cout << " movl " << offset << "(%rbp), %eax" << endl;
    return 0;
}

int GenCodeVisitor::visit(BinaryExp* exp) {
    // Evalúa left y right, usa stack para preservar valores
    exp->left->accept(this);
    cout << " push %rax" << endl;
    exp->right->accept(this);
    cout << " pop %rcx" << endl;
    // Ejemplo para suma:
    if (exp->op == PLUS_OP)
        cout << " add %ecx, %eax" << endl;
    // Completa para otros operadores...
    return 0;
}

int GenCodeVisitor::visit(AssignExp* exp) {
    // Evalúa la derecha y asigna a la izquierda
    exp->right->accept(this);
    // Supón offset de la variable:
    // int offset = env->lookup(exp->left->name);
    // cout << " movl %eax, " << offset << "(%rbp)" << endl;
    return 0;
}

int GenCodeVisitor::visit(UnaryExp* exp) {
    exp->uexp->accept(this);
    // Aplica el operador
    // Ejemplo: negación
    if (exp->op == NEGACION_OP)
        cout << " not %eax" << endl;
    return 0;
}

int GenCodeVisitor::visit(FunctionCallExp* exp) {
    // Empuja argumentos en orden inverso
    for (int i = exp->arguments.size() - 1; i >= 0; --i) {
        exp->arguments[i]->accept(this);
        cout << " push %rax" << endl;
    }
    cout << " call " << exp->function_name << endl;
    cout << " addq $" << (exp->arguments.size() * 8) << ", %rsp" << endl;
    return 0;
}

// --- Statements ---

void GenCodeVisitor::visit(PrintfStatement* stm) {
    // Empuja argumentos y llama a printf
    for (int i = stm->arguments.size() - 1; i >= 0; --i) {
        stm->arguments[i]->accept(this);
        cout << " push %rax" << endl;
    }
    cout << " lea print_fmt(%rip), %rdi" << endl;
    cout << " call printf" << endl;
    cout << " addq $" << (stm->arguments.size() * 8) << ", %rsp" << endl;
}

void GenCodeVisitor::visit(IfStatement* stm) {
    int label_else = cantidad++;
    int label_end = cantidad++;
    stm->condition->accept(this);
    cout << " cmp $0, %eax" << endl;
    cout << " je else_" << label_else << endl;
    if (stm->statements) stm->statements->accept(this);
    cout << " jmp endif_" << label_end << endl;
    cout << "else_" << label_else << ":" << endl;
    if (stm->elsChain) stm->elsChain->accept(this);
    cout << "endif_" << label_end << ":" << endl;
}

void GenCodeVisitor::visit(ElseIfStatement* stm) {
    // Similar a IfStatement, usa labels únicos
    // ...
}

void GenCodeVisitor::visit(WhileStatement* stm) {
    int label_start = cantidad++;
    int label_end = cantidad++;
    cout << "while_" << label_start << ":" << endl;
    stm->condition->accept(this);
    cout << " cmp $0, %eax" << endl;
    cout << " je endwhile_" << label_end << endl;
    stm->b->accept(this);
    cout << " jmp while_" << label_start << endl;
    cout << "endwhile_" << label_end << ":" << endl;
}

void GenCodeVisitor::visit(ForStatement* stm) {
    int label_start = cantidad++;
    int label_end = cantidad++;
    if (stm->init) stm->init->accept(this);
    cout << "for_" << label_start << ":" << endl;
    if (stm->condition) stm->condition->accept(this);
    cout << " cmp $0, %eax" << endl;
    cout << " je endfor_" << label_end << endl;
    if (stm->b) stm->b->accept(this);
    if (stm->update) stm->update->accept(this);
    cout << " jmp for_" << label_start << endl;
    cout << "endfor_" << label_end << ":" << endl;
}

void GenCodeVisitor::visit(ExpressionStatement* stm) {
    if (stm->expression) stm->expression->accept(this);
}

void GenCodeVisitor::visit(ReturnStatement* stm) {
    if (stm->return_value) stm->return_value->accept(this);
    cout << " leave" << endl;
    cout << " ret" << endl;
}

void GenCodeVisitor::visit(VarDec* stm) {
    // Reserva espacio y registra en env
    for (size_t i = 0; i < stm->vars.size(); ++i) {
        // int offset = ...; // calcula offset en stack
        // env->add_var(stm->vars[i], offset, stm->type->type_name);
        if (stm->initializers[i]) {
            stm->initializers[i]->accept(this);
            // cout << " movl %eax, " << offset << "(%rbp)" << endl;
        }
    }
}

void GenCodeVisitor::visit(VarDecList* stm) {
    for (auto vardec : stm->vardecs) {
        vardec->accept(this);
    }
}

void GenCodeVisitor::visit(GlobalVarDec* dec) {
    // Genera en .data
    cout << dec->var_name << ": .quad 0" << endl;
    if (dec->initializer) {
        // Puedes inicializar aquí si lo deseas
    }
}

void GenCodeVisitor::visit(GlobalVarDecList* decList) {
    for (auto dec : decList->global_vardecs) {
        dec->accept(this);
    }
}

void GenCodeVisitor::visit(Parameter* param) {
    // Puedes registrar en env el offset del parámetro
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
    if (b->vardecs) b->vardecs->accept(this);
    if (b->slist) b->slist->accept(this);
}

void GenCodeVisitor::visit(Function* func) {
    cout << func->name << ":" << endl;
    cout << " pushq %rbp" << endl;
    cout << " movq %rsp, %rbp" << endl;
    // Reserva espacio para variables locales
    // env->add_level();
    if (func->body) func->body->accept(this);
    // env->remove_level();
    cout << " leave" << endl;
    cout << " ret" << endl;
}

void GenCodeVisitor::visit(FunctionList* funcList) {
    for (auto func : funcList->functions) {
        func->accept(this);
    }
}

void GenCodeVisitor::visit(MainFunction* mainFunc) {
    if (mainFunc->body) mainFunc->body->accept(this);
}

void GenCodeVisitor::visit(StructDeclaration* structDecl) {
    // Registra el struct en env
    StructInfo info;
    for (auto member : structDecl->members->vardecs) {
        for (auto& var : member->vars) {
            info.fields[var] = member->type->type_name;
        }
    }
    env->add_struct(structDecl->struct_name, info);
}

void GenCodeVisitor::visit(StructDeclarationList* structList) {
    for (auto structDecl : structList->structs) {
        structDecl->accept(this);
    }
}

void GenCodeVisitor::visit(Include* inc) { /* nada para assembly */ }
void GenCodeVisitor::visit(IncludeList* incList) { /* nada para assembly */ }
void GenCodeVisitor::visit(Type* type) { /* nada para assembly */ }
int GenCodeVisitor::visit(ArrayAccessExp* exp) { return 0; }
int GenCodeVisitor::visit(MemberAccessExp* exp) { return 0; }
int GenCodeVisitor::visit(ParenExp* exp) { return exp->inner->accept(this); }

// ...existing code...