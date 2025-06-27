Contenido del archivo (182 caracteres):
----------------------------------------
#include <stdio.h>

int main() {
    int y = 5;
    int z = ++y;
    bool f = true;
    bool g = false;
    if (f && g){
        printf("Resultado: %d\n", z);

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
IDENTIFIER('y')
ASSIGN('=')
NUMBER('5')
SEMICOLON(';')
INT('int')
IDENTIFIER('z')
ASSIGN('=')
INCREMENT('++')
IDENTIFIER('y')
SEMICOLON(';')
IDENTIFIER('bool')
IDENTIFIER('f')
ASSIGN('=')
IDENTIFIER('true')
SEMICOLON(';')
IDENTIFIER('bool')
IDENTIFIER('g')
ASSIGN('=')
IDENTIFIER('false')
SEMICOLON(';')
IF('if')
LEFT_PAREN('(')
IDENTIFIER('f')
LOGICAL_AND('&&')
IDENTIFIER('g')
RIGHT_PAREN(')')
LEFT_BRACE('{')
PRINTF('printf')
LEFT_PAREN('(')
FORMAT_STRING('"Resultado: %d\n"')
COMMA(',')
IDENTIFIER('z')
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


Error durante el analisis: Se esperaba ';' despues de la expresion.
