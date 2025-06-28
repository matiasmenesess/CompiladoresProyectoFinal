Contenido del archivo (481 caracteres):
----------------------------------------
#include <stdio.h>

int main() {
    int y = 5;
    int z = ++y;
    bool f = true;
    bool g = false;
    if (f && g){
        if (1>8){
            printf("Resultado: %d\n", z);

        }else{
            printf("Resultado: %d\n", z);

        }

    }
    else if (f || g){
        if (1>8){
            printf("Resultado: %d\n", z);

        }else{
            printf("Resultado: %d\n", z);

        }

    }else{
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
BOOL('bool')
IDENTIFIER('f')
ASSIGN('=')
TRUE('')
SEMICOLON(';')
BOOL('bool')
IDENTIFIER('g')
ASSIGN('=')
FALSE('')
SEMICOLON(';')
IF('if')
LEFT_PAREN('(')
IDENTIFIER('f')
LOGICAL_AND('&&')
IDENTIFIER('g')
RIGHT_PAREN(')')
LEFT_BRACE('{')
IF('if')
LEFT_PAREN('(')
NUMBER('1')
GREATER_THAN('>')
NUMBER('8')
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
ELSE('else')
LEFT_BRACE('{')
PRINTF('printf')
LEFT_PAREN('(')
FORMAT_STRING('"Resultado: %d\n"')
COMMA(',')
IDENTIFIER('z')
RIGHT_PAREN(')')
SEMICOLON(';')
RIGHT_BRACE('}')
RIGHT_BRACE('}')
ELSE_IF('else if')
LEFT_PAREN('(')
IDENTIFIER('f')
LOGICAL_OR('||')
IDENTIFIER('g')
RIGHT_PAREN(')')
LEFT_BRACE('{')
IF('if')
LEFT_PAREN('(')
NUMBER('1')
GREATER_THAN('>')
NUMBER('8')
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
ELSE('else')
LEFT_BRACE('{')
PRINTF('printf')
LEFT_PAREN('(')
FORMAT_STRING('"Resultado: %d\n"')
COMMA(',')
IDENTIFIER('z')
RIGHT_PAREN(')')
SEMICOLON(';')
RIGHT_BRACE('}')
RIGHT_BRACE('}')
ELSE('else')
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

Programa parseado exitosamente

=== FASE 3: VISITANTE DE IMPRESION ===
#include <stdio.h>


int main() {
    int y = 5;
    int z = ++y;
    bool f = true;
    bool g = false;
    if (f && g) {
        if (1 > 8) {
            printf("Resultado: %d\n", z);
        } else {
            printf("Resultado: %d\n", z);
        }
    }else if (f || g) {
        if (1 > 8) {
            printf("Resultado: %d\n", z);
        } else {
            printf("Resultado: %d\n", z);
        }
    } else {
        printf("Resultado: %d\n", z);
    }
    return 0;
}

Impresion del programa completada.

=== ANALISIS COMPLETADO EXITOSAMENTE ===
