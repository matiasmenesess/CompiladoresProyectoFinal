Contenido del archivo (227 caracteres):
----------------------------------------
#include <stdio.h>

int main() {
    char c = 'b';
    if (c == 'a') {
        printf("Es 'a'\n");
    } else if (c == 'b') {
        printf("Es 'b'\n");
    } else {
        printf("Es otro caracter\n");
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
CHAR('char')
IDENTIFIER('c')
ASSIGN('=')
CHARACTER_CONSTANT(''b'')
SEMICOLON(';')
IF('if')
LEFT_PAREN('(')
IDENTIFIER('c')
EQUAL('==')
CHARACTER_CONSTANT(''a'')
RIGHT_PAREN(')')
LEFT_BRACE('{')
PRINTF('printf')
LEFT_PAREN('(')
STRING_LITERAL('"Es 'a'\n"')
RIGHT_PAREN(')')
SEMICOLON(';')
RIGHT_BRACE('}')
ELSE_IF('else if')
LEFT_PAREN('(')
IDENTIFIER('c')
EQUAL('==')
CHARACTER_CONSTANT(''b'')
RIGHT_PAREN(')')
LEFT_BRACE('{')
PRINTF('printf')
LEFT_PAREN('(')
STRING_LITERAL('"Es 'b'\n"')
RIGHT_PAREN(')')
SEMICOLON(';')
RIGHT_BRACE('}')
ELSE('else')
LEFT_BRACE('{')
PRINTF('printf')
LEFT_PAREN('(')
STRING_LITERAL('"Es otro caracter\n"')
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
    char c = 'b';
    if (c == 'a') {
        printf("Es 'a'\n");
    }else if (c == 'b') {
        printf("Es 'b'\n");
    } else {
        printf("Es otro caracter\n");
    }
    return 0;
}

Impresion del programa completada.

=== ANALISIS COMPLETADO EXITOSAMENTE ===
