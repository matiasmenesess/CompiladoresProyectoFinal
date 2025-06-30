Inicio del main
Archivo leído correctamente
Scanner completado exitosamente

Parseando...
Parseo exitoso
Imprimiendo el AST...
#include <stdio.h>


int main() {
    int contador = 5;
    printf("Iniciando bucle while (cuenta regresiva):\n");
    while (contador > 0) {
        printf("%d...\n", contador);
        contador = contador - 1;
    }
    printf("¡Despegue!\n");
    return 0;
}
Generando código...
Generando codigo ensamblador en tests/test6sentselect.s
