Contenido del archivo (115 caracteres):
----------------------------------------
#include <stdio.h>

int main() {
    int y = 5;
    int z = ++y;
    printf("Resultado: %d\n", z);
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
PRINTF('printf')
LEFT_PAREN('(')
FORMAT_STRING('"Resultado: %d\n"')
COMMA(',')
IDENTIFIER('z')
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
    int y = 5;
    int z = ++y;
    printf("Resultado: %d\n", z);
    return 0;
}

Impresion del programa completada.

=== ANALISIS COMPLETADO EXITOSAMENTE ===
