Inicio del main
Archivo leído correctamente
Parseando...
Tipo: int, Puntero: 0, Referencia: 0
Tipo: int, Puntero: 0, Referencia: 0
Tipo: int, Puntero: 0, Referencia: 0
Tipo: struct Punto, Puntero: 0, Referencia: 0
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
