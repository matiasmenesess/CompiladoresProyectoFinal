#!/usr/bin/env python3
"""
Cliente de prueba para la API del compilador
"""

import requests
import json

# Configuración
API_BASE_URL = "http://localhost:8000"

def test_health():
    """Probar endpoint de salud"""
    print("🔍 Probando health check...")
    try:
        response = requests.get(f"{API_BASE_URL}/health")
        print(f"Status: {response.status_code}")
        print(f"Response: {json.dumps(response.json(), indent=2)}")
        return response.status_code == 200
    except Exception as e:
        print(f"❌ Error: {e}")
        return False

def test_compile(source_code, compile_only=False):
    """Probar compilación"""
    print(f"\n🔨 Probando compilación{'(solo compilar)' if compile_only else '(compilar y ejecutar)'}...")
    print(f"Código:\n{source_code}")
    print("-" * 50)
    
    try:
        payload = {
            "source_code": source_code,
            "compile_only": compile_only
        }
        
        response = requests.post(f"{API_BASE_URL}/compile", json=payload)
        result = response.json()
        
        print(f"Status: {response.status_code}")
        
        if result.get("success"):
            print("✅ Compilación exitosa!")
            
            if result.get("assembly_code"):
                print(f"\n📝 Assembly generado:")
                print(result["assembly_code"][:500] + "..." if len(result["assembly_code"]) > 500 else result["assembly_code"])
            
            if result.get("execution_result") and not compile_only:
                exec_result = result["execution_result"]
                print(f"\n🚀 Ejecución:")
                print(f"  Return code: {exec_result.get('return_code')}")
                if exec_result.get("stdout"):
                    print(f"  Stdout: {exec_result['stdout']}")
                if exec_result.get("stderr"):
                    print(f"  Stderr: {exec_result['stderr']}")
                print(f"  Ejecutado: {exec_result.get('executed')}")
            
            if result.get("compilation_time"):
                print(f"\n⏱️  Tiempo de compilación: {result['compilation_time']:.3f}s")
            if result.get("execution_time"):
                print(f"⏱️  Tiempo de ejecución: {result['execution_time']:.3f}s")
                
        else:
            print("❌ Error en compilación:")
            print(f"  Error: {result.get('error_message')}")
            if result.get("compiler_output"):
                print(f"  Salida del compilador: {result['compiler_output']}")
        
        return result.get("success", False)
        
    except Exception as e:
        print(f"❌ Error de conexión: {e}")
        return False

def test_examples():
    """Probar endpoint de ejemplos"""
    print("\n📚 Probando ejemplos...")
    try:
        response = requests.get(f"{API_BASE_URL}/examples")
        examples = response.json()
        
        print(f"✅ Encontrados {len(examples)} ejemplos:")
        for key, example in examples.items():
            print(f"  - {example['name']}: {example['description']}")
        
        return examples
    except Exception as e:
        print(f"❌ Error: {e}")
        return None

def main():
    print("🧪 Cliente de prueba para API del Compilador")
    print("=" * 60)
    
    # 1. Test health
    if not test_health():
        print("❌ API no está funcionando correctamente")
        return
    
    # 2. Test ejemplos
    examples = test_examples()
    
    # 3. Test compilación simple
    simple_code = """int main() {
    int x = 42;
    int y = x + 8;
    return y;
}"""
    
    test_compile(simple_code)
    
    # 4. Test solo compilación
    test_compile(simple_code, compile_only=True)
    
    # 5. Test con punteros
    pointer_code = """int main() {
    int x = 100;
    int* ptr = &x;
    *ptr = 200;
    return 0;
}"""
    
    test_compile(pointer_code)
    
    # 6. Test con struct
    struct_code = """struct Point {
    int x, y;
};

int main() {
    struct Point p = {10, 20};
    p.x = p.x + 5;
    return o;
}"""
    
    test_compile(struct_code)
    
    # 7. Test con error
    error_code = """int main() {
    undeclared_variable = 42;
    return 0;
}"""
    
    print("\n🧨 Probando código con error...")
    test_compile(error_code)
    
    print("\n✅ Pruebas completadas!")

if __name__ == "__main__":
    main()