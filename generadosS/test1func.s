Inicio del main
Archivo leído correctamente
Parseando...
Tipo: int, Puntero: 0, Referencia: 0
Tipo: int, Puntero: 0, Referencia: 0
Tipo: int, Puntero: 0, Referencia: 0
Tipo: void, Puntero: 0, Referencia: 0
tipo encontrado para el parametro: void 0 0 0
is_ref: 0
Tipo: char, Puntero: 0, Referencia: 0
tipo encontrado para el parametro: char 0 0 0
is_ref: 0
Tipo: int, Puntero: 0, Referencia: 0
Tipo: int, Puntero: 0, Referencia: 0
Parseo exitoso
Imprimiendo el AST...
#include <stdio.h>

int resta = -11;
int maximo = 100 / 2;

int suma(void a, char b) {
    return a + b;
}

int main() {
    int resultado = suma(5, 3);
    printf("La suma es: %d\n", resultado);
    return 0;
}
Generando código...
Generando codigo ensamblador en tests/test1func.s
