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

enum BinaryOp{PLUS_OP, MINUS_OP, MULT_OP, DIV_OP, MOD_OP, EQUAL_OP, NOT_EQUAL_OP, LESS_THAN_OP, GREATER_THAN_OP, LESS_EQUAL_OP, GREATER_EQUAL_OP};

class Exp {
public:
    virtual ~Exp() = 0;
    static string binopToChar(BinaryOp op);
};
class IFExp : public Exp {
public:
    Exp *cond,*left, *right;
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

class IdentifierExp : public Exp {
public:
    std::string name;
    IdentifierExp(const std::string& n);
    ~IdentifierExp();
};

class Program {
public:
};




#endif //EXPRESSION_H
