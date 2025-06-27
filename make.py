import os
import subprocess

# Carpeta donde están los archivos fuente
source_files = [
    "main.cpp",
    "parser.cpp",
    "scanner.cpp",
    "token.cpp",
    "visitor.cpp",
    "expression.cpp"
]

# Nombre del ejecutable
executable = "main"

# Directorios
test_dir = "tests"
output_dir = "asm_outputs"

# Crear carpeta de salida si no existe
os.makedirs(output_dir, exist_ok=True)

# 1. Compilación
print("🔧 Compilando...")
compile_cmd = ["g++", "-std=c++17", "-Wall"] + source_files + ["-o", executable]
result = subprocess.run(compile_cmd)

if result.returncode != 0:
    print("❌ Error de compilación.")
    exit(1)

print("✅ Compilación exitosa.\n")

# 2. Recolección de tests
test_files = []
for root, _, files in os.walk(test_dir):
    for file in files:
        if file.endswith(".txt"):
            test_files.append(os.path.join(root, file))

# 3. Ejecutar tests
for test_file in test_files:
    print(f"🧪 Ejecutando prueba: {test_file}")
    test_name = os.path.splitext(os.path.basename(test_file))[0]
    output_path = os.path.join(output_dir, f"{test_name}.s")

    with open(output_path, "w") as out_file:
        subprocess.run([f"./{executable}", test_file], stdout=out_file)

print("\n✅ Todos los tests fueron ejecutados y sus salidas se guardaron en 'asm_outputs/'")