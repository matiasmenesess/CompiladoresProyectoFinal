Inicio del main
Archivo leído correctamente
Parseando...
Tipo: int, Puntero: 0, Referencia: 0
Tipo: int, Puntero: 0, Referencia: 0
Tipo: int, Puntero: 1, Referencia: 0
Tipo: int, Puntero: 0, Referencia: 0
Tipo: int, Puntero: 0, Referencia: 0
Parseo exitoso
Imprimiendo el AST...
#include <stdio.h>


int main() {
    int[3] arr = {1, 2, 3};
    int* p = arr;
    int x = *(p + 1);
    int u = arr[2] * (p + 2) = 10;
    return 0;
}
Generando código...
