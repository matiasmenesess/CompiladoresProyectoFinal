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

int main() {
    struct Punto p1;
    p1.x = 10;
    p1.y = 20;
    printf("Punto: (%d, %d)\n", p1.x, p1.y);
    return 0;
}
Generando código...
Generando codigo ensamblador en tests/test5struct.s
