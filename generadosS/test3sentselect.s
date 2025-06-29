Inicio del main
Archivo leído correctamente
Parseando...
Tipo: int, Puntero: 0, Referencia: 0
Tipo: char, Puntero: 0, Referencia: 0
Parseo exitoso
Imprimiendo el AST...
#include <stdio.h>


int main() {
    char c = 'b';
    if (c == 'a') {
        printf("Es 'a'\n");
    }else if (c == 'b') {
        printf("Es 'b'\n");
    } else {
        printf("Es otro caracter\n");
    }
    return 0;
}
Generando código...
Generando codigo ensamblador en tests/test3sentselect.s
