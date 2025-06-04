#include <iostream>
#include "token.h"

using namespace std;

Token::Token(Type type):type(type) { text = ""; }

Token::Token(Type type, char c):type(type) { text = string(1, c); }

Token::Token(Type type, const string& source, int first, int last):type(type) {
    text = source.substr(first, last);
}

std::ostream& operator<<(std::ostream& outs, const Token& tok) {
    switch (tok.type) {
        case Token::IDENTIFIER: outs << "IDENTIFIER"; break;
        case Token::INTEGER_CONSTANT: outs << "INTEGER_CONSTANT"; break;
        case Token::FLOATING_CONSTANT: outs << "FLOATING_CONSTANT"; break;
        case Token::CHARACTER_CONSTANT: outs << "CHARACTER_CONSTANT"; break;
        case Token::STRING_LITERAL: outs << "STRING_LITERAL"; break;

        case Token::PLUS: outs << "PLUS"; break;
        case Token::MINUS: outs << "MINUS"; break;
        case Token::MULTIPLY: outs << "MULTIPLY"; break;
        case Token::DIVIDE: outs << "DIVIDE"; break;
        case Token::MODULO: outs << "MODULO"; break;

        case Token::ASSIGN: outs << "ASSIGN"; break;
        case Token::PLUS_ASSIGN: outs << "PLUS_ASSIGN"; break;
        case Token::MINUS_ASSIGN: outs << "MINUS_ASSIGN"; break;
        case Token::MULTIPLY_ASSIGN: outs << "MULTIPLY_ASSIGN"; break;
        case Token::DIVIDE_ASSIGN: outs << "DIVIDE_ASSIGN"; break;
        case Token::MODULO_ASSIGN: outs << "MODULO_ASSIGN"; break;
        case Token::LEFT_SHIFT_ASSIGN: outs << "LEFT_SHIFT_ASSIGN"; break;
        case Token::RIGHT_SHIFT_ASSIGN: outs << "RIGHT_SHIFT_ASSIGN"; break;
        case Token::AND_ASSIGN: outs << "AND_ASSIGN"; break;
        case Token::XOR_ASSIGN: outs << "XOR_ASSIGN"; break;
        case Token::OR_ASSIGN: outs << "OR_ASSIGN"; break;

        case Token::LESS_THAN: outs << "LESS_THAN"; break;
        case Token::GREATER_THAN: outs << "GREATER_THAN"; break;
        case Token::LESS_EQUAL: outs << "LESS_EQUAL"; break;
        case Token::GREATER_EQUAL: outs << "GREATER_EQUAL"; break;
        case Token::EQUAL: outs << "EQUAL"; break;
        case Token::NOT_EQUAL: outs << "NOT_EQUAL"; break;

        case Token::LOGICAL_AND: outs << "LOGICAL_AND"; break;
        case Token::LOGICAL_OR: outs << "LOGICAL_OR"; break;
        case Token::LOGICAL_NOT: outs << "LOGICAL_NOT"; break;

        case Token::BITWISE_AND: outs << "BITWISE_AND"; break;
        case Token::BITWISE_OR: outs << "BITWISE_OR"; break;
        case Token::BITWISE_XOR: outs << "BITWISE_XOR"; break;
        case Token::BITWISE_NOT: outs << "BITWISE_NOT"; break;
        case Token::LEFT_SHIFT: outs << "LEFT_SHIFT"; break;
        case Token::RIGHT_SHIFT: outs << "RIGHT_SHIFT"; break;

        case Token::INCREMENT: outs << "INCREMENT"; break;
        case Token::DECREMENT: outs << "DECREMENT"; break;

        case Token::DOT: outs << "DOT"; break;
        case Token::ARROW: outs << "ARROW"; break;
        case Token::LEFT_PAREN: outs << "LEFT_PAREN"; break;
        case Token::RIGHT_PAREN: outs << "RIGHT_PAREN"; break;
        case Token::LEFT_BRACE: outs << "LEFT_BRACE"; break;
        case Token::RIGHT_BRACE: outs << "RIGHT_BRACE"; break;
        case Token::SEMICOLON: outs << "SEMICOLON"; break;
        case Token::COMMA: outs << "COMMA"; break;
        case Token::COLON: outs << "COLON"; break;
        case Token::QUESTION: outs << "QUESTION"; break;
        case Token::VOID: outs << "VOID"; break;
        case Token::CHAR: outs << "CHAR"; break;
        case Token::SHORT: outs << "SHORT"; break;
        case Token::INT: outs << "INT"; break;
        case Token::LONG: outs << "LONG"; break;
        case Token::FLOAT: outs << "FLOAT"; break;
        case Token::DOUBLE: outs << "DOUBLE"; break;
        case Token::SIGNED: outs << "SIGNED"; break;
        case Token::UNSIGNED: outs << "UNSIGNED"; break;
        case Token::IF: outs << "IF"; break;
        case Token::ELSE: outs << "ELSE"; break;
        case Token::SWITCH: outs << "SWITCH"; break;
        case Token::CASE: outs << "CASE"; break;
        case Token::DEFAULT: outs << "DEFAULT"; break;
        case Token::WHILE: outs << "WHILE"; break;
        case Token::DO: outs << "DO"; break;
        case Token::FOR: outs << "FOR"; break;
        case Token::GOTO: outs << "GOTO"; break;
        case Token::BREAK: outs << "BREAK"; break;
        case Token::CONTINUE: outs << "CONTINUE"; break;
        case Token::RETURN: outs << "RETURN"; break;
        case Token::STRUCT: outs << "STRUCT"; break;
        case Token::UNION: outs << "UNION"; break;
        case Token::CONST: outs << "CONST"; break;
        case Token::VOLATILE: outs << "VOLATILE"; break;
        case Token::SIZEOF: outs << "SIZEOF"; break;
        case Token::INCLUDE: outs << "INCLUDE"; break;
        case Token::HEADER_NAME: outs << "HEADER_NAME"; break;
        case Token::ELLIPSIS: outs << "ELLIPSIS"; break;
        case Token::NEWLINE: outs << "NEWLINE"; break;
        case Token::WHITESPACE: outs << "WHITESPACE"; break;
        case Token::COMMENT: outs << "COMMENT"; break;
        case Token::END_OF_FILE: outs << "END_OF_FILE"; break;
        case Token::ERROR: outs << "ERROR"; break;
        case Token::CAST_EXPRESSION: outs << "CAST_EXPRESSION"; break;
        case Token::POINTER_CONST: outs << "POINTER_CONST"; break;
        case Token::POINTER_VOLATILE: outs << "POINTER_VOLATILE"; break;
        case Token::ABSTRACT_DECLARATOR: outs << "ABSTRACT_DECLARATOR"; break;
        case Token::VARARGS: outs << "VARARGS"; break;
        case Token::INITIALIZER: outs << "INITIALIZER"; break;
        case Token::UNKNOWN: outs << "UNKNOWN"; break;
    }

    outs << "('" << tok.text << "')";
    return outs;
}

std::ostream& operator << ( std::ostream& outs, const Token* tok ) {
    return outs << *tok;
}