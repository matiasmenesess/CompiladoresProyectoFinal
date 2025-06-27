Contenido del archivo (138 caracteres):
----------------------------------------
#include <stdio.h>

int main() {
    int a = 10, b = 2, c = 4;
    int y = (a + b) / c;
    printf("Resultado: %d\n", y);
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
IDENTIFIER('a')
ASSIGN('=')
NUMBER('10')
COMMA(',')
IDENTIFIER('b')
ASSIGN('=')
NUMBER('2')
COMMA(',')
IDENTIFIER('c')
ASSIGN('=')
NUMBER('4')
SEMICOLON(';')
INT('int')
IDENTIFIER('y')
ASSIGN('=')
LEFT_PAREN('(')
IDENTIFIER('a')
PLUS('+')
IDENTIFIER('b')
RIGHT_PAREN(')')
DIVIDE('/')
IDENTIFIER('c')
SEMICOLON(';')
PRINTF('printf')
LEFT_PAREN('(')
FORMAT_STRING('"Resultado: %d\n"')
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
    int a = 10, b = 2, c = 4;
    int y = (a + b) / c;
    printf("Resultado: %d\n", y);
    return 0;
}

Impresion del programa completada.

=== ANALISIS COMPLETADO EXITOSAMENTE ===
