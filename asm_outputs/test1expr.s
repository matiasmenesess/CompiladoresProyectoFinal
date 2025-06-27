Contenido del archivo (113 caracteres):
----------------------------------------
#include <stdio.h>

int main() {
    int x;
    x = 5 + 3 * 2;
    printf("Resultado: %d\n", x);
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
IDENTIFIER('x')
ASSIGN('=')
NUMBER('5')
PLUS('+')
NUMBER('3')
MULTIPLY('*')
NUMBER('2')
SEMICOLON(';')
PRINTF('printf')
LEFT_PAREN('(')
FORMAT_STRING('"Resultado: %d\n"')
COMMA(',')
IDENTIFIER('x')
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

Buscando funciones...
Encontramos el token main
Programa parseado exitosamente

=== FASE 3: VISITANTE DE IMPRESION ===
#include <stdio.h>


int main() {
    int x;
    x = 5 + 3 * 2;
    printf("Resultado: %d\n", x);
    return 0;
}

Impresion del programa completada.

=== ANALISIS COMPLETADO EXITOSAMENTE ===
