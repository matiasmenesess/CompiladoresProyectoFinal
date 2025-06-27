Contenido del archivo (272 caracteres):
----------------------------------------
#include <stdio.h>

void cambiar_valor(int* num) {
    *num = 100;
}

int main() {
    int mi_numero = 10;
    printf("Valor antes de la funcion: %d\n", mi_numero);
    cambiar_valor(&mi_numero);
    printf("Valor despues de la funcion: %d\n", mi_numero);
    return 0;
}
----------------------------------------

=== FASE 1: ANÁLISIS LÉXICO ===
Iniciando Scanner:

INCLUDE('#include')
HEADER_NAME('<stdio.h>')
VOID('void')
IDENTIFIER('cambiar_valor')
LEFT_PAREN('(')
INT('int')
MULTIPLY('*')
IDENTIFIER('num')
RIGHT_PAREN(')')
LEFT_BRACE('{')
DEREFERENCE('*')
IDENTIFIER('num')
ASSIGN('=')
NUMBER('100')
SEMICOLON(';')
RIGHT_BRACE('}')
INT('int')
MAIN('main')
LEFT_PAREN('(')
RIGHT_PAREN(')')
LEFT_BRACE('{')
INT('int')
IDENTIFIER('mi_numero')
ASSIGN('=')
NUMBER('10')
SEMICOLON(';')
PRINTF('printf')
LEFT_PAREN('(')
FORMAT_STRING('"Valor antes de la funcion: %d\n"')
COMMA(',')
IDENTIFIER('mi_numero')
RIGHT_PAREN(')')
SEMICOLON(';')
IDENTIFIER('cambiar_valor')
LEFT_PAREN('(')
ADDRESS_OF('&')
IDENTIFIER('mi_numero')
RIGHT_PAREN(')')
SEMICOLON(';')
PRINTF('printf')
LEFT_PAREN('(')
FORMAT_STRING('"Valor despues de la funcion: %d\n"')
COMMA(',')
IDENTIFIER('mi_numero')
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

void cambiar_valor(int* num) {
    *num = 100;
}

int main() {
    int mi_numero = 10;
    printf("Valor antes de la funcion: %d\n", mi_numero);
    cambiar_valor(&mi_numero);
    printf("Valor despues de la funcion: %d\n", mi_numero);
    return 0;
}

Impresion del programa completada.

=== ANALISIS COMPLETADO EXITOSAMENTE ===
