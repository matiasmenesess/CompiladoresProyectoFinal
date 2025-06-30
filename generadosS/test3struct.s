Inicio del main
Archivo leído correctamente
Scanner completado exitosamente

Parseando...
Parseo exitoso
Imprimiendo el AST...
#include <stdio.h>


struct Punto {
    int x;
    int y;
};

struct Rectangulo {
    struct Punto top_left;
    int ancho;
    int alto;
};

int main() {
    struct Rectangulo r;
    r.top_left.x = 0;
    r.top_left.y = 0;
    r.ancho = 100;
    printf("Rectangulo en (%d, %d)\n", r.top_left.x, r.top_left.y);
    return 0;
}
Generando código...
Generando codigo ensamblador en tests/test3struct.s
