import os
import subprocess

source_files = [
    "main.cpp",
    "parser.cpp",
    "scanner.cpp",
    "token.cpp",
    "visitor.cpp",
    "expression.cpp"
]

executable = "main.exe"

test_dir = "tests"
output_dir = "asm_outputs"

os.makedirs(output_dir, exist_ok=True)

print("🔧 Compilando...")
compile_cmd = ["g++", "-std=c++17", "-Wall"] + source_files + ["-o", executable]
print(f"Ejecutando: {' '.join(compile_cmd)}")

try:
    subprocess.run(["g++", "--version"], check=True, capture_output=True)
except (subprocess.CalledProcessError, FileNotFoundError):
    print("❌ g++ no encontrado. Intentando con otros compiladores...")
    for compiler in ["gcc", "clang++", "cl"]:
        try:
            subprocess.run([compiler, "--version"], check=True, capture_output=True)
            compile_cmd[0] = compiler
            print(f"✅ Usando {compiler}")
            break
        except (subprocess.CalledProcessError, FileNotFoundError):
            continue
    else:
        print("❌ No se encontró ningún compilador C++. Instala MinGW-w64, Visual Studio Build Tools, o Clang.")
        exit(1)

result = subprocess.run(compile_cmd)

if result.returncode != 0:
    print("❌ Error de compilación.")
    exit(1)

print("✅ Compilación exitosa.\n")

test_files = []
for root, _, files in os.walk(test_dir):
    for file in files:
        if file.endswith(".txt"):
            test_files.append(os.path.join(root, file))

for test_file in test_files:
    print(f"🧪 Ejecutando prueba: {test_file}")
    test_name = os.path.splitext(os.path.basename(test_file))[0]
    output_path = os.path.join(output_dir, f"{test_name}.s")

    with open(output_path, "w") as out_file:
        subprocess.run([executable, test_file], stdout=out_file)

print("\n✅ Todos los tests fueron ejecutados y sus salidas se guardaron en 'asm_outputs/'")
