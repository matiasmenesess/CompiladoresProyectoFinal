Inicio del main
Archivo leído correctamente
Parseando...
Tipo: int, Puntero: 0, Referencia: 0
Tipo: int, Puntero: 0, Referencia: 0
Tipo: int, Puntero: 1, Referencia: 0
Parseo exitoso
Imprimiendo el AST...
#include <stdio.h>


int main() {
    int x = 50;
    int* ptr;
    ptr = &x;
    printf("El valor de x es: %d\n", *ptr);
    return 0;
}
Generando código...
Generando codigo ensamblador en tests/test1punteros.s
