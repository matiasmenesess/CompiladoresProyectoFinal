Contenido del archivo (170 caracteres):
----------------------------------------
#include <stdio.h>

int suma(int a, int b) {
    return a + b;
}

int main() {
    int resultado = suma(5, 3);
    printf("La suma es: %d\n", resultado);
    return 0;
}
----------------------------------------

=== FASE 1: ANÁLISIS LÉXICO ===
Iniciando Scanner:

INCLUDE('#include')
HEADER_NAME('<stdio.h>')
INT('int')
IDENTIFIER('suma')
LEFT_PAREN('(')
INT('int')
IDENTIFIER('a')
COMMA(',')
INT('int')
IDENTIFIER('b')
RIGHT_PAREN(')')
LEFT_BRACE('{')
RETURN('return')
IDENTIFIER('a')
PLUS('+')
IDENTIFIER('b')
SEMICOLON(';')
RIGHT_BRACE('}')
INT('int')
MAIN('main')
LEFT_PAREN('(')
RIGHT_PAREN(')')
LEFT_BRACE('{')
INT('int')
IDENTIFIER('resultado')
ASSIGN('=')
IDENTIFIER('suma')
LEFT_PAREN('(')
NUMBER('5')
COMMA(',')
NUMBER('3')
RIGHT_PAREN(')')
SEMICOLON(';')
PRINTF('printf')
LEFT_PAREN('(')
FORMAT_STRING('"La suma es: %d\n"')
COMMA(',')
IDENTIFIER('resultado')
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


Error durante el analisis: Se esperaba ';' despues de la declaracion de variable global.
