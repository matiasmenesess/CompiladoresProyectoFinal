# CompiladoresProyectoFinal
C, STRUCT, PUNTEROS
# Compilador con Soporte para Structs y Punteros en x86-64

Este README documenta la implementación de un compilador que soporta estructuras (structs) y punteros, generando código ensamblador x86-64 optimizado.

## Tabla de Contenidos
- [Arquitectura General](#arquitectura-general)
- [Manejo de Structs](#manejo-de-structs)
- [Sistema de Punteros](#sistema-de-punteros)
- [Acceso a Miembros](#acceso-a-miembros)
- [Generación de Código x86-64](#generación-de-código-x86-64)
- [Ejemplos Completos](#ejemplos-completos)
- [Optimizaciones Implementadas](#optimizaciones-implementadas)

## Arquitectura General

### Visitor Pattern
El compilador utiliza el patrón Visitor para separar la lógica de generación de código del AST:

```cpp
class GenCodeVisitor {
private:
    Environment* env;
    ofstream& out;
    int cantidad = 0;
    
public:
    void visit(StructDeclaration* structDecl);
    void visit(StructDeclarationList* structList);
    int visit(StructInitializerExp* exp, int base_offset);
    
    void visit(UnaryExp* exp);  // Maneja & y *
    void get_member_address(MemberAccessExp* exp);
    
    // Método auxiliar para calcular direcciones
    void get_member_address(MemberAccessExp* exp);
};
```

### Environment Management
```cpp
class Environment {
    // Información de structs
    map<string, StructInfo> structs;
    
    // Variables y sus ubicaciones
    map<string, VarInfo> variables;
    
public:
    void add_struct(const string& name, const StructInfo& info);
    int get_struct_size(const string& struct_name);
    int get_struct_member_offset(const string& struct_name, const string& member);
    bool has_struct(const string& struct_name);
};
```

## Manejo de Structs

### 1. Declaración de Structs

#### Clases AST
```cpp
class StructDeclaration {
public:
    string struct_name;
    VarDecList* members;
    
    StructDeclaration(string name, VarDecList* members);
    int accept(Visitor* visitor);
};

class StructDeclarationList {
public:
    vector<StructDeclaration*> structs;
    
    StructDeclarationList();
    void add(StructDeclaration* struct_decl);
    int accept(Visitor* visitor);
};
```

#### Parser Implementation
```cpp
StructDeclarationList* Parser::parseStructDeclarations() {
    skipComments();
    StructDeclarationList* structs = new StructDeclarationList();
    
    while(match(Token::STRUCT)) {
        skipComments();
        structs->add(parseStructDeclaration());
        skipComments();
    }
    
    return structs;
}

StructDeclaration* Parser::parseStructDeclaration() {
    if (!check(Token::IDENTIFIER)) {
        throw runtime_error("Se esperaba el nombre del struct.");
    }
    string name = current->text;
    advance();
    
    if (!match(Token::LEFT_BRACE)) {
        throw runtime_error("Se esperaba '{' para iniciar el cuerpo del struct.");
    }
    
    VarDecList* members = parseVarDecList();
    
    if (!match(Token::RIGHT_BRACE)) {
        throw runtime_error("Se esperaba '}' para finalizar el cuerpo del struct.");
    }
    
    if (!match(Token::SEMICOLON)) {
        throw runtime_error("Se esperaba ';' despues de la declaracion de struct.");
    }
    
    return new StructDeclaration(name, members);
}
```

#### Generación de Código para Structs
```cpp
void GenCodeVisitor::visit(StructDeclaration* structDecl) {
    StructInfo info;
    int offset = 0;
    
    if (structDecl->members) {
        for (auto member : structDecl->members->vardecs) {
            for (size_t i = 0; i < member->vars.size(); ++i) {
                // Determinar tamaño usando 64 bits
                int member_size = 8; // Por defecto 8 bytes para 64 bits
                
                if (member->types[i]->is_pointer) {
                    member_size = 8; // Punteros siempre 8 bytes en 64 bits
                } else if (member->types[i]->type_name == "char" || 
                          member->types[i]->type_name == "bool") {
                    member_size = 1; // char/bool siguen siendo 1 byte
                } else if (member->types[i]->type_name == "int") {
                    member_size = 8; // int es 8 bytes en 64 bits
                } else if (member->types[i]->type_name.find("struct") == 0) {
                    // Structs anidados
                    string struct_name = member->types[i]->type_name.substr(7);
                    if (env->has_struct(struct_name)) {
                        member_size = env->get_struct_size(struct_name);
                    }
                }
                
                // Alineación a 8 bytes para 64 bits
                int alignment = 8;
                if (member_size == 1) {
                    alignment = 1; // char/bool no necesitan alineación especial
                }
                offset = (offset + alignment - 1) & ~(alignment - 1);
                
                // Registrar campo
                info.fields[member->vars[i]] = {
                    member->types[i]->type_name, 
                    member->types[i]->is_pointer, 
                    member->types[i]->is_array
                };
                info.offsets[member->vars[i]] = offset;
                
                out << "# Miembro: " << member->vars[i] 
                    << " tipo: " << member->types[i]->type_name
                    << " offset: " << offset 
                    << " tamaño: " << member_size << endl;
                
                offset += member_size;
            }
        }
    }
    
    // Alinear el tamaño total a 8 bytes
    info.size = (offset + 7) & ~7;
    env->add_struct(structDecl->struct_name, info);
    
    out << "# Struct " << structDecl->struct_name 
        << " tamaño total: " << info.size << endl;
}
```

### 2. Inicialización de Structs

#### Clase AST para Inicialización
```cpp
class StructInitializerExp : public Exp {
public:
    string struct_name;
    vector<pair<string, Exp*>> members; // member name and value
    
    StructInitializerExp(const string& name);
    void add_member(const string& member_name, Exp* value);
    
    int accept(GenCodeVisitor* visitor, int base_offset) {
        return visitor->visit(this, base_offset);
    }
    int accept(Visitor* visitor);
};
```

#### Generación de Código para Inicialización
```cpp
int GenCodeVisitor::visit(StructInitializerExp* exp, int base_offset) {
    out << "# Inicializando struct en offset " << base_offset << endl;
    
    if (!env->has_struct(exp->struct_name)) {
        cerr << "Error: Estructura '" << exp->struct_name << "' no declarada" << endl;
        exit(1);
    }
    
    StructInfo info = env->get_struct(exp->struct_name);
    
    // Ordenar campos por offset para inicialización correcta
    std::vector<std::string> field_names;
    for (const auto& kv : info.offsets) {
        field_names.push_back(kv.first);
    }
    std::sort(field_names.begin(), field_names.end(),
        [&](const std::string& a, const std::string& b) {
            return info.offsets.at(a) < info.offsets.at(b);
        });
    
    // Inicializar campos en orden
    for (size_t i = 0; i < exp->members.size() && i < field_names.size(); ++i) {
        int field_offset = info.offsets.at(field_names[i]);
        
        // Evaluar expresión de inicialización
        exp->members[i].second->accept(this); // valor en %rax
        
        // Usar movq consistentemente para 64 bits
        out << "    movq %rax, " << (base_offset + field_offset) 
            << "(%rbp) # " << field_names[i] << endl;
    }
    
    // Inicializar campos restantes a 0
    for (size_t i = exp->members.size(); i < field_names.size(); ++i) {
        int field_offset = info.offsets.at(field_names[i]);
        out << "    movq $0, " << (base_offset + field_offset) 
            << "(%rbp) # " << field_names[i] << " = 0" << endl;
    }
    
    return 0;
}
```

## Sistema de Punteros

### Operadores Unarios para Punteros
Los punteros se implementan como operadores unarios:
- `&` (ADDRESS_OF_OP): Obtiene la dirección de una variable
- `*` (DEREFERENCE_OP): Desreferencia un puntero

```cpp
int GenCodeVisitor::visit(UnaryExp* exp) {
    exp->uexp->accept(this);
    
    switch (exp->op) {
        case ADDRESS_OF_OP: {
            if (auto id = dynamic_cast<IdentifierExp*>(exp->uexp)) {
                if (!env->check(id->name)) {
                    cerr << "Error: Variable no declarada: " << id->name << endl;
                    exit(1);
                }
                VarInfo info = env->lookup(id->name);
                if (!info.is_global) {
                    out << "    leaq " << info.offset << "(%rbp), %rax  # &" 
                        << id->name << endl;
                } else {
                    out << "    leaq " << id->name << "(%rip), %rax  # &" 
                        << id->name << endl;
                }
            } else if (auto member = dynamic_cast<MemberAccessExp*>(exp->uexp)) {
                // Soporte para &(obj->field) y &(obj.field)
                get_member_address(member);
                out << "    # &member (dirección ya calculada)" << endl;
            }
            break;
        }
        case DEREFERENCE_OP:
            out << "    movq (%rax), %rax  # *ptr" << endl;
            break;
    }
    return 0;
}
```

### Asignaciones con Punteros
```cpp
// En AssignExp para manejar *ptr = valor
if (auto unary = dynamic_cast<UnaryExp*>(exp->left)) {
    if (unary->op == DEREFERENCE_OP) {
        unary->uexp->accept(this); // obtiene dirección del puntero en %rax
        out << " movq %rax, %rbx # guardar dirección" << endl;
        out << " popq %rax # recuperar valor a asignar" << endl;
        out << " movq %rax, (%rbx) # *ptr = valor" << endl;
    }
}
```

## Acceso a Miembros

### MemberAccessExp para obj.field y obj->field
```cpp
class MemberAccessExp : public Exp {
public:
    Exp* object;
    string member_name;
    bool is_pointer;  // true para ->, false para .
    
    MemberAccessExp(Exp* obj, string member, bool ptr_access = false);
    int accept(Visitor *visitor);
};
```

### Implementación del Acceso a Miembros
```cpp
int GenCodeVisitor::visit(MemberAccessExp* exp) {
    // Detectar tipo de acceso
    int base_offset = 0;
    std::string struct_type;
    bool is_local_struct = false;
    
    if (auto id = dynamic_cast<IdentifierExp*>(exp->object)) {
        if (!env->check(id->name)) {
            cerr << "Error: Variable no declarada: " << id->name << endl;
            exit(1);
        }
        
        struct_type = env->lookup_type(id->name);
        if (struct_type.rfind("struct ", 0) == 0) {
            struct_type = struct_type.substr(7);
        }
        VarInfo info = env->lookup(id->name);
        base_offset = info.offset;
        is_local_struct = !info.is_global;
    }
    
    int member_offset = 0;
    if (env->has_struct(struct_type)) {
        member_offset = env->get_struct_member_offset(struct_type, exp->member_name);
    }
    
    if (exp->is_pointer) {
        // p->campo: evaluar el objeto para obtener puntero
        exp->object->accept(this);
        out << " addq $" << member_offset << ", %rax # offset del miembro " 
            << exp->member_name << endl;
        out << " movq (%rax), %rax # cargar valor del miembro" << endl;
    } else if (is_local_struct) {
        // p.campo: acceso directo en el stack
        out << " movq " << (base_offset + member_offset) 
            << "(%rbp), %rax # " << exp->member_name 
            << " de struct local" << endl;
    } else {
        // Caso general: struct no local
        exp->object->accept(this);
        out << " addq $" << member_offset << ", %rax # offset del miembro " 
            << exp->member_name << endl;
        out << " movq (%rax), %rax # cargar valor del miembro" << endl;
    }
    
    return 0;
}
```

### Función Auxiliar para Direcciones de Miembros
```cpp
void GenCodeVisitor::get_member_address(MemberAccessExp* exp) {
    // Similar a visit(MemberAccessExp) pero retorna dirección en lugar de valor
    int base_offset = 0;
    std::string struct_type;
    bool is_local_struct = false;
    
    if (auto id = dynamic_cast<IdentifierExp*>(exp->object)) {
        struct_type = env->lookup_type(id->name);
        if (struct_type.rfind("struct ", 0) == 0) {
            struct_type = struct_type.substr(7);
        }
        VarInfo info = env->lookup(id->name);
        base_offset = info.offset;
        is_local_struct = !info.is_global;
    }
    
    int member_offset = 0;
    if (env->has_struct(struct_type)) {
        member_offset = env->get_struct_member_offset(struct_type, exp->member_name);
    }
    
    if (exp->is_pointer) {
        // p->campo: obtener dirección del campo
        exp->object->accept(this);
        out << " addq $" << member_offset << ", %rax # dirección de " 
            << exp->member_name << endl;
    } else if (is_local_struct) {
        // p.campo: calcular dirección en el stack
        out << " leaq " << (base_offset + member_offset) 
            << "(%rbp), %rax # dirección de " << exp->member_name 
            << " en struct local" << endl;
    } else {
        // Caso general
        exp->object->accept(this);
        out << " addq $" << member_offset << ", %rax # dirección de " 
            << exp->member_name << endl;
    }
}
```

## Generación de Código x86-64

### Convenciones de 64 bits
- **Registros**: `%rax`, `%rbx`, `%rcx`, etc. (64 bits)
- **Instrucciones**: `movq`, `addq`, `subq`, etc.
- **Tamaños**: 
  - `int`: 8 bytes
  - `char`/`bool`: 1 byte (alineado a 8)
  - Punteros: 8 bytes
  - Structs: Alineados a 8 bytes

### Alineación de Memoria
```cpp
// Alineación de campos en structs
int alignment = 8;
if (member_size == 1) {
    alignment = 1; // char/bool no necesitan alineación especial
}
offset = (offset + alignment - 1) & ~(alignment - 1);

// Alineación del tamaño total del struct
info.size = (offset + 7) & ~7;
```

### Cálculo de Stack Space
```cpp
int GenCodeVisitor::calcular_stack_body(Body* body) {
    int stack = 0;
    for (auto elem : body->elements) {
        if (auto vardec = dynamic_cast<VarDec*>(elem)) {
            for (size_t i = 0; i < vardec->vars.size(); ++i) {
                int var_size = 8; // Por defecto 64 bits
                std::string tname = vardec->types[i]->type_name;
                
                if (vardec->types[i]->is_pointer) {
                    var_size = 8; // Punteros = 8 bytes
                } else if (tname == "char" || tname == "bool") {
                    var_size = 1;
                } else if (tname == "int") {
                    var_size = 8;
                } else if (tname.find("struct") == 0) {
                    std::string struct_name = tname.substr(7);
                    var_size = env->get_struct_size(struct_name);
                }
                
                if (var_size < 8) var_size = 8; // Alinear a 8 bytes
                stack += var_size;
            }
        }
        // Recursión para estructuras de control
        else if (auto forstm = dynamic_cast<ForStatement*>(elem)) {
            if (forstm->b) stack += calcular_stack_body(forstm->b);
        }
        else if (auto ifstm = dynamic_cast<IfStatement*>(elem)) {
            if (ifstm->statements) stack += calcular_stack_body(ifstm->statements);
        }
        // ... más casos
    }
    return stack;
}
```

## Ejemplos Completos

### Ejemplo 1: Struct Básico
```c
struct Point {
    int x, y;
    char label;
};

int main() {
    struct Point p = {10, 20, 'A'};
    p.x = p.x + 5;
    printf("%d\n", p.x);
    return 0;
}
```

**Código Assembly Generado:**
```assembly
.data
print_fmt: .string "%ld\n"
# Miembro: x tipo: int offset: 0 tamaño: 8
# Miembro: y tipo: int offset: 8 tamaño: 8
# Miembro: label tipo: char offset: 16 tamaño: 1
# Struct Point tamaño total: 24
# Campo label: offset 16
# Campo y: offset 8
# Campo x: offset 0
.text
.globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 subq $32, %rsp
# Declarando variable: p en offset -24
# Inicializando struct en offset -24
 movq $10, %rax
    movq %rax, -24(%rbp) # x
 movq $20, %rax
    movq %rax, -16(%rbp) # y
 movq $65, %rax
    movq %rax, -8(%rbp) # label
 movq -24(%rbp), %rax # x de struct local
    movq %rax, %rdx
 movq $5, %rax
    addq %rdx, %rax
 pushq %rax
 popq %rax # recuperar valor a asignar
 pushq %rax # guardar valor temporalmente
 leaq -24(%rbp), %rax # dirección de x en struct local
 movq %rax, %rbx # guardar dirección
 popq %rax # recuperar valor
 movq %rax, (%rbx) # escribir valor en member
.section .rodata
printf_fmt_0: .string "%d\n"
.text
    pushq %rbp # salvar frame pointer para alineación
    leaq printf_fmt_0(%rip), %rdi
 movq -24(%rbp), %rax # x de struct local
    movq %rax, %rsi
    xorq %rax, %rax # 0 registros vectoriales usados
    call printf@PLT
    popq %rbp # restaurar frame pointer
 movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits


```

### Ejemplo 2: Punteros a Struct
```c
struct Node {
    int data;
    struct Node* next;
};

int main() {
    struct Node node = {42, 0};
    struct Node* ptr = &node;
    ptr->data = 100;
    printf("El valor del nodo es: %d\n", ptr->data);
    return 0;
}
```

**Código Assembly Generado:**
```assembly
.data
print_fmt: .string "%ld\n"
# Miembro: data tipo: int offset: 0 tamaño: 8
# Miembro: next tipo: struct Node offset: 8 tamaño: 8
# Struct Node tamaño total: 16
# Campo next: offset 8
# Campo data: offset 0
.text
.globl main
main:
 pushq %rbp
 movq %rsp, %rbp
 subq $32, %rsp
# Declarando variable: node en offset -16
# Declarando variable: ptr en offset -24
# Inicializando struct en offset -16
 movq $42, %rax
    movq %rax, -16(%rbp) # data
 movq $0, %rax
    movq %rax, -8(%rbp) # next
# Cargando valor de node 0 -1
 movq -16(%rbp), %rax # node
    leaq -16(%rbp), %rax  # &node
    movq %rax, -24(%rbp) # ptr
 movq $100, %rax
 pushq %rax
 popq %rax # recuperar valor a asignar
 pushq %rax # guardar valor temporalmente
# Cargando valor de ptr 0 -1
 movq -24(%rbp), %rax # ptr
 addq $0, %rax # dirección de data
 movq %rax, %rbx # guardar dirección
 popq %rax # recuperar valor
 movq %rax, (%rbx) # escribir valor en member
.section .rodata
printf_fmt_0: .string "El valor del nodo es: %d\n"
.text
    pushq %rbp # salvar frame pointer para alineación
    leaq printf_fmt_0(%rip), %rdi
# Cargando valor de ptr 0 -1
 movq -24(%rbp), %rax # ptr
 addq $0, %rax # offset del miembro data
 movq (%rax), %rax # cargar valor del miembro
    movq %rax, %rsi
    xorq %rax, %rax # 0 registros vectoriales usados
    call printf@PLT
    popq %rbp # restaurar frame pointer
 movq $0, %rax
    leave
    ret
.section .note.GNU-stack,"",@progbits

```

## Conclusión

Esta implementación proporciona soporte completo para structs y punteros en un compilador que genera código x86-64 eficiente. Las características clave incluyen:

- **Punteros con dereferenciación**  
- **Acceso a miembros optimizado (. y ->)**
- **Soporte para funciones con parámetros por referencia**
- **Generación de código x86-64**

El diseño modular permite fácil extensión para características adicionales como arrays dinámicos, herencia, o optimizaciones más avanzadas.

# Proyecto Compilador C- Instrucciones de uso

## Requisitos previos

- Tener instalado **g++** (para compilar el compilador)
- Tener instalado **gcc** (para ejecutar los archivos `.s` generados)
- Tener **Python 3** instalado

---

## Estructura del proyecto

- `make.py`: Script que compila el compilador y ejecuta todos los tests (`.txt`) en la carpeta `tests/`, generando archivos `.s` en el mismo directorio de cada test.
- `ejecutador.py`: Script que toma un archivo `.s` generado y lo compila/ejecuta usando `gcc`, mostrando la salida del programa ensamblado.
- Carpeta `tests/`: Contiene los archivos de prueba `.txt` que serán procesados por el compilador.

---
# Manual de Usuario

## 📋 Prerrequisitos del Sistema

### 🖥️ **Requerimientos Mínimos**
- **RAM**: 2GB mínimo, 4GB recomendado
- **Espacio en disco**: 500MB libres
- **Procesador**: Compatible con x86-64
- **Sistema operativo**: Linux, macOS, o Windows tener en cuenta que si o si se necesita un entorno linux para ejecutar los archivos .s
### 🛠️ **Dependencias por Plataforma**

#### 🐧 **Linux (Ubuntu/Debian)**
```bash
# Actualizar sistema
sudo apt update && sudo apt upgrade

# Instalar dependencias
sudo apt install -y build-essential gcc g++ python3 python3-pip python3-venv

# Verificar instalaciones
gcc --version
g++ --version
python3 --version
```

#### 🍎 **macOS**
```bash
# Instalar Xcode Command Line Tools
xcode-select --install

# Instalar Homebrew (si no está instalado)
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Instalar dependencias
brew install python3
brew install gcc

# Verificar instalaciones
gcc --version
python3 --version
```

#### 🪟 **Windows**
```powershell
# Opción 1: Usar WSL2 (Recomendado)
# 1. Instalar WSL2 desde Microsoft Store
# 2. Instalar Ubuntu desde Microsoft Store
# 3. Seguir instrucciones de Linux dentro de WSL

# Opción 2: Instalación nativa
# 1. Instalar Python desde https://python.org
# 2. Instalar MinGW-w64 o Visual Studio Build Tools
# 3. Agregar al PATH las rutas de instalación

# Verificar desde Command Prompt o PowerShell
python --version
gcc --version
```

## 📋 Cómo levantar y usar el proyecto

### 1. Compilar el compilador y generar archivos `.s` desde tests

#### 🐧 **Linux / 🍎 macOS**
poner el archivo en la carpetaa tests o si no modfique el make.py de acuerdo a su conveniencia.
```bash
# Compilar el compilador 
python3 make.py

# Ejecutar tests del codigo assembly generado
python3 ejecutador.py
```

#### 🪟 **Windows**
```cmd
# En Command Prompt o PowerShell
python make.py

# Ejecutar tests
python ejecutador.py ruta\al\archivo.txt
```

### 2. Ejecutar el frontend con Streamlit

#### 📥 **Instalación de dependencias**

##### 🐧 **Linux / 🍎 macOS**
```bash
# Crear entorno virtual
python3 -m venv venv

# Activar entorno virtual
source venv/bin/activate

# Instalar Streamlit
pip install streamlit
```

##### 🪟 **Windows**
```cmd
# Crear entorno virtual
python -m venv venv

# Activar entorno virtual
venv\Scripts\activate

# Instalar Streamlit
pip install streamlit
```

#### 🚀 **Ejecución del frontend**

##### 🐧 **Linux / 🍎 macOS**
```bash
# Ejecutar la aplicación
streamlit run main.py
```

##### 🪟 **Windows**
```cmd
# Ejecutar la aplicación
streamlit run main.py
```

#### 🌐 **Acceso a la aplicación**

Una vez ejecutado, la aplicación estará disponible en:
- **URL**: http://localhost:8501
- **Interfaz**: Navegador web con editor de código integrado

### 3. Uso del compilador

#### ✅ **Mediante frontend (recomendado)**
1. Abrir http://localhost:8501 en el navegador
2. Escribir código C en el editor
3. Hacer clic en "🚀 Compilar y Ejecutar"
4. Ver resultados en las pestañas de Assembly y Ejecución

#### ⚙️ **Mediante línea de comandos**

##### 🐧 **Linux / 🍎 macOS**
```bash
# Compilar archivo específico
./main archivo_entrada.txt

# El archivo .s se genera automáticamente
# Ejemplo: archivo_entrada.txt → archivo_entrada.s
```

##### 🪟 **Windows**
```cmd
# Compilar archivo específico
main.exe archivo_entrada.txt

# El archivo .s se genera automáticamente
# Ejemplo: archivo_entrada.txt → archivo_entrada.s
```

## 🔧 **Solución de Problemas Comunes**

### 🐧 **Linux**
```bash
# Si gcc no se encuentra
sudo apt install build-essential

# Si python3 no se encuentra
sudo apt install python3 python3-pip
```

### 🍎 **macOS**
```bash
# Si gcc no se encuentra
xcode-select --install

# Si hay problemas de permisos
sudo chown -R $(whoami) /usr/local
```

### 🪟 **Windows**
```cmd
# Si python no se encuentra
# Reinstalar Python y marcar "Add to PATH"

# Si gcc no se encuentra
# Instalar MinGW-w64 y agregar al PATH
```