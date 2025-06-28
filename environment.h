#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;


struct FieldInfo {
    std::string type_name;
    bool is_pointer;
    bool is_array;
};

struct StructInfo {
    std::unordered_map<std::string, FieldInfo> fields; // nombre_campo -> info de campo
    std::unordered_map<std::string, int> offsets;      // nombre_campo -> offset en bytes
    int size = 0;                                      // tamaño total del struct
};
struct VarInfo {
    int offset;
    string type;
    bool is_pointer;
    bool is_array;
    int valor; // Valor actual (útil para interpretación o debug)
};
struct FunctionParamInfo : public VarInfo {
    int reg_index;
};
struct FunctionInfo {
    std::string return_type;
    std::vector<FunctionParamInfo> params;
    int stack_size; 
};


class Environment {
private:
    vector<unordered_map<string, VarInfo>> levels; // Almacena toda la info de la variable
    unordered_map<string, FunctionInfo> functions;
    unordered_map<string, StructInfo> structs;

    int search_rib(const string& var) {
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
    }

    // Añadir un nuevo nivel
    void add_level() {
        unordered_map<string, VarInfo> new_level;
        levels.push_back(new_level);
    }

    // Añadir una variable
    void add_var(const string& var, int offset, const string& type, bool is_ptr = false, bool is_array = false, int valor = 0) {
        if (levels.empty()) {
            cout << "Environment sin niveles: no se pueden agregar variables" << endl;
            exit(0);
        }
        VarInfo info = {offset, type, is_ptr, is_array, valor};
        levels.back()[var] = info;
    }

    // Remover un nivel
    bool remove_level() {
        if (!levels.empty()) {
            levels.pop_back();
            return true;
        }
        return false;
    }

    // Actualizar el valor de una variable
    bool update(const string& x, int v) {
        int idx = search_rib(x);
        if (idx < 0) return false;
        levels[idx][x].valor = v;
        return true;
    }

    // Verificar si una variable está declarada
    bool check(const string& x) {
        int idx = search_rib(x);
        return (idx >= 0);
    }

    // Obtener la información de una variable
    VarInfo lookup(const string& x) {
        int idx = search_rib(x);
        if (idx < 0) {
            cout << "Variable no declarada: " << x << endl;
            exit(0);
        }
        return levels[idx][x];
    }

    // Obtener el tipo de una variable
    string lookup_type(const string& x) {
        return lookup(x).type;
    }

    // Verificar el tipo de una variable antes de asignar un valor
    bool typecheck(const string& var, const string& expected_type) {
        string actual_type = lookup_type(var);
        if (actual_type != expected_type) {
            cout << "Error de tipo: se esperaba " << expected_type << " pero se encontró " << actual_type << " para la variable " << var << endl;
            return false;
        }
        return true;
    }

    // Funciones
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

    // Structs
    int get_struct_size(const std::string& name) {
        if (!has_struct(name)) {
            std::cout << "Struct no declarado: " << name << std::endl;
            exit(0);
        }
        return structs[name].size;
    }
    void add_struct(const std::string& name, const StructInfo& info) {
        structs[name] = info;
    }

    int get_struct_member_offset(const string& struct_name, const string& member_name) {
        if (!has_struct(struct_name)) {
            cout << "Struct no declarado: " << struct_name << endl;
            exit(0);
        }
        const auto& info = structs[struct_name];
        if (info.offsets.find(member_name) == info.offsets.end()) {
            cout << "Miembro no encontrado: " << member_name << " en struct " << struct_name << endl;
            exit(0);
        }
        return info.offsets.at(member_name);
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

#endif // ENVIRONMENT_H