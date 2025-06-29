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
    int y = 20;
    int* p = &y;
    printf("Valor original de y: %d\n", y);
    *p = 30;
    printf("Nuevo valor de y: %d\n", y);
    return 0;
}
Generando código...
