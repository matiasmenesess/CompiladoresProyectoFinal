Inicio del main
Archivo leído correctamente
Scanner completado exitosamente

Parseando...
Parseo exitoso
Imprimiendo el AST...
#include <stdio.h>


void cambiar_valor(int* num) {
    *num = 100;
}

int main() {
    int mi_numero = 10;
    printf("Valor antes de la funcion: %d\n", mi_numero);
    cambiar_valor(&mi_numero);
    printf("Valor despues de la funcion: %d\n", mi_numero);
    return 0;
}
Generando código...
Generando codigo ensamblador en tests/test4punteros.s
