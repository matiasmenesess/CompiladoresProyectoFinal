#include <iostream>
#include <fstream>
#include <string>
#include "scanner.h"
#include "parser.h"
#include "expression.h"

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

    string input;
    string line;
    while (getline(infile, line)) {
        input += line + '\n';
    }
    infile.close();

    if (input.empty()) {
        cout << "El archivo está vacío." << endl;
        return 1;
    }

    cout << "Contenido del archivo (" << input.size() << " caracteres):\n";
    cout << "----------------------------------------\n";
    cout << input;
    cout << "----------------------------------------\n\n";

    try {
        cout << "=== FASE 1: ANÁLISIS LÉXICO ===" << endl;
        Scanner scanner(input.c_str());
        test_scanner(&scanner);
        cout << "Scanner completado exitosamente\n" << endl;

        cout << "=== FASE 2: PARSER ===" << endl;

        Scanner parser_scanner(input.c_str());
        Parser parser(&parser_scanner);

        cout << "Iniciando parser..." << endl;
        Program* program = parser.parseProgram();

        cout << "parser completado exitosamente!" << endl;
        cout << "Programa parseado correctamente." << endl;

        cout << "\n=== INFORMACIÓN DEL PROGRAMA ===" << endl;
        cout << "✓ Programa parseado exitosamente" << endl;
        cout << "✓ Estructura del AST creada" << endl;

        delete program;

    } catch (const exception& e) {
        cout << "\nError durante el analisis: " << e.what() << endl;
        return 1;
    } catch (...) {
        cout << "\nError desconocido durante el análisis" << endl;
        return 1;
    }

    cout << "\n=== ANALISIS COMPLETADO EXITOSAMENTE ===" << endl;
    return 0;
}
