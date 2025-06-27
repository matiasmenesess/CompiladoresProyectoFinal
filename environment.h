//
// Created by zamirlm on 6/23/25.
//

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;


struct FunctionInfo {
    string return_type;
    vector<pair<string, string>> params; // {param_type, param_name}
};
struct StructInfo {
    unordered_map<string, string> fields; // nombre_campo -> tipo
};


class Environment {
private:
    vector<unordered_map<string, int>> levels;  // Almacena valores de variables
    vector<unordered_map<string, string>> type_levels;  // Almacena tipos de variables
    unordered_map<string, FunctionInfo> functions;  // Almacena información de funciones
    unordered_map<string, StructInfo> structs;

    int search_rib(string var) {
        int idx = levels.size() - 1;
        while (idx >= 0) {
            if (levels[idx].find(var) != levels[idx].end()) {
                return idx;
            }
            idx--;
        }
        return -1;
    }
public:
    Environment() {}
    void clear() {
        levels.clear();
        type_levels.clear();
    }
    // Añadir un nuevo nivel
    void add_level() {
        unordered_map<string, int> l;
        unordered_map<string, string> t;  // Mapa para tipos
        levels.push_back(l);
        type_levels.push_back(t);
    }
    // Añadir una variable con su valor y tipo
    void add_var(string var, int value, string type) {
        if (levels.size() == 0) {
            cout << "Environment sin niveles: no se pueden agregar variables" << endl;
            exit(0);
        }
        levels.back()[var] = value;
        type_levels.back()[var] = type;
    }
    // Añadir una variable sin valor inicial
    void add_var(string var, string type) {
        levels.back()[var] = 0;  // Valor por defecto
        type_levels.back()[var] = type;
    }
    // Remover un nivel
    bool remove_level() {
        if (levels.size() > 0) {
            levels.pop_back();
            type_levels.pop_back();
            return true;
        }
        return false;
    }
    // Actualizar el valor de una variable
    bool update(string x, int v) {
        int idx = search_rib(x);
        if (idx < 0) return false;
        levels[idx][x] = v;
        return true;
    }
    // Verificar si una variable está declarada
    bool check(string x) {
        int idx = search_rib(x);
        return (idx >= 0);
    }


    // Obtener el valor de una variable

    int lookup(string x) {
        int idx = search_rib(x);
        if (idx < 0) {
            cout << "Variable no declarada: " << x << endl;
            exit(0);
        }
        return levels[idx][x];
    }


    // Obtener el tipo de una variable

    string lookup_type(string x) {
        int idx = search_rib(x);
        if (idx < 0) {
            cout << "Variable no declarada: " << x << endl;
            exit(0);
        }
        return type_levels[idx][x];
    }
    // Verificar el tipo de una variable antes de asignar un valor
    bool typecheck(string var, string expected_type) {
        string actual_type = lookup_type(var);
        if (actual_type != expected_type) {
            cout << "Error de tipo: se esperaba " << expected_type << " pero se encontró " << actual_type << " para la variable " << var << endl;
            return false;
        }
        return true;
    }
    void add_function(const string& name, const FunctionInfo& info) {
        functions[name] = info;
    }

    bool has_function(const string& name) {
        return functions.find(name) != functions.end();
    }

    FunctionInfo get_function(const string& name) {
        if (!has_function(name)) {
            cout << "Función no declarada: " << name << endl;
            exit(0);
        }
        return functions[name];
    }
     void add_struct(const string& name, const StructInfo& info) {
        structs[name] = info;
    }

    bool has_struct(const string& name) {
        return structs.find(name) != structs.end();
    }

    StructInfo get_struct(const string& name) {
        if (!has_struct(name)) {
            cout << "Struct no declarado: " << name << endl;
            exit(0);
        }
        return structs[name];
    }
};

#endif //ENVIRONMENT_H
