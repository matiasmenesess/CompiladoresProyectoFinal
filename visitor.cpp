//
// Created by zamirlm on 6/21/25.
//

#include "visitor.h"
#include <iostream>

#include "expression.h"

#include "visitor.h"

#include <unordered_map>

using namespace std;


int Include::accept(Visitor *visitor) {
    visitor->visit(this);
    return 0;
}
int IncludeList::accept(Visitor *visitor) {
    visitor->visit(this);
    return 0;
}

int LineComment::accept(Visitor *visitor) {
    visitor->visit(this);
    return 0;
}

int BlockComment::accept(Visitor *visitor) {
    visitor->visit(this);
    return 0;
}
int Comment::accept(Visitor *visitor) {
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

int AssignStatement::accept(Visitor *visitor) {
    visitor->visit(this);
    return 0;
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

void PrintVisitor::visit(Include* inc) {
    cout << "#include " << (inc->is_system_header ? "<" : "\"") << inc->header_name << (inc->is_system_header ? ">" : "\"") << endl;
}


