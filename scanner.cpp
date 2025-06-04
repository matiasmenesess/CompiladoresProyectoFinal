#include <iostream>
#include <cstring>
#include "token.h"
#include "scanner.h"

using namespace std;

Scanner::Scanner(const char* s):input(s),first(0), current(0) { }


bool is_white_space(char c) {
    return c == ' ' || c == '\n' || c == '\r' || c == '\t';
}
Token* Scanner::nextToken() {
    Token* token;
    while (current < input.length() &&  is_white_space(input[current]) ) current++;
    if (current >= input.length()) return new Token(Token::END_OF_FILE);
    char c  = input[current];
    first = current;

    if (c == '#') {
        current++;
        while (current < input.length() && isalpha(input[current]))
            current++;
        string directive = input.substr(first, current - first);
        if (directive == "#include") {
            token = new Token(Token::INCLUDE, directive, 0, directive.length());
        } else {
            token = new Token(Token::ERROR, directive, 0, directive.length());
        }
        return token;
    }

    if (c == '<') {
        int start = current;
        current++;
        while (current < input.length() && input[current] != '>') {
            current++;
        }
        if (current < input.length() && input[current] == '>') {
            current++;
            string header = input.substr(start, current - start);
            token = new Token(Token::HEADER_NAME, header, 0, header.length());
            return token;
        } else {
            current = start;
            c = input[current];
        }
    }

    if (c == '(') {
        int temp_pos = current + 1;
        bool is_cast = false;

        while (temp_pos < input.length() && is_white_space(input[temp_pos])) {
            temp_pos++;
        }

        if (isalpha(input[temp_pos])) {
            int type_start = temp_pos;
            while (temp_pos < input.length() && (isalnum(input[temp_pos]) || input[temp_pos] == '_')) {
                temp_pos++;
            }
            string type = input.substr(type_start, temp_pos - type_start);

            if (type == "void" || type == "char" || type == "short" || type == "int" ||
                type == "long" || type == "float" || type == "double" || type == "signed" ||
                type == "unsigned" || type == "struct" || type == "union" || type == "const" ||
                type == "volatile") {

                while (temp_pos < input.length() && is_white_space(input[temp_pos])) {
                    temp_pos++;
                }
                if (temp_pos < input.length() && input[temp_pos] == ')') {
                    is_cast = true;
                }
            }
        }

        if (is_cast) {
            while (current < input.length() && input[current] != ')') {
                current++;
            }
            if (current < input.length() && input[current] == ')') {
                current++;
                string cast_expr = input.substr(first, current - first);
                token = new Token(Token::CAST_EXPRESSION, cast_expr, first, current - first);
                return token;
            }
        }

        token = new Token(Token::LEFT_PAREN, c);
    }

    if (c == '\'') {
        current++;
        if (current < input.length()) {
            if (input[current] == '\\' && current + 1 < input.length()) {
                current += 2;
            } else {
                current++;
            }
        }
        if (current < input.length() && input[current] == '\'') {
            current++;
            token = new Token(Token::CHARACTER_CONSTANT, input, first, current - first);
        } else {
            token = new Token(Token::ERROR, input, first, current - first);
        }
        return token;
    }

    if (c == '"') {
        current++;
        while (current < input.length() && input[current] != '"') {
            if (input[current] == '\\' && current + 1 < input.length()) {
                current += 2;
            } else {
                current++;
            }
        }
        if (current < input.length() && input[current] == '"') {
            current++;
            string text = input.substr(first, current - first);
            if (text.find('.') != string::npos &&
                (text.find(".h\"") != string::npos || text.find(".c\"") != string::npos)) {
                token = new Token(Token::HEADER_NAME, input, first, current - first);
            } else {
                token = new Token(Token::STRING_LITERAL, input, first, current - first);
            }
        } else {
            token = new Token(Token::ERROR, input, first, current - first);
        }
        return token;
    }

    if (isdigit(c)) {
        current++;
        while (current < input.length() && isdigit(input[current]))
            current++;

        if (current < input.length() && input[current] == '.') {
            current++;
            while (current < input.length() && isdigit(input[current]))
                current++;
            token = new Token(Token::FLOATING_CONSTANT, input, first, current - first);
        } else {
            token = new Token(Token::INTEGER_CONSTANT, input, first, current - first);
        }
    }

    else if (isalpha(c) || c == '_') {
        current++;
        while (current < input.length() && (isalnum(input[current]) || input[current] == '_'))
            current++;
        string word = input.substr(first, current - first);
        if (word == "if") {
            token = new Token(Token::IF, word, 0, word.length());
        } else if (word == "else") {
            token = new Token(Token::ELSE, word, 0, word.length());
        } else if (word == "while") {
            token = new Token(Token::WHILE, word, 0, word.length());
        } else if (word == "do") {
            token = new Token(Token::DO, word, 0, word.length());
        } else if (word == "for") {
            token = new Token(Token::FOR, word, 0, word.length());
        } else if (word == "return") {
            token = new Token(Token::RETURN, word, 0, word.length());
        } else if (word == "void") {
            token = new Token(Token::VOID, word, 0, word.length());
        } else if (word == "char") {
            token = new Token(Token::CHAR, word, 0, word.length());
        } else if (word == "short") {
            token = new Token(Token::SHORT, word, 0, word.length());
        } else if (word == "int") {
            token = new Token(Token::INT, word, 0, word.length());
        } else if (word == "long") {
            token = new Token(Token::LONG, word, 0, word.length());
        } else if (word == "float") {
            token = new Token(Token::FLOAT, word, 0, word.length());
        } else if (word == "double") {
            token = new Token(Token::DOUBLE, word, 0, word.length());
        } else if (word == "signed") {
            token = new Token(Token::SIGNED, word, 0, word.length());
        } else if (word == "unsigned") {
            token = new Token(Token::UNSIGNED, word, 0, word.length());
        } else if (word == "switch") {
            token = new Token(Token::SWITCH, word, 0, word.length());
        } else if (word == "case") {
            token = new Token(Token::CASE, word, 0, word.length());
        } else if (word == "default") {
            token = new Token(Token::DEFAULT, word, 0, word.length());
        } else if (word == "goto") {
            token = new Token(Token::GOTO, word, 0, word.length());
        } else if (word == "break") {
            token = new Token(Token::BREAK, word, 0, word.length());
        } else if (word == "continue") {
            token = new Token(Token::CONTINUE, word, 0, word.length());
        } else if (word == "struct") {
            token = new Token(Token::STRUCT, word, 0, word.length());
        } else if (word == "union") {
            token = new Token(Token::UNION, word, 0, word.length());
        } else if (word == "const") {
            token = new Token(Token::CONST, word, 0, word.length());
        } else if (word == "volatile") {
            token = new Token(Token::VOLATILE, word, 0, word.length());
        } else if (word == "sizeof") {
            token = new Token(Token::SIZEOF, word, 0, word.length());
        } else {
            token = new Token(Token::IDENTIFIER, word, 0, word.length());
        }
    }

    else if (strchr("+-*/()=;,<>!&|^~%{}.:?", c)) {
        switch(c) {
            case '.': {
                if (current + 2 < input.length() &&
                    input[current + 1] == '.' && input[current + 2] == '.') {
                    token = new Token(Token::ELLIPSIS, "...", 0, 3);
                    current += 2;

                    int temp_pos = current + 1;
                    while (temp_pos < input.length() && is_white_space(input[temp_pos])) {
                        temp_pos++;
                    }
                    if (temp_pos < input.length() && input[temp_pos] == ')') {
                        token = new Token(Token::VARARGS, "...)", 0, 4);
                        current = temp_pos;
                    }
                } else {
                    token = new Token(Token::DOT, c);
                }
                break;
            }
            case '+':
                if (current + 1 < input.length() && input[current + 1] == '+') {
                    token = new Token(Token::INCREMENT, "++", 0, 2);
                    current++;
                } else if (current + 1 < input.length() && input[current + 1] == '=') {
                    token = new Token(Token::PLUS_ASSIGN, "+=", 0, 2);
                    current++;
                } else {
                    token = new Token(Token::PLUS, c);
                }
                break;
            case '-':
                if (current + 1 < input.length() && input[current + 1] == '-') {
                    token = new Token(Token::DECREMENT, "--", 0, 2);
                    current++;
                } else if (current + 1 < input.length() && input[current + 1] == '=') {
                    token = new Token(Token::MINUS_ASSIGN, "-=", 0, 2);
                    current++;
                } else if (current + 1 < input.length() && input[current + 1] == '>') {
                    token = new Token(Token::ARROW, "->", 0, 2);
                    current++;
                } else {
                    token = new Token(Token::MINUS, c);
                }
                break;
            case '*': {
                if (current + 1 < input.length() && input[current + 1] == '=') {
                    token = new Token(Token::MULTIPLY_ASSIGN, "*=", 0, 2);
                    current++;
                } else {
                    int ptr_pos = current + 1;
                    while (ptr_pos < input.length() && is_white_space(input[ptr_pos])) {
                        ptr_pos++;
                    }

                    if (ptr_pos < input.length()) {
                        if (input.substr(ptr_pos, 5) == "const") {
                            token = new Token(Token::POINTER_CONST, "* const", 0, 7);
                            current = ptr_pos + 5;
                        } else if (input.substr(ptr_pos, 8) == "volatile") {
                            token = new Token(Token::POINTER_VOLATILE, "* volatile", 0, 9);
                            current = ptr_pos + 8;
                        } else {
                            token = new Token(Token::MULTIPLY, c);
                        }
                    } else {
                        token = new Token(Token::MULTIPLY, c);
                    }
                }
                break;
            }
            case '/':
                if (current + 1 < input.length() && input[current + 1] == '=') {
                    token = new Token(Token::DIVIDE_ASSIGN, "/=", 0, 2);
                    current++;
                } else {
                    token = new Token(Token::DIVIDE, c);
                }
                break;
            case '%':
                if (current + 1 < input.length() && input[current + 1] == '=') {
                    token = new Token(Token::MODULO_ASSIGN, "%=", 0, 2);
                    current++;
                } else {
                    token = new Token(Token::MODULO, c);
                }
                break;
            case '=': {
                if (current + 1 < input.length() && input[current + 1] == '=') {
                    token = new Token(Token::EQUAL, "==", 0, 2);
                    current++;
                } else {
                    int init_start = current + 1;
                    while (init_start < input.length() && is_white_space(input[init_start])) {
                        init_start++;
                    }

                    if (init_start < input.length()) {
                        token = new Token(Token::INITIALIZER, "=", 0, 1);
                    } else {
                        token = new Token(Token::ASSIGN, c);
                    }
                }
                break;
            }
            case '<':
                if (current + 1 < input.length() && input[current + 1] == '=') {
                    token = new Token(Token::LESS_EQUAL, "<=", 0, 2);
                    current++;
                } else if (current + 1 < input.length() && input[current + 1] == '<') {
                    if (current + 2 < input.length() && input[current + 2] == '=') {
                        token = new Token(Token::LEFT_SHIFT_ASSIGN, "<<=", 0, 3);
                        current += 2;
                    } else {
                        token = new Token(Token::LEFT_SHIFT, "<<", 0, 2);
                        current++;
                    }
                } else {
                    token = new Token(Token::LESS_THAN, c);
                }
                break;
            case '>':
                if (current + 1 < input.length() && input[current + 1] == '=') {
                    token = new Token(Token::GREATER_EQUAL, ">=", 0, 2);
                    current++;
                } else if (current + 1 < input.length() && input[current + 1] == '>') {
                    if (current + 2 < input.length() && input[current + 2] == '=') {
                        token = new Token(Token::RIGHT_SHIFT_ASSIGN, ">>=", 0, 3);
                        current += 2;
                    } else {
                        token = new Token(Token::RIGHT_SHIFT, ">>", 0, 2);
                        current++;
                    }
                } else {
                    token = new Token(Token::GREATER_THAN, c);
                }
                break;
            case '!':
                if (current + 1 < input.length() && input[current + 1] == '=') {
                    token = new Token(Token::NOT_EQUAL, "!=", 0, 2);
                    current++;
                } else {
                    token = new Token(Token::LOGICAL_NOT, c);
                }
                break;
            case '&':
                if (current + 1 < input.length() && input[current + 1] == '&') {
                    token = new Token(Token::LOGICAL_AND, "&&", 0, 2);
                    current++;
                } else if (current + 1 < input.length() && input[current + 1] == '=') {
                    token = new Token(Token::AND_ASSIGN, "&=", 0, 2);
                    current++;
                } else {
                    token = new Token(Token::BITWISE_AND, c);
                }
                break;
            case '|':
                if (current + 1 < input.length() && input[current + 1] == '|') {
                    token = new Token(Token::LOGICAL_OR, "||", 0, 2);
                    current++;
                } else if (current + 1 < input.length() && input[current + 1] == '=') {
                    token = new Token(Token::OR_ASSIGN, "|=", 0, 2);
                    current++;
                } else {
                    token = new Token(Token::BITWISE_OR, c);
                }
                break;
            case '^':
                if (current + 1 < input.length() && input[current + 1] == '=') {
                    token = new Token(Token::XOR_ASSIGN, "^=", 0, 2);
                    current++;
                } else {
                    token = new Token(Token::BITWISE_XOR, c);
                }
                break;
            case '~': token = new Token(Token::BITWISE_NOT, c); break;
            case '(': token = new Token(Token::LEFT_PAREN, c); break;
            case ')': token = new Token(Token::RIGHT_PAREN, c); break;
            case '{': token = new Token(Token::LEFT_BRACE, c); break;
            case '}': token = new Token(Token::RIGHT_BRACE, c); break;
            case ';': token = new Token(Token::SEMICOLON, c); break;
            case ',': token = new Token(Token::COMMA, c); break;
            case ':': token = new Token(Token::COLON, c); break;
            case '?': token = new Token(Token::QUESTION, c); break;
            default:
                cout << "No debería llegar acá" << endl;
                token = new Token(Token::ERROR, c);
        }
        current++;
    }
    else {
        token = new Token(Token::ERROR, c);
        current++;
    }
    return token;
}

void Scanner::reset() {
    first = 0;
    current = 0;
}

Scanner::~Scanner() { }

void test_scanner(Scanner* scanner) {
    Token* current;
    cout << "Iniciando Scanner:" << endl<< endl;
    while ((current = scanner->nextToken())->type != Token::END_OF_FILE) {
        if (current->type == Token::ERROR) {
            cout << "Error en scanner - carácter inválido: " << current->text << endl;
            break;
        } else {
            cout << *current << endl;
        }
        delete current;
    }
    cout << "TOKEN(END_OF_FILE)" << endl;
    delete current;
}