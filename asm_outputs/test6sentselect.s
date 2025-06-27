Contenido del archivo (262 caracteres):
----------------------------------------
#include <stdio.h>

int main() {
    int contador = 5;
    printf("Iniciando bucle while (cuenta regresiva):\n");
    while (contador > 0) {
        printf("%d...\n", contador);
        contador = contador - 1;
    }
    printf("¡Despegue!\n");
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
IDENTIFIER('contador')
ASSIGN('=')
NUMBER('5')
SEMICOLON(';')
PRINTF('printf')
LEFT_PAREN('(')
STRING_LITERAL('"Iniciando bucle while (cuenta regresiva):\n"')
RIGHT_PAREN(')')
SEMICOLON(';')
WHILE('while')
LEFT_PAREN('(')
IDENTIFIER('contador')
GREATER_THAN('>')
NUMBER('0')
RIGHT_PAREN(')')
LEFT_BRACE('{')
PRINTF('printf')
LEFT_PAREN('(')
FORMAT_STRING('"%d...\n"')
COMMA(',')
IDENTIFIER('contador')
RIGHT_PAREN(')')
SEMICOLON(';')
IDENTIFIER('contador')
ASSIGN('=')
IDENTIFIER('contador')
MINUS('-')
NUMBER('1')
SEMICOLON(';')
RIGHT_BRACE('}')
PRINTF('printf')
LEFT_PAREN('(')
STRING_LITERAL('"¡Despegue!\n"')
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
    int contador = 5;
    printf("Iniciando bucle while (cuenta regresiva):\n");
    while (contador > 0) {
        printf("%d...\n", contador);
        contador = contador - 1;
    }
    printf("¡Despegue!\n");
    return 0;
}

Impresion del programa completada.

=== ANALISIS COMPLETADO EXITOSAMENTE ===
