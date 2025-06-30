Inicio del main
Archivo leído correctamente
Scanner completado exitosamente

Parseando...
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
