Contenido del archivo (218 caracteres):
----------------------------------------
#include <stdio.h>

int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int main() {
    int f = factorial(5);
    printf("Factorial de 5 es: %d\n", f);
    return 0;
}
----------------------------------------

=== FASE 1: ANÁLISIS LÉXICO ===
Iniciando Scanner:

INCLUDE('#include')
HEADER_NAME('<stdio.h>')
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
INT('int')
MAIN('main')
LEFT_PAREN('(')
RIGHT_PAREN(')')
LEFT_BRACE('{')
INT('int')
IDENTIFIER('f')
ASSIGN('=')
IDENTIFIER('factorial')
LEFT_PAREN('(')
NUMBER('5')
RIGHT_PAREN(')')
SEMICOLON(';')
PRINTF('printf')
LEFT_PAREN('(')
FORMAT_STRING('"Factorial de 5 es: %d\n"')
COMMA(',')
IDENTIFIER('f')
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

int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int main() {
    int f = factorial(5);
    printf("Factorial de 5 es: %d\n", f);
    return 0;
}

Impresion del programa completada.

=== ANALISIS COMPLETADO EXITOSAMENTE ===
