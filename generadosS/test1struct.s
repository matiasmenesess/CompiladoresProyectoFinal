Inicio del main
Archivo leído correctamente
Scanner completado exitosamente

Parseando...
Parseo exitoso
Imprimiendo el AST...
#include <stdio.h>


struct Persona {
    char* nombre;
    int edad;
};

int main() {
    char* mensaje = "Hola mundo!";
    int x = 5 / 1;
    int* ptr = &x;
    struct Persona p = {"Juan", 20};
    printf("Mensaje: %s\n", mensaje);
    printf("Persona: %s, %d anos\n", p.nombre, p.edad);
    return 0;
}
Generando código...
Generando codigo ensamblador en tests/test1struct.s
