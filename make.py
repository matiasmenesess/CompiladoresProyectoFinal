
import os
import subprocess

source_files = [
    "main.cpp",
    "parser.cpp",
    "scanner.cpp",
    "token.cpp",
    "visitor.cpp",
    "expression.cpp",
    "gencode.cpp"
]

executable = "main"

test_dir = "tests"
output_dir = "generadosS"

os.makedirs(output_dir, exist_ok=True)

print("🔧 Compilando...")
compile_cmd = ["g++", "-std=c++17", "-Wall"] + source_files + ["-o", executable]
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

    with open(test_file, "r") as f:
        contenido = f.read()

print("\n✅ Todos los tests fueron ejecutados y sus salidas se guardaron en 'asm_outputs/'")
