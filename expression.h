//
// Created by zamirlm on 6/5/25.
//

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include <unordered_map>
#include <list>
#include <vector>
using namespace std;

enum BinaryOp {
    PLUS_OP,
    MINUS_OP,
    MULT_OP,
    DIV_OP,
    MOD_OP,
    EQUAL_OP,
    NOT_EQUAL_OP,
    LESS_THAN_OP,
    GREATER_THAN_OP,
    LESS_EQUAL_OP,
    GREATER_EQUAL_OP,
    LOGICAL_AND_OP,
    LOGICAL_OR_OP,
    ASSIGN_OP,
    PLUS_EQUAL_OP,
    MINUS_EQUAL_OP,
    MULTIPLY_EQUAL_OP,
    DIVIDE_EQUAL_OP,
    MODULO_EQUAL_OP,
    MEMBER_ACCESS_OP,
    POINTER_ACCESS_OP,
};

enum UnaryOp {
    NEGACION_OP,
    PLUS_PLUS_OP,
    MINUS_MINUS_OP,
    DEREFERENCE_OP,
    ADDRESS_OF_OP,
    UNARY_PLUS_OP,
    UNARY_MINUS_OP,
};

class Body;
class Exp;
class Stm;

class ImpValue {
public:
    string tipo;
    int valor;
    bool bool_value;
    ImpValue(string tipo, int valor, bool bol);
    ImpValue();
    ~ImpValue();
};

class Exp {
public:
    virtual ~Exp() = 0;
    static string binopToChar(BinaryOp op);
    static string unaryToChar(UnaryOp op);
};

class Include {
public:
    string header_name;
    bool is_system_header;
    Include(string header, bool system = false);
    ~Include();
};

class IncludeList {
public:
    list<Include*> includes;
    IncludeList();
    void add(Include* inc);
    ~IncludeList();
};

class Comment {
public:
    string text;
    Comment(string text);
    virtual ~Comment() = 0;
};

class LineComment : public Comment {
public:
    LineComment(string text);
    ~LineComment();
};

class BlockComment : public Comment {
public:
    BlockComment(string text);
    ~BlockComment();
};

class Type {
public:
    string type_name;
    bool is_pointer;
    bool is_array;
    Exp* array_size;

    Type(string name);
    Type(string name, bool pointer);
    Type(string name, Exp* size);
    ~Type();
};

class IFExp : public Exp {
public:
    Exp *cond, *left, *right;
    IFExp(Exp *cond, Exp* l, Exp* r);
    ~IFExp();
};

class BinaryExp : public Exp {
public:
    Exp *left, *right;
    string type;
    BinaryOp op;
    BinaryExp(Exp* l, Exp* r, BinaryOp op);
    ~BinaryExp();
};

class AssignExp : public Exp {
public:
    Exp* left;
    Exp* right;
    BinaryOp assign_op;
    AssignExp(Exp* l, Exp* r, BinaryOp op);
    ~AssignExp();
};

class UnaryExp : public Exp {
public:
    Exp* uexp;
    string type;
    UnaryOp op;
    bool is_prefix;
    UnaryExp(Exp* uexp, UnaryOp op, bool prefix = true);
    ~UnaryExp();
};

class NumberExp : public Exp {
public:
    int value;
    NumberExp(int v);
    ~NumberExp();
};

class BoolExp : public Exp {
public:
    int value;
    BoolExp(bool v);
    ~BoolExp();
};

class CharExp : public Exp {
public:
    char value;
    CharExp(char v);
    ~CharExp();
};

class StringExp : public Exp {
public:
    string value;
    StringExp(string v);
    ~StringExp();
};

class IdentifierExp : public Exp {
public:
    std::string name;
    IdentifierExp(const std::string& n);
    ~IdentifierExp();
};

class FunctionCallExp : public Exp {
public:
    string function_name;
    list<Exp*> arguments;
    FunctionCallExp(string name);
    void add_argument(Exp* arg);
    ~FunctionCallExp();
};

class ArrayAccessExp : public Exp {
public:
    Exp* array;
    Exp* index;
    ArrayAccessExp(Exp* arr, Exp* idx);
    ~ArrayAccessExp();
};

class MemberAccessExp : public Exp {
public:
    Exp* object;
    string member_name;
    bool is_pointer;
    MemberAccessExp(Exp* obj, string member, bool ptr_access = false);
    ~MemberAccessExp();
};

class ParenExp : public Exp {
public:
    Exp* inner;
    ParenExp(Exp* exp);
    ~ParenExp();
};

class Stm {
public:
    virtual ~Stm() = 0;
};

class AssignStatement : public Stm {
public:
    std::string id;
    Exp* rhs;
    BinaryOp assign_op;
    AssignStatement(std::string id, Exp* e, BinaryOp op = ASSIGN_OP);
    ~AssignStatement();
};

class PrintStatement : public Stm {
public:
    Exp* e;
    PrintStatement(Exp* e);
    ~PrintStatement();
};

class PrintfStatement : public Stm {
public:
    string format_string;
    list<Exp*> arguments;
    PrintfStatement(string format);
    void add_argument(Exp* arg);
    ~PrintfStatement();
};

class IfStatement : public Stm {
public:
    struct ConditionalBlock {
        Exp* condition;
        Body* body;
    };

    std::vector<ConditionalBlock> blocks;
    int id;
    int counter;
    IfStatement(Exp* cond, Body* thenBody);
    void addBlock(Exp* cond, Body* body);
    void addElse(Body* elseBody);
    ~IfStatement();
};
class WhileStatement : public Stm {
public:
    Exp* condition;
    Body* b;
    int id;
    int counter;
    WhileStatement(Exp* condition, Body* b);
    ~WhileStatement();
};

class ForStatement : public Stm {
public:
    Exp* init;
    Exp* condition;
    Exp* update;
    Body* b;
    int id;
    int counter;
    ForStatement(Exp* init, Exp* condition, Exp* update, Body* b);
    ~ForStatement();
};

class ExpressionStatement : public Stm {
public:
    Exp* expression;
    ExpressionStatement(Exp* exp);
    ~ExpressionStatement();
};

class ReturnStatement : public Stm {
public:
    Exp* return_value;
    ReturnStatement(Exp* value = nullptr);
    ~ReturnStatement();
};

class VarDec {
public:
    Type* type;
    list<string> vars;
    list<Exp*> initializers;
    VarDec(Type* type, list<string> vars);
    void add_initializer(Exp* init);
    ~VarDec();
};

class VarDecList {
public:
    list<VarDec*> vardecs;
    VarDecList();
    void add(VarDec* vardec);
    ~VarDecList();
};

class GlobalVarDec {
public:
    Type* type;
    string var_name;
    Exp* initializer; // for global initialization
    GlobalVarDec(Type* type, string name, Exp* init = nullptr);
    ~GlobalVarDec();
};

class GlobalVarDecList {
public:
    list<GlobalVarDec*> global_vardecs;
    GlobalVarDecList();
    void add(GlobalVarDec* vardec);
    ~GlobalVarDecList();
};

class Parameter {
public:
    Type* type;
    string name;
    Parameter(Type* type, string name);
    ~Parameter();
};

class ParameterList {
public:
    list<Parameter*> parameters;
    ParameterList();
    void add(Parameter* param);
    ~ParameterList();
};

class StatementList {
public:
    list<Stm*> stms;
    StatementList();
    void add(Stm* stm);
    ~StatementList();
};

class Body {
public:
    VarDecList* vardecs;
    StatementList* slist;
    Body(VarDecList* vardecs, StatementList* stms);
    ~Body();
};

class Function {
public:
    Type* return_type;
    string name;
    ParameterList* parameters;
    Body* body;
    Function(Type* ret_type, string name, ParameterList* params, Body* body);
    ~Function();
};

class FunctionList {
public:
    list<Function*> functions;
    FunctionList();
    void add(Function* func);
    ~FunctionList();
};

class MainFunction {
public:
    Body* body;
    MainFunction(Body* body);
    ~MainFunction();
};

class StructDeclaration {
public:
    string struct_name;
    VarDecList* members;
    StructDeclaration(string name, VarDecList* members);
    ~StructDeclaration();
};

class StructDeclarationList {
public:
    list<StructDeclaration*> structs;
    StructDeclarationList();
    void add(StructDeclaration* struct_decl);
    ~StructDeclarationList();
};

class Program {
public:
    IncludeList* includes;
    GlobalVarDecList* global_declarations;
    StructDeclarationList* struct_declarations;
    FunctionList* functions;
    MainFunction* main_function;

    Program(IncludeList* includes,
            GlobalVarDecList* globals,
            StructDeclarationList* structs,
            FunctionList* functions,
            MainFunction* main);
    ~Program();
};

#endif //EXPRESSION_H