Contenido del archivo (216 caracteres):
----------------------------------------
#include <stdio.h>

int main() {
    int y = 20;
    int* p = &y;
    printf("Valor original de y: %d\n", y);
    *p = 30; // Modificar y a traves del puntero
    printf("Nuevo valor de y: %d\n", y);
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
NUMBER('20')
SEMICOLON(';')
INT('int')
MULTIPLY('*')
IDENTIFIER('p')
ASSIGN('=')
ADDRESS_OF('&')
IDENTIFIER('y')
SEMICOLON(';')
PRINTF('printf')
LEFT_PAREN('(')
FORMAT_STRING('"Valor original de y: %d\n"')
COMMA(',')
IDENTIFIER('y')
RIGHT_PAREN(')')
SEMICOLON(';')
DEREFERENCE('*')
IDENTIFIER('p')
ASSIGN('=')
NUMBER('30')
SEMICOLON(';')
LINE_COMMENT('// Modificar y a traves del puntero
')
PRINTF('printf')
LEFT_PAREN('(')
FORMAT_STRING('"Nuevo valor de y: %d\n"')
COMMA(',')
IDENTIFIER('y')
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

Error durante el analisis: Se esperaba una expresión primaria (numero, identificador, cadena, parentesis). Se obtuvo el token // Modificar y a traves del puntero

