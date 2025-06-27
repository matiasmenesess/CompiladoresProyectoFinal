Contenido del archivo (805 caracteres):
----------------------------------------
#include <stdio.h>

/*
 * Ejemplo de estructura y función
 * para probar el scanner
 */
struct Persona {
    char* nombre;
    int edad;
};

int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    else {
        return n * factorial(n - 1);
    }
}

int main() {
    char* mensaje = "Hola mundo!";
    int x = 5 / 1;
    int* ptr = &x;
    struct Persona p = {"Juan", 20};

    printf("Mensaje: %s\n", mensaje);
    printf("Factorial de %d es %d\n", x, factorial(x));
    printf("Persona: %s, %d anos\n", p.nombre, p.edad);

    for (int i = 0; i < 5; i++) {
        printf("%d ", i);
        if (i % 2 == 0) {
            printf("(par)");
        }else if (i % 2 != 0) {
            printf("(impar)");
        }
        else {
            printf("(otro)");
        }
    }

    return 0;
}
----------------------------------------

=== FASE 1: ANÁLISIS LÉXICO ===
Iniciando Scanner:

INCLUDE('#include')
HEADER_NAME('<stdio.h>')
BLOCK_COMMENT('/*
 * Ejemplo de estructura y función
 * para probar el scanner
 */')
STRUCT('struct')
IDENTIFIER('Persona')
LEFT_BRACE('{')
CHAR('char')
MULTIPLY('*')
IDENTIFIER('nombre')
SEMICOLON(';')
INT('int')
IDENTIFIER('edad')
SEMICOLON(';')
RIGHT_BRACE('}')
SEMICOLON(';')
INT('int')
IDENTIFIER('factorial')
LEFT_PAREN('(')
INT('int')
IDENTIFIER('n')
RIGHT_PAREN(')')
LEFT_BRACE('{')
IF('if')
LEFT_PAREN('(')
IDENTIFIER('n')
LESS_EQUAL('<=')
NUMBER('1')
RIGHT_PAREN(')')
LEFT_BRACE('{')
RETURN('return')
NUMBER('1')
SEMICOLON(';')
RIGHT_BRACE('}')
ELSE('else')
LEFT_BRACE('{')
RETURN('return')
IDENTIFIER('n')
MULTIPLY('*')
IDENTIFIER('factorial')
LEFT_PAREN('(')
IDENTIFIER('n')
MINUS('-')
NUMBER('1')
RIGHT_PAREN(')')
SEMICOLON(';')
RIGHT_BRACE('}')
RIGHT_BRACE('}')
INT('int')
MAIN('main')
LEFT_PAREN('(')
RIGHT_PAREN(')')
LEFT_BRACE('{')
CHAR('char')
MULTIPLY('*')
IDENTIFIER('mensaje')
ASSIGN('=')
STRING_LITERAL('"Hola mundo!"')
SEMICOLON(';')
INT('int')
IDENTIFIER('x')
ASSIGN('=')
NUMBER('5')
DIVIDE('/')
NUMBER('1')
SEMICOLON(';')
INT('int')
MULTIPLY('*')
IDENTIFIER('ptr')
ASSIGN('=')
ADDRESS_OF('&')
IDENTIFIER('x')
SEMICOLON(';')
STRUCT('struct')
IDENTIFIER('Persona')
IDENTIFIER('p')
ASSIGN('=')
LEFT_BRACE('{')
STRING_LITERAL('"Juan"')
COMMA(',')
NUMBER('20')
RIGHT_BRACE('}')
SEMICOLON(';')
PRINTF('printf')
LEFT_PAREN('(')
FORMAT_STRING('"Mensaje: %s\n"')
COMMA(',')
IDENTIFIER('mensaje')
RIGHT_PAREN(')')
SEMICOLON(';')
PRINTF('printf')
LEFT_PAREN('(')
FORMAT_STRING('"Factorial de %d es %d\n"')
COMMA(',')
IDENTIFIER('x')
COMMA(',')
IDENTIFIER('factorial')
LEFT_PAREN('(')
IDENTIFIER('x')
RIGHT_PAREN(')')
RIGHT_PAREN(')')
SEMICOLON(';')
PRINTF('printf')
LEFT_PAREN('(')
FORMAT_STRING('"Persona: %s, %d anos\n"')
COMMA(',')
IDENTIFIER('p')
DOT('.')
IDENTIFIER('nombre')
COMMA(',')
IDENTIFIER('p')
DOT('.')
IDENTIFIER('edad')
RIGHT_PAREN(')')
SEMICOLON(';')
FOR('for')
LEFT_PAREN('(')
INT('int')
IDENTIFIER('i')
ASSIGN('=')
NUMBER('0')
SEMICOLON(';')
IDENTIFIER('i')
LESS_THAN('<')
NUMBER('5')
SEMICOLON(';')
IDENTIFIER('i')
INCREMENT('++')
RIGHT_PAREN(')')
LEFT_BRACE('{')
PRINTF('printf')
LEFT_PAREN('(')
FORMAT_STRING('"%d "')
COMMA(',')
IDENTIFIER('i')
RIGHT_PAREN(')')
SEMICOLON(';')
IF('if')
LEFT_PAREN('(')
IDENTIFIER('i')
MODULO('%')
NUMBER('2')
EQUAL('==')
NUMBER('0')
RIGHT_PAREN(')')
LEFT_BRACE('{')
PRINTF('printf')
LEFT_PAREN('(')
STRING_LITERAL('"(par)"')
RIGHT_PAREN(')')
SEMICOLON(';')
RIGHT_BRACE('}')
ELSE_IF('else if')
LEFT_PAREN('(')
IDENTIFIER('i')
MODULO('%')
NUMBER('2')
NOT_EQUAL('!=')
NUMBER('0')
RIGHT_PAREN(')')
LEFT_BRACE('{')
PRINTF('printf')
LEFT_PAREN('(')
STRING_LITERAL('"(impar)"')
RIGHT_PAREN(')')
SEMICOLON(';')
RIGHT_BRACE('}')
ELSE('else')
LEFT_BRACE('{')
PRINTF('printf')
LEFT_PAREN('(')
STRING_LITERAL('"(otro)"')
RIGHT_PAREN(')')
SEMICOLON(';')
RIGHT_BRACE('}')
RIGHT_BRACE('}')
RETURN('return')
NUMBER('0')
SEMICOLON(';')
RIGHT_BRACE('}')
TOKEN(END_OF_FILE)
Scanner completado exitosamente

=== FASE 2: PARSER ===
Iniciando parser...

Programa parseado exitosamente

=== FASE 3: VISITANTE DE IMPRESION ===
#include <stdio.h>


struct Persona {
    char* nombre;
    int edad;
};

int factorial(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int main() {
    char* mensaje = ""Hola mundo!"";
    int x = 5 / 1;
    int* ptr = &x;
    struct Persona p = ""Juan"";
    printf("Mensaje: %s\n", mensaje);
    printf("Factorial de %d es %d\n", x, factorial(x));
    printf("Persona: %s, %d anos\n", p.nombre, p.edad);
    for (int i = 0; i < 5; i++) {
        printf("%d ", i);
        if (i % 2 == 0) {
            printf("(par)");
        }else if (i % 2 != 0) {
            printf("(impar)");
        } else {
            printf("(otro)");
        }
    }
    return 0;
}

Impresion del programa completada.

=== ANALISIS COMPLETADO EXITOSAMENTE ===
