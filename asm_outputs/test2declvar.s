Contenido del archivo (151 caracteres):
----------------------------------------
#include<stdio.h>
int main(){
    int x;
    int y;
    x = 1;
    y = 10;
    x = 20;
    printf(" %d\n", x);
    printf(" %d\n", y);
    return 0;
}
----------------------------------------

=== FASE 1: ANÁLISIS LÉXICO ===
Iniciando Scanner:

INCLUDE('#include')
HEADER_NAME('<stdio.h>')
INT('int')
MAIN('main')
LEFT_PAREN('(')
RIGHT_PAREN(')')
LEFT_BRACE('{')
INT('int')
IDENTIFIER('x')
SEMICOLON(';')
INT('int')
IDENTIFIER('y')
SEMICOLON(';')
IDENTIFIER('x')
ASSIGN('=')
NUMBER('1')
SEMICOLON(';')
IDENTIFIER('y')
ASSIGN('=')
NUMBER('10')
SEMICOLON(';')
IDENTIFIER('x')
ASSIGN('=')
NUMBER('20')
SEMICOLON(';')
PRINTF('printf')
LEFT_PAREN('(')
FORMAT_STRING('" %d\n"')
COMMA(',')
IDENTIFIER('x')
RIGHT_PAREN(')')
SEMICOLON(';')
PRINTF('printf')
LEFT_PAREN('(')
FORMAT_STRING('" %d\n"')
COMMA(',')
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

int main() {
    int x;
    int y;
    x = 1;
    y = 10;
    x = 20;
    printf(" %d\n", x);
    printf(" %d\n", y);
    return 0;
}

Impresion del programa completada.

=== ANALISIS COMPLETADO EXITOSAMENTE ===
