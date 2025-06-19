#include <iostream>
#include <fstream>
#include <string>
#include "scanner.h"

using namespace std;

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        cout << "Numero incorrecto de argumentos. Uso: " << argv[0] << " <archivo_de_entrada>" << endl;
        return 1;
    }

    ifstream infile(argv[1]);
    if (!infile.is_open()) {
        cout << "No se pudo abrir el archivo: " << argv[1] << endl;
        return 1;
    }

    // Leer el archivo completo
    string input;
    string line;
    while (getline(infile, line)) {
        input += line + '\n';
    }
    infile.close();

    // Verificar que el archivo no esté vacío
    if (input.empty()) {
        cout << "El archivo está vacío." << endl;
        return 1;
    }

    cout << "Contenido del archivo (" << input.size() << " caracteres):\n";
    cout << "----------------------------------------\n";
    cout << input;
    cout << "----------------------------------------\n\n";

    try {
        Scanner scanner(input.c_str());
        test_scanner(&scanner);
        cout << "\nScanner completado exitosamente" << endl;
    } catch (const exception& e) {
        cout << "\nError durante el escaneo: " << e.what() << endl;
        return 1;
    }

    return 0;
}