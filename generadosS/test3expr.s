Inicio del main
Archivo leído correctamente
Parseando...
Tipo: int, Puntero: 0, Referencia: 0
Tipo: int, Puntero: 0, Referencia: 0
Tipo: int, Puntero: 0, Referencia: 0
Tipo: bool, Puntero: 0, Referencia: 0
Tipo: bool, Puntero: 0, Referencia: 0
Parseo exitoso
Imprimiendo el AST...
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
Generando código...
Generando codigo ensamblador en tests/test3expr.s
