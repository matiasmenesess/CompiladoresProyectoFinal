#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <iostream>

class Token {
public:
    enum Type {
        IDENTIFIER,
        INTEGER_CONSTANT,
        CHARACTER_CONSTANT,
        STRING_LITERAL,
        FORMAT_STRING,

        INT,
        CHAR,
        VOID,
        STRUCT,

        IF,
        ELSE,
        WHILE,
        FOR,
        RETURN,
        INCLUDE,

        // Operators
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        MODULO,
        INCREMENT,
        DECREMENT,
        ASSIGN,
        PLUS_ASSIGN,
        MINUS_ASSIGN,
        MULTIPLY_ASSIGN,
        DIVIDE_ASSIGN,
        MODULO_ASSIGN,
        EQUAL,
        NOT_EQUAL,
        LESS_THAN,
        GREATER_THAN,
        LESS_EQUAL,
        GREATER_EQUAL,
        LOGICAL_AND,
        LOGICAL_OR,
        LOGICAL_NOT,

        POINTER,        // *
        ADDRESS_OF,     // &
        ARROW,          // ->

        LEFT_PAREN,
        RIGHT_PAREN,
        LEFT_BRACE,
        RIGHT_BRACE,
        LEFT_BRACKET,
        RIGHT_BRACKET,
        SEMICOLON,
        COMMA,
        COLON,

        PREPROCESSOR,
        HEADER_NAME,

        LINE_COMMENT,

        START_COMMENT_BLOCK,
        END_COMMENT_BLOCK,

        // Special
        MAIN,
        PRINTF,
        END_OF_FILE,
        ERROR,
        UNKNOWN
    };

    Type type;
    std::string text;
    size_t line;
    size_t column;

    Token(Type type, size_t line = 0, size_t column = 0);
    Token(Type type, char c, size_t line = 0, size_t column = 0);
    Token(Type type, const std::string& source, int first, int last, size_t line = 0, size_t column = 0);

    friend std::ostream& operator<<(std::ostream& outs, const Token& tok);
    friend std::ostream& operator<<(std::ostream& outs, const Token* tok);

    bool isType() const {
        return type == INT || type == CHAR || type == VOID || type == STRUCT;
    }

    bool isOperator() const {
        return (type >= PLUS && type <= LOGICAL_NOT) ||
               (type >= ASSIGN && type <= MODULO_ASSIGN);
    }

    bool isPreprocessor() const {
        return type == INCLUDE || type == PREPROCESSOR || type == HEADER_NAME;
    }
};

#endif // TOKEN_H