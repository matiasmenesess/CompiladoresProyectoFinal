#include <iostream>
#include <fstream>
#include <string>
#include "scanner.h"
#include "parser.h"
#include "visitor.h"
using namespace std;
int main(int argc, const char *argv[]){
    cout << "Inicio del main" << endl;
    if (argc != 2)
    {
        cout << "Numero incorrecto de argumentos. Uso: " << argv[0] << " <archivo_de_entrada>" << endl;
        exit(1);
    }
    ifstream infile(argv[1]);
    if (!infile.is_open())
    {
        cout << "No se pudo abrir el archivo: " << argv[1] << endl;
        exit(1);
    }
    string input;
    string line;
    while (getline(infile, line))
    {
        input += line + '\n';
    }
    infile.close();
    cout << "Archivo leído correctamente" << endl;
    Scanner scanner(input.c_str());
    Parser parser(&scanner);
    try
    {
        cout << "Parseando..." << endl;
        Program *program = parser.parseProgram();
        cout << "Parseo exitoso" << endl;
        string inputFile(argv[1]);
        size_t dotPos = inputFile.find_last_of('.');
        string baseName = (dotPos == string::npos) ? inputFile : inputFile.substr(0, dotPos);
        string outputFilename = baseName + ".s";
        ofstream outfile(outputFilename);
        if (!outfile.is_open())
        {
            cerr << "Error al crear el archivo de salida: " << outputFilename << endl;
            delete program;
            return 1;
        }
        cout << "Generando código..." << endl;
        GenCodeVisitor codigo(outfile);
        codigo.gencode(program);
        cout << "Generando codigo ensamblador en " << outputFilename << endl;
        outfile.close();
        delete program;
    }

    catch (const exception &e){
        cout << "Error durante la ejecución: " << e.what() << endl;
        return 1;
    }
    return 0;
}
