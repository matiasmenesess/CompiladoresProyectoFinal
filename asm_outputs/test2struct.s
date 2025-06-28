Contenido del archivo (230 caracteres):
----------------------------------------
#include <stdio.h>

struct Libro {
    char* titulo;
    int anio;
};

int main() {
    struct Libro mi_libro = {"C Programming", 1978};
    printf("Libro: %s, Publicado en: %d\n", mi_libro.titulo, mi_libro.anio);
    return 0;
}
----------------------------------------

=== FASE 1: ANÁLISIS LÉXICO ===
Iniciando Scanner:

INCLUDE('#include')
HEADER_NAME('<stdio.h>')
STRUCT('struct')
IDENTIFIER('Libro')
LEFT_BRACE('{')
CHAR('char')
MULTIPLY('*')
IDENTIFIER('titulo')
SEMICOLON(';')
INT('int')
IDENTIFIER('anio')
SEMICOLON(';')
RIGHT_BRACE('}')
SEMICOLON(';')
INT('int')
MAIN('main')
LEFT_PAREN('(')
RIGHT_PAREN(')')
LEFT_BRACE('{')
STRUCT('struct')
IDENTIFIER('Libro')
IDENTIFIER('mi_libro')
ASSIGN('=')
LEFT_BRACE('{')
STRING_LITERAL('"C Programming"')
COMMA(',')
NUMBER('1978')
RIGHT_BRACE('}')
SEMICOLON(';')
PRINTF('printf')
LEFT_PAREN('(')
FORMAT_STRING('"Libro: %s, Publicado en: %d\n"')
COMMA(',')
IDENTIFIER('mi_libro')
DOT('.')
IDENTIFIER('titulo')
COMMA(',')
IDENTIFIER('mi_libro')
DOT('.')
IDENTIFIER('anio')
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


struct Libro {
    char* titulo;
    int anio;
};

int main() {
    struct Libro mi_libro = {""C Programming"", 1978};
    printf("Libro: %s, Publicado en: %d\n", mi_libro.titulo, mi_libro.anio);
    return 0;
}

Impresion del programa completada.

=== ANALISIS COMPLETADO EXITOSAMENTE ===
