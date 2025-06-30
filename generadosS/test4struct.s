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
    struct Punto p;
    p.x = 5;
    p.y = p.x * 2;
    printf("p.y deberia ser 10: %d\n", p.y);
    return 0;
}
Generando código...
Generando codigo ensamblador en tests/test4struct.s
