Contenido del archivo (131 caracteres):
----------------------------------------
#include <stdio.h>

int main() {
    int x = 10;
    int* ptr = &x;
    printf("La direccion de x es: %p\n", ptr);
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
NUMBER('10')
SEMICOLON(';')
INT('int')
MULTIPLY('*')
IDENTIFIER('ptr')
ASSIGN('=')
ADDRESS_OF('&')
IDENTIFIER('x')
SEMICOLON(';')
PRINTF('printf')
LEFT_PAREN('(')
FORMAT_STRING('"La direccion de x es: %p\n"')
COMMA(',')
IDENTIFIER('ptr')
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
    int x = 10;
    int* ptr = &x;
    printf("La direccion de x es: %p\n", ptr);
    return 0;
}

Impresion del programa completada.

=== ANALISIS COMPLETADO EXITOSAMENTE ===
