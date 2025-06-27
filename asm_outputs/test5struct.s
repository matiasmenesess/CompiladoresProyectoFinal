Contenido del archivo (186 caracteres):
----------------------------------------
#include <stdio.h>

struct Punto {
    int x;
    int y;
};

int main() {
    struct Punto p1;
    p1.x = 10;
    p1.y = 20;
    printf("Punto: (%d, %d)\n", p1.x, p1.y);
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
IDENTIFIER('p1')
SEMICOLON(';')
IDENTIFIER('p1')
DOT('.')
IDENTIFIER('x')
ASSIGN('=')
NUMBER('10')
SEMICOLON(';')
IDENTIFIER('p1')
DOT('.')
IDENTIFIER('y')
ASSIGN('=')
NUMBER('20')
SEMICOLON(';')
PRINTF('printf')
LEFT_PAREN('(')
FORMAT_STRING('"Punto: (%d, %d)\n"')
COMMA(',')
IDENTIFIER('p1')
DOT('.')
IDENTIFIER('x')
COMMA(',')
IDENTIFIER('p1')
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
    struct Punto p1;
    p1.x = 10;
    p1.y = 20;
    printf("Punto: (%d, %d)\n", p1.x, p1.y);
    return 0;
}

Impresion del programa completada.

=== ANALISIS COMPLETADO EXITOSAMENTE ===
