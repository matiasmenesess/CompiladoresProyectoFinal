Contenido del archivo (159 caracteres):
----------------------------------------
#include <stdio.h>

int main() {
    int x = 1, y = 0;
    if (x == 1 && y == 0) {
        printf("Ambas condiciones son verdaderas\n");
    }
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
ASSIGN('=')
NUMBER('1')
COMMA(',')
IDENTIFIER('y')
ASSIGN('=')
NUMBER('0')
SEMICOLON(';')
IF('if')
LEFT_PAREN('(')
IDENTIFIER('x')
EQUAL('==')
NUMBER('1')
LOGICAL_AND('&&')
IDENTIFIER('y')
EQUAL('==')
NUMBER('0')
RIGHT_PAREN(')')
LEFT_BRACE('{')
PRINTF('printf')
LEFT_PAREN('(')
STRING_LITERAL('"Ambas condiciones son verdaderas\n"')
RIGHT_PAREN(')')
SEMICOLON(';')
RIGHT_BRACE('}')
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
    int x = 1, y = 0;
    if (x == 1 && y == 0) {
        printf("Ambas condiciones son verdaderas\n");
    }
    return 0;
}

Impresion del programa completada.

=== ANALISIS COMPLETADO EXITOSAMENTE ===
