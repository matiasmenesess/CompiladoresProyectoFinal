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
    int x = 10;
    int* ptr = &x;
    printf("La direccion de x es: %p\n", ptr);
    return 0;
}
Generando código...
Generando codigo ensamblador en tests/test2punteros.s
