from fastapi import FastAPI, HTTPException, UploadFile, File
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import JSONResponse, FileResponse
from pydantic import BaseModel
import subprocess
import tempfile
import os
import asyncio
import time
from pathlib import Path
from typing import Optional
from fastapi.staticfiles import StaticFiles

app = FastAPI(
    title="Compilador C API",
    description="API para compilar código C a assembly x86-64 y ejecutarlo",
    version="1.0.0"
)
app.mount("/static", StaticFiles(directory=".", html=True), name="static")


# CORS para permitir frontend
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],  # En producción, especifica dominios
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

# Configuración
COMPILER_EXECUTABLE = "../main"  # Ruta a tu compilador compilado
TEMP_DIR = "/tmp/compiler_api"
MAX_EXECUTION_TIME = 10  # segundos

# Crear directorio temporal
os.makedirs(TEMP_DIR, exist_ok=True)

class CompileRequest(BaseModel):
    source_code: str
    compile_only: bool = False  # Si true, solo compila sin ejecutar

class CompileResponse(BaseModel):
    success: bool
    assembly_code: Optional[str] = None
    execution_result: Optional[dict] = None
    compiler_output: Optional[str] = None
    error_message: Optional[str] = None
    compilation_time: Optional[float] = None
    execution_time: Optional[float] = None

@app.get("/")
async def root():
    return {
        "message": "API del Compilador C",
        "version": "1.0.0",
        "endpoints": {
            "compile": "POST /compile - Compilar y ejecutar código",
            "health": "GET /health - Estado de la API",
            "examples": "GET /examples - Obtener ejemplos"
        }
    }

@app.get("/health")
async def health_check():
    """Verificar que el compilador y GCC estén disponibles"""
    checks = {}
    
    # Verificar compilador
    try:
        result = subprocess.run([COMPILER_EXECUTABLE, "--version"], 
                              capture_output=True, text=True, timeout=5)
        checks["compiler"] = {
            "available": result.returncode == 0,
            "version": result.stdout.strip() if result.returncode == 0 else "Error"
        }
    except:
        checks["compiler"] = {"available": False, "version": "No encontrado"}
    
    # Verificar GCC
    try:
        result = subprocess.run(["gcc", "--version"], 
                              capture_output=True, text=True, timeout=5)
        checks["gcc"] = {
            "available": result.returncode == 0,
            "version": result.stdout.split('\n')[0] if result.returncode == 0 else "Error"
        }
    except:
        checks["gcc"] = {"available": False, "version": "No encontrado"}
    
    return {
        "status": "healthy" if all(check["available"] for check in checks.values()) else "unhealthy",
        "checks": checks,
        "temp_dir": TEMP_DIR
    }

@app.post("/compile", response_model=CompileResponse)
async def compile_code(request: CompileRequest):
    """Compilar código C y opcionalmente ejecutarlo"""
    
    if not request.source_code.strip():
        raise HTTPException(status_code=400, detail="Código fuente vacío")
    
    # Generar nombres únicos para archivos
    timestamp = int(time.time() * 1000000)  # microsegundos para más unicidad
    base_name = f"code_{timestamp}"
    source_file = os.path.join(TEMP_DIR, f"{base_name}.c")
    assembly_file = os.path.join(TEMP_DIR, f"{base_name}.s")
    executable_file = os.path.join(TEMP_DIR, f"{base_name}")
    
    try:
        # 1. Escribir código fuente
        with open(source_file, 'w', encoding='utf-8') as f:
            f.write(request.source_code)
        
        # 2. Compilar con tu compilador
        compile_start = time.time()
        
        compile_process = await asyncio.create_subprocess_exec(
            COMPILER_EXECUTABLE, source_file,
            stdout=asyncio.subprocess.PIPE,
            stderr=asyncio.subprocess.PIPE
        )
        
        compile_stdout, compile_stderr = await asyncio.wait_for(
            compile_process.communicate(), timeout=30
        )
        
        compile_time = time.time() - compile_start
        
        if compile_process.returncode != 0:
            return CompileResponse(
                success=False,
                error_message=f"Error de compilación: {compile_stderr.decode()}",
                compiler_output=compile_stdout.decode(),
                compilation_time=compile_time
            )
        
        # 3. Leer assembly generado
        assembly_code = ""
        if os.path.exists(assembly_file):
            with open(assembly_file, 'r', encoding='utf-8') as f:
                assembly_code = f.read()
        
        # Si solo se pidió compilación, retornar aquí
        if request.compile_only:
            return CompileResponse(
                success=True,
                assembly_code=assembly_code,
                compiler_output=compile_stdout.decode(),
                compilation_time=compile_time
            )
        
        # 4. Ensamblar con GCC
        gcc_process = await asyncio.create_subprocess_exec(
            "gcc", "-o", executable_file, assembly_file,
            stdout=asyncio.subprocess.PIPE,
            stderr=asyncio.subprocess.PIPE
        )
        
        gcc_stdout, gcc_stderr = await asyncio.wait_for(
            gcc_process.communicate(), timeout=15
        )
        
        if gcc_process.returncode != 0:
            return CompileResponse(
                success=True,  # Compilación exitosa
                assembly_code=assembly_code,
                compiler_output=compile_stdout.decode(),
                compilation_time=compile_time,
                execution_result={
                    "gcc_error": gcc_stderr.decode(),
                    "executed": False
                }
            )
        
        # 5. Ejecutar programa
        exec_start = time.time()
        
        exec_process = await asyncio.create_subprocess_exec(
            executable_file,
            stdout=asyncio.subprocess.PIPE,
            stderr=asyncio.subprocess.PIPE
        )
        
        try:
            exec_stdout, exec_stderr = await asyncio.wait_for(
                exec_process.communicate(), timeout=MAX_EXECUTION_TIME
            )
            exec_time = time.time() - exec_start
            
            execution_result = {
                "stdout": exec_stdout.decode(),
                "stderr": exec_stderr.decode(),
                "return_code": exec_process.returncode,
                "executed": True,
                "execution_time": exec_time
            }
            
        except asyncio.TimeoutError:
            exec_process.kill()
            await exec_process.wait()
            execution_result = {
                "stdout": "",
                "stderr": f"Timeout: El programa tardó más de {MAX_EXECUTION_TIME} segundos",
                "return_code": -1,
                "executed": False,
                "execution_time": MAX_EXECUTION_TIME
            }
        
        return CompileResponse(
            success=True,
            assembly_code=assembly_code,
            execution_result=execution_result,
            compiler_output=compile_stdout.decode(),
            compilation_time=compile_time,
            execution_time=execution_result.get("execution_time")
        )
        
    except asyncio.TimeoutError:
        raise HTTPException(status_code=408, detail="Timeout en compilación")
    except Exception as e:
        raise HTTPException(status_code=500, detail=f"Error interno: {str(e)}")
    finally:
        # Limpiar archivos temporales
        for file_path in [source_file, assembly_file, executable_file]:
            try:
                if os.path.exists(file_path):
                    os.remove(file_path)
            except:
                pass

@app.get("/examples")
async def get_examples():
    """Obtener ejemplos de código"""
    examples = {
        "hello_world": {
            "name": "Hello World",
            "description": "Programa básico que retorna un valor",
            "code": """int main() {
        int result = 42;
        return 0;
    }"""
        },
        "arithmetic": {
            "name": "Operaciones Aritméticas",
            "description": "Operaciones básicas con enteros",
            "code": """int main() {
        int a = 10;
        int b = 5;
        int sum = a + b;
        int diff = a - b;
        int prod = a * b;
        return 0;
    }"""
        },
        "pointers": {
            "name": "Punteros Básicos",
            "description": "Uso básico de punteros",
            "code": """int main() {
        int x = 100;
        int* ptr = &x;
        *ptr = 200;
        return 0;
    }"""
        },
        "structs": {
            "name": "Estructuras",
            "description": "Definición y uso de structs",
            "code": """struct Point {
        int x, y;
    };
    
    int main() {
        struct Point p = {10, 20};
        p.x = p.x + 5;
        return 0;
    }"""
        },
        "functions": {
            "name": "Funciones",
            "description": "Definición y llamada de funciones",
            "code": """int add(int a, int b) {
        return a + b;
    }
    
    int multiply(int x, int y) {
        return x * y;
    }
    
    int main() {
        int result1 = add(15, 25);
        int result2 = multiply(4, 7);
        return 0;
    }"""
        },
        "loops": {
            "name": "Bucles",
            "description": "Bucles for y while",
            "code": """int main() {
        int sum = 0;
        for (int i = 1; i <= 10; i++) {
            sum = sum + i;
        }
        int count = 0;
        while (count < 5) {
            sum = sum + count;
            count++;
        }
        return 0;
    }"""
        },
        "complex_structs": {
            "name": "Structs Complejos",
            "description": "Punteros a structs y acceso a miembros",
            "code": """struct Node {
        int data;
        struct Node* next;
    };
    
    int main() {
        struct Node node1 = {10, 0};
        struct Node node2 = {20, 0};
        node1.next = &node2;
        struct Node* ptr = &node1;
        int total = ptr->data + ptr->next->data;
        return 0;
    }"""
        }
    }

@app.post("/compile-file")
async def compile_file(file: UploadFile = File(...)):
    """Compilar un archivo .c subido"""
    
    if not file.filename.endswith('.c'):
        raise HTTPException(status_code=400, detail="Solo se permiten archivos .c")
    
    # Leer contenido del archivo
    content = await file.read()
    source_code = content.decode('utf-8')
    
    # Usar la función de compilación existente
    request = CompileRequest(source_code=source_code)
    return await compile_code(request)

@app.get("/download-assembly/{filename}")
async def download_assembly(filename: str):
    """Descargar archivo assembly (endpoint para futuro uso)"""
    file_path = os.path.join(TEMP_DIR, filename)
    if os.path.exists(file_path):
        return FileResponse(file_path, media_type='text/plain', filename=filename)
    raise HTTPException(status_code=404, detail="Archivo no encontrado")

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(
        "main:app", 
        host="0.0.0.0", 
        port=8000, 
        reload=True,
        log_level="info"
    )