Inicio del main
Archivo leído correctamente
Parseando...
Tipo: void, Puntero: 0, Referencia: 0
Tipo: int, Puntero: 0, Referencia: 0
tipo encontrado para el parametro: int 0 0 0
array
array
is_ref: 0
Tipo: int, Puntero: 0, Referencia: 0
tipo encontrado para el parametro: int 0 0 0
is_ref: 0
Tipo: int, Puntero: 0, Referencia: 0
Tipo: int, Puntero: 0, Referencia: 0
Tipo: int, Puntero: 0, Referencia: 0
Parseo exitoso
Imprimiendo el AST...
#include <stdio.h>


void llenar(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        arr[i] = i;
    }
}

int main() {
    int[10] datos;
    llenar(datos, 10);
    return 0;
}
Generando código...
Variable no declarada: i
