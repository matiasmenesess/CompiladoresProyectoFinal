Contenido del archivo (162 caracteres):
----------------------------------------
#include <stdio.h>

int main() {
    int a = 1, b = 0;
    if (a == 1 || b == 1) {
        printf("Al menos una condicion es verdadera\n");
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
IDENTIFIER('a')
ASSIGN('=')
NUMBER('1')
COMMA(',')
IDENTIFIER('b')
ASSIGN('=')
NUMBER('0')
SEMICOLON(';')
IF('if')
LEFT_PAREN('(')
IDENTIFIER('a')
EQUAL('==')
NUMBER('1')
LOGICAL_OR('||')
IDENTIFIER('b')
EQUAL('==')
NUMBER('1')
RIGHT_PAREN(')')
LEFT_BRACE('{')
PRINTF('printf')
LEFT_PAREN('(')
STRING_LITERAL('"Al menos una condicion es verdadera\n"')
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

Buscando funciones...
Encontramos el token main
Programa parseado exitosamente

=== FASE 3: VISITANTE DE IMPRESION ===
#include <stdio.h>


int main() {
    int a = 1, b = 0;
    if (a == 1 || b == 1) {
        printf("Al menos una condicion es verdadera\n");
    }
    return 0;
}

Impresion del programa completada.

=== ANALISIS COMPLETADO EXITOSAMENTE ===
