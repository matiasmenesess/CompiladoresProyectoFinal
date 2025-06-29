Inicio del main
Archivo leído correctamente
Parseando...
Tipo: void, Puntero: 0, Referencia: 0
Tipo: int, Puntero: 1, Referencia: 0
tipo encontrado para el parametro: int 1 0 0
is_ref: 0
Tipo: int, Puntero: 0, Referencia: 0
Tipo: int, Puntero: 0, Referencia: 0
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
