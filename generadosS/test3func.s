Inicio del main
Archivo leído correctamente
Scanner completado exitosamente

Parseando...
Parseo exitoso
Imprimiendo el AST...
#include <stdio.h>


int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int main() {
    int f = factorial(5);
    printf("Factorial de 5 es: %d\n", f);
    return 0;
}
Generando código...
Generando codigo ensamblador en tests/test3func.s
