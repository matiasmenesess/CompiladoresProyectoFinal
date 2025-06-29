Inicio del main
Archivo leído correctamente
Parseando...
Tipo: char, Puntero: 1, Referencia: 0
Tipo: int, Puntero: 0, Referencia: 0
Tipo: int, Puntero: 0, Referencia: 0
Tipo: struct Libro, Puntero: 0, Referencia: 0
Parseo exitoso
Imprimiendo el AST...
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
Generando código...
Generando codigo ensamblador en tests/test2struct.s
