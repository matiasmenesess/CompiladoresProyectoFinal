Contenido del archivo (124 caracteres):
----------------------------------------
#include <stdio.h>

void imprimir_hola() {
    printf("Hola Mundo\n");
}

int main() {
    imprimir_hola();
    return 0;
}
----------------------------------------

=== FASE 1: ANÁLISIS LÉXICO ===
Iniciando Scanner:

INCLUDE('#include')
HEADER_NAME('<stdio.h>')
VOID('void')
IDENTIFIER('imprimir_hola')
LEFT_PAREN('(')
RIGHT_PAREN(')')
LEFT_BRACE('{')
PRINTF('printf')
LEFT_PAREN('(')
STRING_LITERAL('"Hola Mundo\n"')
RIGHT_PAREN(')')
SEMICOLON(';')
RIGHT_BRACE('}')
INT('int')
MAIN('main')
LEFT_PAREN('(')
RIGHT_PAREN(')')
LEFT_BRACE('{')
IDENTIFIER('imprimir_hola')
LEFT_PAREN('(')
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

void imprimir_hola() {
    printf("Hola Mundo\n");
}

int main() {
    imprimir_hola();
    return 0;
}

Impresion del programa completada.

=== ANALISIS COMPLETADO EXITOSAMENTE ===
