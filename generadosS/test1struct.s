Inicio del main
Archivo leído correctamente
Parseando...
Tipo: char, Puntero: 1, Referencia: 0
Tipo: int, Puntero: 0, Referencia: 0
Tipo: int, Puntero: 0, Referencia: 0
Tipo: int, Puntero: 0, Referencia: 0
tipo encontrado para el parametro: int 0 0 0
is_ref: 0
Tipo: int, Puntero: 0, Referencia: 0
Tipo: char, Puntero: 1, Referencia: 0
Tipo: int, Puntero: 0, Referencia: 0
Tipo: int, Puntero: 1, Referencia: 0
Tipo: struct Persona, Puntero: 0, Referencia: 0
Tipo: int, Puntero: 0, Referencia: 0
Parseo exitoso
Imprimiendo el AST...
#include <stdio.h>


struct Persona {
    char* nombre;
    int edad;
};

int factorial(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int main() {
    char* mensaje = ""Hola mundo!"";
    int x = 5 / 1;
    int* ptr = &x;
    struct Persona p = {""Juan"", 20};
    printf("Mensaje: %s\n", mensaje);
    printf("Factorial de %d es %d\n", x, factorial(x));
    printf("Persona: %s, %d anos\n", p.nombre, p.edad);
    for (int i = 0; i < 5; i++) {
        printf("%d ", i);
        if (i % 2 == 0) {
            printf("(par)");
        }else if (i % 2 != 0) {
            printf("(impar)");
        } else {
            printf("(otro)");
        }
    }
    return 0;
}
Generando código...
Variable no declarada: i
