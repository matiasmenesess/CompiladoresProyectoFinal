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
    struct Punto p;
    p.x = 5;
    p.y = p.x * 2;
    printf("p.y deberia ser 10: %d\n", p.y);
    return 0;
}
Generando código...
