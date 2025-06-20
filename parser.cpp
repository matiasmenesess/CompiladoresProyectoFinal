//
// Created by zamirlm on 6/5/25.
//

#include "parser.h"
#include "expression.h"
#include "scanner.h"
#include "token.h"
using namespace std;

bool Parser::match(Token::Type ttype) {
    if (check(ttype)) {
        advance();
        return true;
    }
    return false;
}

bool Parser::check(Token::Type ttype) {
    if (isAtEnd()) return false;
    return current->type == ttype;
}

bool Parser::advance() {
    if (!isAtEnd()) {
        Token* temp = current;
        if (previous) delete previous;
        current = scanner->nextToken();
        previous = temp;
        if (check(Token::ERROR)) {
            cout << "Error de análisis, carácter no reconocido: " << current->text << endl;
            exit(1);
        }
        return true;
    }
    return false;
}

bool Parser::isAtEnd() {
    return (current->type == Token::END_OF_FILE);
}

Parser::Parser(Scanner* sc):scanner(sc) {
    previous = NULL;
    current = scanner->nextToken();
    if (current->type == Token::ERROR) {
        cout << "Error en el primer token: " << current->text << endl;
        exit(1);
    }
}

Parser::~Parser() {
    if (current) delete current;
    if (previous) delete previous;
}



Program* Parser::parseProgram() {
    IncludeList* includes = parseIncludes();
    if (check((Token::BLOCK_COMMENT))){
        match(Token::BLOCK_COMMENT);

        //BORRAR LUEGO
        cout<<previous->text<<endl;

    }
    GlobalVarDecList* globals = parseGlobalDeclarations();
    StructDeclarationList* structs = parseStructDeclarations();
    FunctionList* functions = parseFunctions();
    MainFunction* main = parseMainFunction();
    return new Program(includes, globals, structs, functions, main);
}

IncludeList* Parser::parseIncludes() {
    IncludeList* includes = new IncludeList();
    while (check(Token::INCLUDE)) {
        includes->add(parseInclude());
    }
    return includes;
}

Include* Parser::parseInclude() {
    if(!match(Token::INCLUDE)){
        cout << "Error: se esperaba un 'include'." << endl;
        exit(1);
    }

    //BORRAR LUEGO
    cout<<"#include";

    if(!match(Token::HEADER_NAME)){
        cout << "Error: se esperaba un nombre de header después de #include." << endl;
        exit(1);
    }

    string headerName = previous->text;

    //BORRAR LUEGO
    cout<<headerName+"\n";

    bool isSystemHeader = (headerName[0] == '<');

    return new Include(headerName, isSystemHeader);
}

GlobalVarDecList* Parser::parseGlobalDeclarations() {
    GlobalVarDecList* globals = new GlobalVarDecList();
    // Esta lógica de lookahead es compleja y se mantiene igual.
    while (!isAtEnd() && !check(Token::STRUCT) && !check(Token::MAIN)) {
        if (check(Token::INT) || check(Token::CHAR)) {
            Token* type_tok = current; advance();
            if(!check(Token::IDENTIFIER)) break; // Salir si no es un patrón de declaración
            Token* id_tok = current;

            if(check(Token::LEFT_PAREN)) {
                scanner->reset();
                current = scanner->nextToken();
                while(current->text != type_tok->text) current = scanner->nextToken();
                previous = nullptr;
                break;
            }
            scanner->reset();
            current = scanner->nextToken();
            while(current->text != type_tok->text) current = scanner->nextToken();
            previous = nullptr;

            globals->add(parseGlobalVarDec());

            if (!match(Token::SEMICOLON)) {
                throw runtime_error("Se esperaba ';' despues de la declaracion de variable global.");
            }

        } else {
            break;
        }
    }
    return globals;
}

GlobalVarDec* Parser::parseGlobalVarDec() {
    Type* type = parseType();
    if (!check(Token::IDENTIFIER)) {
        throw runtime_error("Se esperaba un identificador para la variable global.");
    }
    string name = current->text;
    advance();

    Exp* init = nullptr;
    if (match(Token::ASSIGN)) {
        init = parseExpression();
    }
    return new GlobalVarDec(type, name, init);
}

StructDeclarationList* Parser::parseStructDeclarations() {
    StructDeclarationList* structs = new StructDeclarationList();
    while(match(Token::STRUCT)) {
        //BORRAR LUEGO
        cout<<"struct ";
        structs->add(parseStructDeclaration());
    }
    return structs;
}

StructDeclaration* Parser::parseStructDeclaration() {
    if (!check(Token::IDENTIFIER)) {
        throw runtime_error("Se esperaba el nombre del struct.");
    }
    string name = current->text;

    //BORRAR LUEGO
    cout<<name;

    advance();

    if (!match(Token::LEFT_BRACE)) {
        throw runtime_error("Se esperaba '{' para iniciar el cuerpo del struct.");
    }

    //BORRAR LUEGO
    cout<<"{\n";


    VarDecList* members = parseVarDecList();
    if (!match(Token::RIGHT_BRACE)) {
        throw runtime_error("Se esperaba '}' para finalizar el cuerpo del struct.");
    }

    //BORRAR LUEGO
    cout<<"}";

    if (!match(Token::SEMICOLON)) {
        throw runtime_error("Se esperaba ';' despues de la declaracion de struct.");
    }

    cout<<";\n";

    return new StructDeclaration(name, members);
}

FunctionList* Parser::parseFunctions() {
    FunctionList* functions = new FunctionList();
    // La lógica de lookahead se mantiene
    while(!isAtEnd() && !check(Token::MAIN)) {
        if(check(Token::INT) || check(Token::CHAR) || check(Token::VOID)) {

            //BORRAR LUEGO
            if(check(Token::INT)){
                cout<<"int ";
            }
            else if(check(Token::CHAR)){
                cout<<"char ";
            }
            else if(check(Token::VOID)){
                cout<<"void ";
            }


            Token* temp_current = current; advance();
            if(check(Token::IDENTIFIER)){
                Token* temp_id = current; advance();

                //BORRAR LUEGO
                cout<<previous->text;


                if(check(Token::LEFT_PAREN)) {

                    //BORRAR LUEGO
                    cout<<"(";

                    current = temp_current;
                    scanner->reset();
                    while(current->text != temp_current->text) current = scanner->nextToken();
                    functions->add(parseFunction());
                } else {
                    current = temp_current;
                    scanner->reset();
                    while(current->text != temp_current->text) current = scanner->nextToken();
                    break;
                }
            } else {
                current = temp_current;
                scanner->reset();
                while(current->text != temp_current->text) current = scanner->nextToken();
                break;
            }
        } else {
            break;
        }
    }
    return functions;
}

Function* Parser::parseFunction() {
    Type* return_type = parseType();

    if (!check(Token::IDENTIFIER)) {
        throw runtime_error("Se esperaba un nombre de funcion.");
    }
    string name = current->text;



    advance();

    if (!match(Token::LEFT_PAREN)) {
        throw runtime_error("Se esperaba '(' despues del nombre de funcion.");
    }
    ParameterList* params = parseParameterList();
    if (!match(Token::RIGHT_PAREN)) {
        throw runtime_error("Se esperaba ')' despues de los parametros de la funcion.");
    }
    if (!match(Token::LEFT_BRACE)) {
        throw runtime_error("Se esperaba '{' antes del cuerpo de la funcion.");
    }
    Body* body = parseBody();
    if (!match(Token::RIGHT_BRACE)) {
        throw runtime_error("Se esperaba '}' despues del cuerpo de la funcion.");
    }
    return new Function(return_type, name, params, body);
}

MainFunction* Parser::parseMainFunction() {


    if (match(Token::INT) && match(Token::MAIN) && match(Token::LEFT_PAREN) && match(Token::RIGHT_PAREN)) {
        if (!match(Token::LEFT_BRACE)) {
            throw runtime_error("Se esperaba '{' para el cuerpo de main.");
        }
        Body* body = parseBody();
        if (!match(Token::RIGHT_BRACE)) {
            throw runtime_error("Se esperaba '}' para cerrar main.");
        }
        return new MainFunction(body);
    }
    cout << "Error: No se encontró la función 'int main()'." << endl;
    exit(1);
    return nullptr;
}

Type* Parser::parseType() {
    string typeName;

    if (check(Token::INT)) {
        typeName = "int";

        //BORRAR LUEGO
        cout<<typeName;

        advance();
    } else if (check(Token::CHAR)) {
        typeName = "char";

        //BORRAR LUEGO
        cout<<typeName;

        advance();
    } else if (check(Token::VOID)) {
        typeName = "void";

        //BORRAR LUEGO
        cout<<typeName;

        advance();
    } else if (check(Token::STRUCT)) {
        advance();

        if (!check(Token::IDENTIFIER)) {
            cout << "Error: se esperaba un nombre de struct después de 'struct'." << endl;
            exit(1);
        }

        typeName = "struct " + current->text;
        advance();
    } else {
        cout << "Error: se esperaba un tipo (int, char, void, struct)." << endl;
        exit(1);
    }

    bool isPointer = false;
    while (check(Token::MULTIPLY)) {
        isPointer = true;

        //BORRAR LUEGO
        cout<<"*";

        advance(); // Consumir cada '*'
    }

    if (isPointer) {
        return new Type(typeName, true);
    } else {
        return new Type(typeName);
    }
}

ParameterList* Parser::parseParameterList() {
    ParameterList* params = new ParameterList();
    if (!check(Token::RIGHT_PAREN)) {
        do {
            params->add(parseParameter());
        } while (match(Token::COMMA));
    }
    return params;
}

Parameter* Parser::parseParameter() {
    Type* type = parseType();
    if (!check(Token::IDENTIFIER)) {
        throw runtime_error("Se esperaba un nombre para el parametro.");
    }
    string name = current->text;
    advance();
    return new Parameter(type, name);
}

Body* Parser::parseBody() {
    VarDecList* var_decs = parseVarDecList();
    StatementList* stm_list = parseStatementList();
    return new Body(var_decs, stm_list);
}
VarDecList* Parser::parseVarDecList() {
    VarDecList* vardecs = new VarDecList();

    while (check(Token::INT) || check(Token::CHAR) || check(Token::STRUCT)) {



        vardecs->add(parseVarDec());
        if (!match(Token::SEMICOLON)) {
            throw runtime_error("Se esperaba ';' despues de la declaracion de variable.");
        }

        //BORRAR LUEGO
        cout << ";\n";

    }
    return vardecs;
}

VarDec* Parser::parseVarDec() {
    Type* type = parseType();
    list<string> vars;
    list<Exp*> initializers;
    do {
        if (!check(Token::IDENTIFIER)) {
            throw runtime_error("Se esperaba un identificador.");
        }
        string name = current->text;

        //BORRAR LUEGO
        cout <<" "<<name;

        advance();
        vars.push_back(name);

        if (match(Token::ASSIGN)) {
            //BORRAR LUEGO
            cout << " = ";

            initializers.push_back(parseExpression());
        } else {
            initializers.push_back(nullptr);
        }

        if (check(Token::COMMA)) {
            //BORRAR LUEGO
            cout << ", ";
        }

    } while (match(Token::COMMA));

    VarDec* vd = new VarDec(type, vars);
    for(auto init : initializers) {
        if(init) vd->add_initializer(init);
    }
    return vd;
}

StatementList* Parser::parseStatementList() {
    StatementList* stms = new StatementList();
    while (!check(Token::RIGHT_BRACE) && !isAtEnd()) {
        stms->add(parseStatement());
    }
    return stms;
}
Stm* Parser::parseStatement() {
    if (match(Token::IF)) return parseIfStatement();
    if (match(Token::WHILE)) return parseWhileStatement();
    if (match(Token::FOR)) return parseForStatement();
    if (match(Token::RETURN)) return parseReturnStatement();
    if (match(Token::PRINTF)) return parsePrintfStatement();
    return parseExpressionStatement();
}

Stm* Parser::parseIfStatement() {
    if (!match(Token::LEFT_PAREN)) throw runtime_error("Se esperaba '(' despues de 'if'.");
    Exp* cond = parseExpression();
    if (!match(Token::RIGHT_PAREN)) throw runtime_error("Se esperaba ')' despues de la condicion del if.");
    if (!match(Token::LEFT_BRACE)) throw runtime_error("Se esperaba '{' para el cuerpo del if.");
    Body* if_body = parseBody();
    if (!match(Token::RIGHT_BRACE)) throw runtime_error("Se esperaba '}' para cerrar el cuerpo del if.");

    Stm* else_chain = nullptr;
    if (match(Token::ELSE_IF)) {
        else_chain = parseIfStatement();
    } else if (match(Token::ELSE)) {
        if (!match(Token::LEFT_BRACE)) throw runtime_error("Se esperaba '{' para el cuerpo del else.");
        Body* else_body = parseBody();
        if (!match(Token::RIGHT_BRACE)) throw runtime_error("Se esperaba '}' para cerrar el cuerpo del else.");
        else_chain = new IfStatement(nullptr, else_body, nullptr);
    }
    return new IfStatement(cond, if_body, else_chain);
}

Stm* Parser::parseWhileStatement() {
    if (!match(Token::LEFT_PAREN)) throw runtime_error("Se esperaba '(' despues de 'while'.");
    Exp* cond = parseExpression();
    if (!match(Token::RIGHT_PAREN)) throw runtime_error("Se esperaba ')' despues de la condicion del while.");
    if (!match(Token::LEFT_BRACE)) throw runtime_error("Se esperaba '{' para el cuerpo del while.");
    Body* body = parseBody();
    if (!match(Token::RIGHT_BRACE)) throw runtime_error("Se esperaba '}' para cerrar el cuerpo del while.");
    return new WhileStatement(cond, body);
}
Stm* Parser::parseForStatement() {
    if (!match(Token::LEFT_PAREN)) throw runtime_error("Se esperaba '(' despues de 'for'.");
    Exp* init = nullptr;
    if(!check(Token::SEMICOLON)) init = parseExpression();
    if (!match(Token::SEMICOLON)) throw runtime_error("Se esperaba ';' despues de la inicializacion del for.");

    Exp* cond = nullptr;
    if(!check(Token::SEMICOLON)) cond = parseExpression();
    if (!match(Token::SEMICOLON)) throw runtime_error("Se esperaba ';' despues de la condicion del for.");

    Exp* update = nullptr;
    if(!check(Token::RIGHT_PAREN)) update = parseExpression();
    if (!match(Token::RIGHT_PAREN)) throw runtime_error("Se esperaba ')' despues de las clausulas del for.");
    if (!match(Token::LEFT_BRACE)) throw runtime_error("Se esperaba '{' para el cuerpo del for.");
    Body* body = parseBody();
    if (!match(Token::RIGHT_BRACE)) throw runtime_error("Se esperaba '}' para cerrar el cuerpo del for.");
    return new ForStatement(init, cond, update, body);
}

Stm* Parser::parseReturnStatement() {
    Exp* val = nullptr;
    if (!check(Token::SEMICOLON)) val = parseExpression();
    if (!match(Token::SEMICOLON)) throw runtime_error("Se esperaba ';' despues de la sentencia return.");
    return new ReturnStatement(val);
}

Stm* Parser::parsePrintfStatement() {
    if (!match(Token::LEFT_PAREN)) throw runtime_error("Se esperaba '(' despues de 'printf'.");
    if(!check(Token::FORMAT_STRING) && !check(Token::STRING_LITERAL)) {
        throw runtime_error("Se esperaba una cadena de formato en printf.");
    }
    string format_string = current->text;
    advance();

    PrintfStatement* printf_stm = new PrintfStatement(format_string);
    if(match(Token::COMMA)) {
        list<Exp*> args = parseArguments();
        for(auto arg: args) printf_stm->add_argument(arg);
    }
    if (!match(Token::RIGHT_PAREN)) throw runtime_error("Se esperaba ')' despues de los argumentos de printf.");
    if (!match(Token::SEMICOLON)) throw runtime_error("Se esperaba ';' despues de la llamada a printf.");
    return printf_stm;
}

Stm* Parser::parseExpressionStatement() {
    Exp* exp = parseExpression();
    if (!match(Token::SEMICOLON)) {
        throw runtime_error("Se esperaba ';' despues de la expresion.");
    }
    return new ExpressionStatement(exp);
}

// Expression parsing
Exp* Parser::parseExpression() { return parseAssignment(); }

Exp* Parser::parseAssignment() {
    Exp* left = parseLogicalOr();
    if (match(Token::ASSIGN) || match(Token::PLUS_ASSIGN) || match(Token::MINUS_ASSIGN) ||
        match(Token::MULTIPLY_ASSIGN) || match(Token::DIVIDE_ASSIGN) || match(Token::MODULO_ASSIGN)) {
        Token* op_token = previous;
        BinaryOp op;
        if(op_token->type == Token::ASSIGN) op = ASSIGN_OP;
        else if(op_token->type == Token::PLUS_ASSIGN) op = PLUS_EQUAL_OP;
        else if(op_token->type == Token::MINUS_ASSIGN) op = MINUS_EQUAL_OP;
        else if(op_token->type == Token::MULTIPLY_ASSIGN) op = MULTIPLY_EQUAL_OP;
        else if(op_token->type == Token::DIVIDE_ASSIGN) op = DIVIDE_EQUAL_OP;
        else op = MODULO_EQUAL_OP;
        Exp* right = parseAssignment();
        return new AssignExp(left, right, op);
    }
    return left;
}

Exp* Parser::parseLogicalOr() {
    Exp* expr = parseLogicalAnd();
    while (match(Token::LOGICAL_OR)) {
        expr = new BinaryExp(expr, parseLogicalAnd(), LOGICAL_OR_OP);
    }
    return expr;
}
Exp* Parser::parseLogicalAnd() {
    Exp* expr = parseEquality();
    while (match(Token::LOGICAL_AND)) {
        expr = new BinaryExp(expr, parseEquality(), LOGICAL_AND_OP);
    }
    return expr;
}

Exp* Parser::parseComparison() {
    Exp* expr = parseAdditive();

    while (check(Token::LESS_THAN) || check(Token::GREATER_THAN) ||
           check(Token::LESS_EQUAL) || check(Token::GREATER_EQUAL)) {
        BinaryOp op;
        if (check(Token::LESS_THAN)) {
            op = LESS_THAN_OP;
        } else if (check(Token::GREATER_THAN)) {
            op = GREATER_THAN_OP;
        } else if (check(Token::LESS_EQUAL)) {
            op = LESS_EQUAL_OP;
        } else {
            op = GREATER_EQUAL_OP;
        }

        advance(); // Consumir el operador

        Exp* right = parseAdditive();
        expr = new BinaryExp(expr, right, op);
    }

    return expr;
}

Exp* Parser::parseEquality() {
    Exp* expr = parseComparison();

    while (check(Token::EQUAL) || check(Token::NOT_EQUAL)) {
        BinaryOp op;
        if (check(Token::EQUAL)) {
            op = EQUAL_OP;
        } else {
            op = NOT_EQUAL_OP;
        }

        advance(); // Consumir el operador

        Exp* right = parseComparison();
        expr = new BinaryExp(expr, right, op);
    }

    return expr;
}

Exp* Parser::parseAdditive() {
    Exp* expr = parseMultiplicative();

    while (check(Token::PLUS) || check(Token::MINUS)) {
        BinaryOp op;
        if (check(Token::PLUS)) {
            op = PLUS_OP;
        } else {
            op = MINUS_OP;
        }

        advance(); // Consumir el operador

        Exp* right = parseMultiplicative();
        expr = new BinaryExp(expr, right, op);
    }

    return expr;
}

Exp* Parser::parseMultiplicative() {
    Exp* expr = parseUnary();

    while (check(Token::MULTIPLY) || check(Token::DIVIDE) || check(Token::MODULO)) {
        BinaryOp op;
        if (check(Token::MULTIPLY)) {
            op = MULT_OP;
        } else if (check(Token::DIVIDE)) {
            op = DIV_OP;
        } else {
            op = MOD_OP;
        }

        advance(); // Consumir el operador

        Exp* right = parseUnary();
        expr = new BinaryExp(expr, right, op);
    }

    return expr;
}

Exp* Parser::parseUnary() {
    if (check(Token::LOGICAL_NOT) || check(Token::INCREMENT) || check(Token::DECREMENT) ||
        check(Token::DEREFERENCE) || check(Token::ADDRESS_OF) ||
        check(Token::PLUS) || check(Token::MINUS)) {

        UnaryOp op;
        if (check(Token::LOGICAL_NOT)) {
            op = NEGACION_OP;
        } else if (check(Token::INCREMENT)) {
            op = PLUS_PLUS_OP;
        } else if (check(Token::DECREMENT)) {
            op = MINUS_MINUS_OP;
        } else if (check(Token::DEREFERENCE)) {
            op = DEREFERENCE_OP;
        } else if (check(Token::ADDRESS_OF)) {
            op = ADDRESS_OF_OP;
        } else if (check(Token::PLUS)) {
            op = UNARY_PLUS_OP;
        } else if (check(Token::MINUS)) {
            op = UNARY_MINUS_OP;
        }

        advance();

        Exp* expr = parseUnary();

        return new UnaryExp(expr, op, true);
    }

    // Si no hay operador unario, pasamos a postfix
    return parsePostfix();
}

Exp* Parser::parsePostfix() {
    Exp* expr = parsePrimary();
    while (true) {
        if (match(Token::INCREMENT)) {
            expr = new UnaryExp(expr, PLUS_PLUS_OP, false);
        } else if (match(Token::DECREMENT)) {
            expr = new UnaryExp(expr, MINUS_MINUS_OP, false);
        } else if (match(Token::LEFT_BRACKET)) {
            Exp* index = parseExpression();
            if (!match(Token::RIGHT_BRACKET)) throw runtime_error("Se esperaba ']' despues del indice del array.");
            expr = new ArrayAccessExp(expr, index);
        } else if (match(Token::LEFT_PAREN)) {
            IdentifierExp* id_exp = dynamic_cast<IdentifierExp*>(expr);
            if (!id_exp) throw runtime_error("La llamada a función debe ser sobre un identificador.");
            FunctionCallExp* call = new FunctionCallExp(id_exp->name);
            if(!check(Token::RIGHT_PAREN)){
                list<Exp*> args = parseArguments();
                for(auto arg: args) call->add_argument(arg);
            }
            if (!match(Token::RIGHT_PAREN)) throw runtime_error("Se esperaba ')' despues de los argumentos de la funcion.");
            expr = call;
        } else if (match(Token::DOT)) {
            if (!check(Token::IDENTIFIER)) throw runtime_error("Se esperaba el nombre del miembro.");
            string member_name = current->text;
            advance();
            expr = new MemberAccessExp(expr, member_name, false);
        } else if (match(Token::ARROW)) {
            if (!check(Token::IDENTIFIER)) throw runtime_error("Se esperaba el nombre del miembro.");
            string member_name = current->text;
            advance();
            expr = new MemberAccessExp(expr, member_name, true);
        } else {
            break;
        }
    }
    return expr;
}

Exp* Parser::parsePrimary() {
    if (match(Token::NUMBER)) return new NumberExp(stoi(previous->text));
    if (match(Token::IDENTIFIER)) return new IdentifierExp(previous->text);
    if (match(Token::STRING_LITERAL) || match(Token::FORMAT_STRING)) return new StringExp(previous->text);
    if (match(Token::CHARACTER_CONSTANT)) return new CharExp(previous->text[1]);
    if (match(Token::LEFT_PAREN)) {
        Exp* expr = parseExpression();
        if (!match(Token::RIGHT_PAREN)) throw runtime_error("Se esperaba ')' despues de la expresion.");
        return new ParenExp(expr);
    }
    if(match(Token::LEFT_BRACE)){
        list<Exp*> inits = parseInitializerList();
        if (!match(Token::RIGHT_BRACE)) throw runtime_error("Se esperaba '}' para cerrar la lista de inicializadores.");
        if(!inits.empty()) return inits.front();
        return nullptr;
    }
    throw runtime_error("Se esperaba una expresión primaria (numero, identificador, cadena, parentesis).");
}

Exp* Parser::parseFunctionCall() {
    // Esta lógica está ahora dentro de `parsePostfix` para permitir encadenamiento.
    // Dejar vacía o eliminar.
    return nullptr;
}

Exp* Parser::parseArrayAccess() {
    // Esta lógica está ahora dentro de `parsePostfix` para permitir encadenamiento.
    // Dejar vacía o eliminar.
    return nullptr;
}

Exp* Parser::parseMemberAccess() {
    // Esta lógica está ahora dentro de `parsePostfix` para permitir encadenamiento.
    // Dejar vacía o eliminar.
    return nullptr;
}

Exp* Parser::parseNumberExp() {
    if (!check(Token::NUMBER)) {
        cout << "Error: se esperaba un número." << endl;
        exit(1);
    }

    string numberText = current->text;
    int value = stoi(numberText);

    advance();

    return new NumberExp(value);
}

list<Exp*> Parser::parseArguments() {
    list<Exp*> args;
    do {
        args.push_back(parseExpression());
    } while (match(Token::COMMA));
    return args;
}


list<Exp*> Parser::parseInitializerList() {
    list<Exp*> inits;
    if (!check(Token::RIGHT_BRACE)) {
        do {
            inits.push_back(parseExpression());
        } while (match(Token::COMMA));
    }
    return inits;
}
