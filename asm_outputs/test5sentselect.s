Contenido del archivo (277 caracteres):
----------------------------------------
#include <stdio.h>

int main() {
    int i, j;
    printf("Iniciando bucles anidados:\n");
    for (i = 1; i <= 3; i++) {
        for (j = 1; j <= 2; j++) {
            printf("i=%d, j=%d\n", i, j);
        }
    }
    printf("Bucles anidados finalizados.\n");
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
IDENTIFIER('i')
COMMA(',')
IDENTIFIER('j')
SEMICOLON(';')
PRINTF('printf')
LEFT_PAREN('(')
STRING_LITERAL('"Iniciando bucles anidados:\n"')
RIGHT_PAREN(')')
SEMICOLON(';')
FOR('for')
LEFT_PAREN('(')
IDENTIFIER('i')
ASSIGN('=')
NUMBER('1')
SEMICOLON(';')
IDENTIFIER('i')
LESS_EQUAL('<=')
NUMBER('3')
SEMICOLON(';')
IDENTIFIER('i')
INCREMENT('++')
RIGHT_PAREN(')')
LEFT_BRACE('{')
FOR('for')
LEFT_PAREN('(')
IDENTIFIER('j')
ASSIGN('=')
NUMBER('1')
SEMICOLON(';')
IDENTIFIER('j')
LESS_EQUAL('<=')
NUMBER('2')
SEMICOLON(';')
IDENTIFIER('j')
INCREMENT('++')
RIGHT_PAREN(')')
LEFT_BRACE('{')
PRINTF('printf')
LEFT_PAREN('(')
FORMAT_STRING('"i=%d, j=%d\n"')
COMMA(',')
IDENTIFIER('i')
COMMA(',')
IDENTIFIER('j')
RIGHT_PAREN(')')
SEMICOLON(';')
RIGHT_BRACE('}')
RIGHT_BRACE('}')
PRINTF('printf')
LEFT_PAREN('(')
STRING_LITERAL('"Bucles anidados finalizados.\n"')
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
Error: se esperaba un tipo (int, char, void, struct).
