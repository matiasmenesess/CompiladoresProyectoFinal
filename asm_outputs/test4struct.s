Contenido del archivo (187 caracteres):
----------------------------------------
#include <stdio.h>

struct Punto {
    int x;
    int y;
};

int main() {
    struct Punto p;
    p.x = 5;
    p.y = p.x * 2;
    printf("p.y deberia ser 10: %d\n", p.y);
    return 0;
}
----------------------------------------

=== FASE 1: ANÁLISIS LÉXICO ===
Iniciando Scanner:

INCLUDE('#include')
HEADER_NAME('<stdio.h>')
STRUCT('struct')
IDENTIFIER('Punto')
LEFT_BRACE('{')
INT('int')
IDENTIFIER('x')
SEMICOLON(';')
INT('int')
IDENTIFIER('y')
SEMICOLON(';')
RIGHT_BRACE('}')
SEMICOLON(';')
INT('int')
MAIN('main')
LEFT_PAREN('(')
RIGHT_PAREN(')')
LEFT_BRACE('{')
STRUCT('struct')
IDENTIFIER('Punto')
IDENTIFIER('p')
SEMICOLON(';')
IDENTIFIER('p')
DOT('.')
IDENTIFIER('x')
ASSIGN('=')
NUMBER('5')
SEMICOLON(';')
IDENTIFIER('p')
DOT('.')
IDENTIFIER('y')
ASSIGN('=')
IDENTIFIER('p')
DOT('.')
IDENTIFIER('x')
MULTIPLY('*')
NUMBER('2')
SEMICOLON(';')
PRINTF('printf')
LEFT_PAREN('(')
FORMAT_STRING('"p.y deberia ser 10: %d\n"')
COMMA(',')
IDENTIFIER('p')
DOT('.')
IDENTIFIER('y')
RIGHT_PAREN(')')
SEMICOLON(';')
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

struct Punto {
    int x;
    int y;
};

int main() {
    struct Punto p;
    p.x = 5;
    p.y = p.x * 2;
    printf("p.y deberia ser 10: %d\n", p.y);
    return 0;
}

Impresion del programa completada.

=== ANALISIS COMPLETADO EXITOSAMENTE ===
