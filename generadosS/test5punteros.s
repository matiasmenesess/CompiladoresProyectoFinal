Inicio del main
Archivo leído correctamente
Scanner completado exitosamente

Parseando...
Parseo exitoso
Imprimiendo el AST...
#include <stdio.h>


int main() {
    int y = 20;
    int* p = &y;
    printf("Valor original de y: %d\n", y);
    *p = 30;
    printf("Nuevo valor de y: %d\n", y);
    return 0;
}
Generando código...
Generando codigo ensamblador en tests/test5punteros.s
