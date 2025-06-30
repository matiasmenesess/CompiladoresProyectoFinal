Inicio del main
Archivo leído correctamente
Scanner completado exitosamente

Parseando...
Parseo exitoso
Imprimiendo el AST...
#include <stdio.h>


int suma(int&& a, int b) {
    a++;
    return a;
}

int main() {
    int a = 10;
    printf("Entero: %d, Caracter: %c\n", a, 'a');
    int b = 20;
    int resultado = suma(a, b);
    printf("La suma es: %d\n", a);
    return 0;
}
Generando código...
Generando codigo ensamblador en tests/test1func.s
