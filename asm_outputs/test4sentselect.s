Contenido del archivo (212 caracteres):
----------------------------------------
#include <stdio.h>

int main() {

    printf("Iniciando bucle for:\n");
    for (int i = 0; i < 5; i++) {
        printf("Iteracion numero: %d\n", i);
    }
    printf("Bucle for finalizado.\n");
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
PRINTF('printf')
LEFT_PAREN('(')
STRING_LITERAL('"Iniciando bucle for:\n"')
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
FORMAT_STRING('"Iteracion numero: %d\n"')
COMMA(',')
IDENTIFIER('i')
RIGHT_PAREN(')')
SEMICOLON(';')
RIGHT_BRACE('}')
PRINTF('printf')
LEFT_PAREN('(')
STRING_LITERAL('"Bucle for finalizado.\n"')
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
    printf("Iniciando bucle for:\n");
    for (int i = 0; i < 5; i++) {
        printf("Iteracion numero: %d\n", i);
    }
    printf("Bucle for finalizado.\n");
    return 0;
}

Impresion del programa completada.

=== ANALISIS COMPLETADO EXITOSAMENTE ===
