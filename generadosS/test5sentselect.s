Inicio del main
Archivo leído correctamente
Parseando...
Tipo: int, Puntero: 0, Referencia: 0
Tipo: int, Puntero: 0, Referencia: 0
Tipo: int, Puntero: 0, Referencia: 0
Parseo exitoso
Imprimiendo el AST...
#include <stdio.h>


int main() {
    printf("Iniciando bucles anidados:\n");
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 2; j++) {
            printf("i=%d, j=%d\n", i, j);
        }
    }
    printf("Bucles anidados finalizados.\n");
    return 0;
}
Generando código...
Variable no declarada: i
