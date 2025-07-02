import streamlit as st
import subprocess
import os
import tempfile
import time
from pathlib import Path
import base64
import pandas as pd

st.set_page_config(
    page_title="🚀 Compilador C ",
    page_icon="⚙️",
    layout="wide",
    initial_sidebar_state="expanded"
)

def load_css():
    st.markdown("""
    <style>
    @import url('https://fonts.googleapis.com/css2?family=Inter:wght@300;400;500;600;700&family=JetBrains+Mono:wght@400;500;600&display=swap');
    
    .stApp {
        background: linear-gradient(135deg, #667eea 0%, #764ba2 50%, #f093fb 100%);
        font-family: 'Inter', sans-serif;
    }
    
    .main-header {
        background: rgba(255, 255, 255, 0.1);
        backdrop-filter: blur(20px);
        border-radius: 20px;
        padding: 2rem;
        margin-bottom: 2rem;
        border: 1px solid rgba(255, 255, 255, 0.2);
        text-align: center;
        box-shadow: 0 20px 40px rgba(0, 0, 0, 0.1);
    }
    
    .main-header h1 {
        background: linear-gradient(135deg, #fff 0%, #f093fb 100%);
        -webkit-background-clip: text;
        -webkit-text-fill-color: transparent;
        font-size: 3rem;
        margin-bottom: 0.5rem;
        font-weight: 700;
    }
    
    .main-header p {
        color: rgba(255, 255, 255, 0.9);
        font-size: 1.2rem;
        margin: 0;
    }
    
    .glass-panel {
        background: rgba(255, 255, 255, 0.1);
        backdrop-filter: blur(20px);
        border-radius: 20px;
        padding: 1.5rem;
        margin: 1rem 0;
        border: 1px solid rgba(255, 255, 255, 0.2);
        box-shadow: 0 20px 40px rgba(0, 0, 0, 0.1);
    }
    
    .stTextArea textarea {
        background: rgba(15, 23, 42, 0.9) !important;
        border: 1px solid rgba(255, 255, 255, 0.2) !important;
        border-radius: 12px !important;
        color: #e2e8f0 !important;
        font-family: 'JetBrains Mono', monospace !important;
        font-size: 14px !important;
        line-height: 1.6 !important;
    }
    
    .stButton > button {
        background: linear-gradient(135deg, #667eea 0%, #764ba2 100%) !important;
        color: white !important;
        border: none !important;
        border-radius: 12px !important;
        padding: 0.75rem 2rem !important;
        font-weight: 600 !important;
        transition: all 0.3s ease !important;
        box-shadow: 0 4px 15px rgba(102, 126, 234, 0.4) !important;
    }
    
    .stButton > button:hover {
        transform: translateY(-2px) !important;
        box-shadow: 0 8px 25px rgba(102, 126, 234, 0.6) !important;
    }
    
    .css-1d391kg {
        background: rgba(255, 255, 255, 0.1) !important;
        backdrop-filter: blur(20px) !important;
    }
    
    .metric-card {
        background: rgba(255, 255, 255, 0.1);
        backdrop-filter: blur(20px);
        border-radius: 16px;
        padding: 1.5rem;
        margin: 0.5rem 0;
        border: 1px solid rgba(255, 255, 255, 0.2);
        text-align: center;
    }
    
    .metric-card h3 {
        color: #fff;
        margin: 0;
        font-size: 1.8rem;
        font-weight: 600;
    }
    
    .metric-card p {
        color: rgba(255, 255, 255, 0.8);
        margin: 0.5rem 0 0 0;
        font-size: 0.9rem;
    }
    
    .stCode {
        border-radius: 12px !important;
        border: 1px solid rgba(255, 255, 255, 0.2) !important;
    }
    
    .stAlert {
        border-radius: 12px !important;
        backdrop-filter: blur(20px) !important;
    }
    
    .stProgress .st-bo {
        background: linear-gradient(135deg, #667eea 0%, #764ba2 100%) !important;
    }
    
    .status-success {
        background: linear-gradient(135deg, #10b981 0%, #059669 100%);
        color: white;
        padding: 0.5rem 1rem;
        border-radius: 20px;
        font-weight: 600;
        display: inline-block;
        margin: 0.5rem 0;
    }
    
    .status-error {
        background: linear-gradient(135deg, #ef4444 0%, #dc2626 100%);
        color: white;
        padding: 0.5rem 1rem;
        border-radius: 20px;
        font-weight: 600;
        display: inline-block;
        margin: 0.5rem 0;
    }
    
    .status-warning {
        background: linear-gradient(135deg, #f59e0b 0%, #d97706 100%);
        color: white;
        padding: 0.5rem 1rem;
        border-radius: 20px;
        font-weight: 600;
        display: inline-block;
        margin: 0.5rem 0;
    }
    </style>
    """, unsafe_allow_html=True)

def create_header():
    st.markdown("""
    <div class="main-header">
        <h1>🚀 Compilador C </h1>
        <p>Compilador moderno con soporte para structs, punteros y generación de código x86-64
            Hecho por Zamir Lizardo y Matias Meneses
            para el curso de Compiladores de la UTEC.
            Con mucho cariño para el profesor Julio Yarasca y nuestro querido TA Luis. 
        </p>
    </div>
    """, unsafe_allow_html=True)

def load_examples():
    examples = {
        "🌍 Hello World": """
#include <stdio.h>
int main() {
    printf("¡Hola, mundo estoy programando en c!\n");  
    return 0;
}""",
        "🔢 Operaciones Aritméticas": """#include <stdio.h>
int main() {
    int a = 10;
    int b = 5;
    int sum = a + b;
    int diff = a - b;
    int prod = a * b;
    printf("Suma: %d, Resta: %d, Producto: %d\n", sum, diff, prod);
    return 0;
}""",
        "👉 Punteros Básicos": """
#include <stdio.h>
int main() {
    int x = 100;
    int* ptr = &x;
    *ptr = 200;
    printf("Valor de x: %d\n", x);
    return 0;
}""",
        "🏗️ Estructuras": """
#include <stdio.h>
struct Point {
    int x, y;
};

int main() {
    struct Point p = {10, 20};
    p.x = p.x + 5;
    printf("Punto: (%d, %d)\n", p.x, p.y);
    return 0;
}""",
        "⚙️ Funciones": """#include <stdio.h>
int add(int a, int b) {
    return a + b;
}

int multiply(int x, int y) {
    return x * y;
}

int main() {
    int result1 = add(15, 25);
    int result2 = multiply(4, 7);
    printf("Suma: %d, Producto: %d\n", result1, result2);
    return 0;
}""",
        "🔄 Bucles": """#include<stdio.h>
int main() {
    int sum = 0;
    
    for (int i = 1; i <= 10; i++) {
        sum = sum + i;
    }
    
    int count = 0;
    while (count < 5) {
        sum = sum + count;
        count++;
    }
    
    printf("Suma total: %d\n", sum);
    return 0;
}""",
        "🔗 Structs y Punteros": """
#include <stdio.h>
struct Punto {
    int x;
    int y;
};

void duplica_y(struct Punto* pt) {
    pt->y = pt->x * 2;
}

int main() {
    struct Punto p;
    p.x = 5;
    duplica_y(&p);
    printf("p.y deberia ser 10: %d\n", p.y);
    return 0;}
    """
    }
    return examples

def compile_and_run(codigo, compilador_path="./main"):
    """Compila y ejecuta el código usando el compilador personalizado"""
    
    compilation_stats = {
        "success": False,
        "assembly_code": "",
        "execution_output": "",
        "compilation_time": 0,
        "execution_time": 0,
        "return_code": None,
        "errors": ""
    }
    
    with tempfile.TemporaryDirectory() as tmpdir:
        try:
            txt_path = os.path.join(tmpdir, "programa.txt")
            with open(txt_path, "w", encoding='utf-8') as f:
                f.write(codigo)
            
            start_time = time.time()
            
            result = subprocess.run(
                [compilador_path, txt_path], 
                capture_output=True, 
                text=True,
                timeout=30
            )
            
            compilation_stats["compilation_time"] = time.time() - start_time
            
            if result.returncode != 0:
                compilation_stats["errors"] = f"Error de compilación:\n{result.stdout}\n{result.stderr}"
                return compilation_stats
            
            asm_path = txt_path.replace(".txt", ".s")
            if os.path.exists(asm_path):
                with open(asm_path, "r", encoding='utf-8') as f:
                    compilation_stats["assembly_code"] = f.read()
            else:
                compilation_stats["errors"] = "No se generó el archivo .s"
                return compilation_stats
            
            bin_path = os.path.join(tmpdir, "programa_bin")
            gcc_result = subprocess.run(
                ["gcc", "-g", "-no-pie", asm_path, "-o", bin_path],
                capture_output=True, 
                text=True,
                timeout=15
            )
            
            if gcc_result.returncode != 0:
                compilation_stats["errors"] = f"Error en GCC:\n{gcc_result.stderr}"
                return compilation_stats
            
            start_time = time.time()
            
            run_result = subprocess.run(
                [bin_path], 
                capture_output=True, 
                text=True,
                timeout=10
            )
            
            compilation_stats["execution_time"] = time.time() - start_time
            compilation_stats["execution_output"] = run_result.stdout
            compilation_stats["return_code"] = run_result.returncode
            compilation_stats["success"] = True
            
            if run_result.stderr:
                compilation_stats["errors"] = f"Errores de ejecución:\n{run_result.stderr}"
            
            return compilation_stats
            
        except subprocess.TimeoutExpired:
            compilation_stats["errors"] = "Timeout: El proceso tardó demasiado tiempo"
            return compilation_stats
        except FileNotFoundError:
            compilation_stats["errors"] = f"No se encontró el compilador en: {compilador_path}"
            return compilation_stats
        except Exception as e:
            compilation_stats["errors"] = f"Error inesperado: {str(e)}"
            return compilation_stats

def show_metrics(stats):
    col1, col2, col3, col4 = st.columns(4)
    
    with col1:
        st.markdown(f"""
        <div class="metric-card">
            <h3>{stats['compilation_time']:.3f}s</h3>
            <p>⏱️ Tiempo de Compilación</p>
        </div>
        """, unsafe_allow_html=True)
    
    with col2:
        st.markdown(f"""
        <div class="metric-card">
            <h3>{stats['execution_time']:.3f}s</h3>
            <p>🚀 Tiempo de Ejecución</p>
        </div>
        """, unsafe_allow_html=True)
    
    with col3:
        lines = len(stats['assembly_code'].split('\n')) if stats['assembly_code'] else 0
        st.markdown(f"""
        <div class="metric-card">
            <h3>{lines}</h3>
            <p>📄 Líneas de Assembly</p>
        </div>
        """, unsafe_allow_html=True)
    
    with col4:
        if stats['return_code'] is not None:
            if stats['return_code'] == 0:
                status_class = "status-success"
                status_text = "✅ ÉXITO"
            elif stats['return_code'] == -11:
                status_class = "status-error" 
                status_text = "❌ SEGFAULT"
            else:
                status_class = "status-warning"
                status_text = f"⚠️ ERROR {stats['return_code']}"
        else:
            status_class = "status-warning"
            status_text = "⏳ PENDIENTE"
            
        st.markdown(f"""
        <div class="metric-card">
            <div class="{status_class}">{status_text}</div>
            <p>📊 Estado</p>
        </div>
        """, unsafe_allow_html=True)

def main():
    load_css()
    create_header()
    
    with st.sidebar:
        st.markdown("### ⚙️ Configuración")
        
        compilador_path = st.text_input(
            "📂 Ruta del Compilador:", 
            value="./main",
            help="Ruta al ejecutable de tu compilador"
        )
        
        st.markdown("---")
        st.markdown("### 📚 Ejemplos")
        
        examples = load_examples()
        selected_example = st.selectbox(
            "Selecciona un ejemplo:",
            ["Código personalizado"] + list(examples.keys())
        )
        
        if st.button("📥 Cargar Ejemplo"):
            if selected_example != "Código personalizado":
                st.session_state.codigo = examples[selected_example]
                st.rerun()
        
        st.markdown("---")
        st.markdown("### ℹ️ Información")
        st.info("""
        **Instrucciones:**
        1. Escribe tu código C
        2. Haz clic en 'Compilar y Ejecutar'
        3. Ve el assembly generado
        4. Revisa los resultados
        5. Tener en cuenta que no es un compilador completo, sino un entorno de aprendizaje
        
        **Atajos:**
        - Ctrl+Enter: Compilar
        """)
    
    col1, col2 = st.columns([1.5, 1])
    
    with col1:
        st.markdown("### 📝 Editor de Código")
        
        codigo_inicial = """#include <stdio.h>
int main() {
    printf("¡Hola, mundo estoy programando en c!\n");
    return 0;
}"""
        
        if "codigo" not in st.session_state:
            st.session_state.codigo = codigo_inicial
        
        codigo = st.text_area(
            "Escribe tu código C aquí:",
            value=st.session_state.codigo,
            height=400,
            key="editor",
            help="Editor de código C con syntax highlighting"
        )
        
        st.session_state.codigo = codigo
        
        col_btn1, col_btn2, col_btn3 = st.columns(3)
        
        with col_btn1:
            compile_btn = st.button("🚀 Compilar y Ejecutar", type="primary", use_container_width=True)
        
        with col_btn2:
            if st.button("🧹 Limpiar", use_container_width=True):
                st.session_state.codigo = ""
                st.rerun()
        
        with col_btn3:
            if st.button("📥 Descargar .c", use_container_width=True):
                st.download_button(
                    label="💾 Descargar .c",
                    data=codigo,
                    file_name="programa.c",
                    mime="text/plain",
                    use_container_width=True
                )
    
    with col2:
        st.markdown("### 📊 Resultados")
        
        if compile_btn and codigo.strip():
            with st.spinner("🔄 Compilando código..."):
                stats = compile_and_run(codigo, compilador_path)
            
            show_metrics(stats)
            
            if stats["success"]:
                tab1, tab2, tab3 = st.tabs(["🔧 Assembly", "🖥️ Ejecución", "📈 Estadísticas"])
                
                with tab1:
                    st.markdown("**Código Assembly Generado:**")
                    if stats["assembly_code"]:
                        st.code(stats["assembly_code"], language="asm")
                        
                        col_asm1, col_asm2, col_asm3 = st.columns(3)
                        
                        with col_asm1:
                            st.download_button(
                                label="📥 Descargar .s",
                                data=stats["assembly_code"],
                                file_name="programa.s",
                                mime="text/plain",
                                key="download_assembly",
                                help="Descargar el código assembly generado"
                            )
                        
                        with col_asm2:
                            lines = stats["assembly_code"].split('\n')
                            instructions = [line.strip() for line in lines if line.strip() and not line.strip().startswith('#') and not line.strip().startswith('.') and ':' not in line]
                            st.metric("🔧 Instrucciones", len(instructions))
                        
                        with col_asm3:
                            mov_count = sum(1 for line in lines if 'mov' in line.lower())
                            st.metric("📊 Movimientos", mov_count)
                            
                        st.markdown("---")
                        st.markdown("**📈 Análisis del Assembly:**")
                        
                        analysis_col1, analysis_col2 = st.columns(2)
                        
                        with analysis_col1:
                            instruction_types = {
                                "Movimientos": sum(1 for line in lines if any(inst in line.lower() for inst in ['movq', 'movl', 'movb'])),
                                "Aritmética": sum(1 for line in lines if any(inst in line.lower() for inst in ['addq', 'subq', 'imulq', 'idivq'])),
                                "Comparaciones": sum(1 for line in lines if any(inst in line.lower() for inst in ['cmpq', 'testq'])),
                                "Saltos": sum(1 for line in lines if any(inst in line.lower() for inst in ['jmp', 'jz', 'jnz', 'je', 'jne'])),
                                "Stack": sum(1 for line in lines if any(inst in line.lower() for inst in ['pushq', 'popq'])),
                                "Llamadas": sum(1 for line in lines if 'call' in line.lower())
                            }
                            
                            st.markdown("**Tipos de Instrucciones:**")
                            for inst_type, count in instruction_types.items():
                                if count > 0:
                                    st.write(f"• {inst_type}: {count}")
                        
                        with analysis_col2:
                            registers = ['%rax', '%rbx', '%rcx', '%rdx', '%rsi', '%rdi', '%rbp', '%rsp']
                            reg_usage = {}
                            
                            for reg in registers:
                                reg_usage[reg] = sum(1 for line in lines if reg in line.lower())
                            
                            used_regs = {k: v for k, v in reg_usage.items() if v > 0}
                            
                            if used_regs:
                                st.markdown("**Uso de Registros:**")
                                for reg, count in sorted(used_regs.items(), key=lambda x: x[1], reverse=True)[:5]:
                                    st.write(f"• {reg}: {count} veces")
                        
                        st.markdown("---")
                        st.markdown("**🗂️ Secciones del Assembly:**")
                        
                        sections = {
                            "📊 .data": [line for line in lines if line.strip().startswith('.data') or 'print_fmt:' in line],
                            "📝 .text": [line for line in lines if line.strip().startswith('.text')],
                            "🏷️ Labels": [line for line in lines if line.strip().endswith(':') and not line.strip().startswith('.') and 'print_fmt' not in line],
                            "💬 Comentarios": [line for line in lines if line.strip().startswith('#')]
                        }
                        
                        section_col1, section_col2 = st.columns(2)
                        
                        with section_col1:
                            for section, content in list(sections.items())[:2]:
                                if content:
                                    st.write(f"{section}: {len(content)} líneas")
                        
                        with section_col2:
                            for section, content in list(sections.items())[2:]:
                                if content:
                                    st.write(f"{section}: {len(content)} líneas")
                        
                    else:
                        st.warning("No se generó código assembly")
                
                with tab2:
                    st.markdown("**Resultado de la Ejecución:**")
                    
                    if stats["execution_output"]:
                        st.code(stats["execution_output"], language="text")
                        
                        st.download_button(
                            label="📥 Descargar Salida",
                            data=stats["execution_output"],
                            file_name="output.txt",
                            mime="text/plain",
                            key="download_output",
                            help="Descargar la salida del programa"
                        )
                    else:
                        st.info("El programa no produjo salida en stdout")
                    
                    if stats["return_code"] is not None:
                        col_status1, col_status2 = st.columns(2)
                        
                        with col_status1:
                            if stats["return_code"] == 0:
                                st.success(f"✅ Programa terminó exitosamente")
                                st.balloons()  # Celebración visual
                            elif stats["return_code"] == -11:
                                st.error("❌ Segmentation Fault")
                                st.markdown("""
                                **💡 Posibles causas del Segfault:**
                                - Puntero no inicializado
                                - Desreferencia de puntero NULL
                                - Acceso fuera de bounds de array
                                - Stack overflow por recursión infinita
                                - Error en cálculo de offsets de struct
                                """)
                            elif stats["return_code"] == -6:
                                st.error("❌ Abort Signal (SIGABRT)")
                            elif stats["return_code"] == -9:
                                st.error("❌ Killed (SIGKILL)")
                            elif stats["return_code"] < 0:
                                st.warning(f"⚠️ Programa terminó con señal: {abs(stats['return_code'])}")
                            else:
                                st.warning(f"⚠️ Programa terminó con código de error: {stats['return_code']}")
                        
                        with col_status2:
                            st.metric("🔢 Código de Retorno", stats['return_code'])
                            
                            if stats["execution_time"] > 0:
                                if stats["execution_time"] < 0.001:
                                    performance = "⚡ Muy Rápido"
                                elif stats["execution_time"] < 0.1:
                                    performance = "🚀 Rápido" 
                                elif stats["execution_time"] < 1.0:
                                    performance = "✅ Normal"
                                else:
                                    performance = "🐌 Lento"
                                
                                st.metric("⚡ Rendimiento", performance)
                    
                    if stats["errors"] and "Errores de ejecución:" in stats["errors"]:
                        st.markdown("---")
                        st.markdown("**⚠️ Errores de Ejecución:**")
                        error_lines = stats["errors"].split("Errores de ejecución:\n")[1] if "Errores de ejecución:\n" in stats["errors"] else stats["errors"]
                        st.code(error_lines, language="text")
                
                with tab3:
                    st.markdown("**Estadísticas de Compilación:**")
                    
                    col_stat1, col_stat2 = st.columns(2)
                    
                    with col_stat1:
                        st.metric("⏱️ Tiempo de Compilación", f"{stats['compilation_time']:.3f}s")
                        st.metric("📄 Líneas de Assembly", len(stats['assembly_code'].split('\n')) if stats['assembly_code'] else 0)
                    
                    with col_stat2:
                        st.metric("🚀 Tiempo de Ejecución", f"{stats['execution_time']:.3f}s")
                        st.metric("🔢 Código de Salida", stats['return_code'] if stats['return_code'] is not None else "N/A")
                    
                    if stats['compilation_time'] > 0 and stats['execution_time'] > 0:
                        st.markdown("---")
                        st.markdown("**📊 Distribución de Tiempos:**")
                                                
                        tiempo_total = stats['compilation_time'] + stats['execution_time']
                        
                        df_tiempos = pd.DataFrame({
                            'Fase': ['Compilación', 'Ejecución'],
                            'Tiempo (s)': [stats['compilation_time'], stats['execution_time']],
                            'Porcentaje': [
                                (stats['compilation_time'] / tiempo_total) * 100,
                                (stats['execution_time'] / tiempo_total) * 100
                            ]
                        })
                        
                        st.bar_chart(df_tiempos.set_index('Fase')['Tiempo (s)'])
                        
                        col_perc1, col_perc2 = st.columns(2)
                        with col_perc1:
                            st.info(f"🔨 Compilación: {df_tiempos.iloc[0]['Porcentaje']:.1f}%")
                        with col_perc2:
                            st.info(f"⚡ Ejecución: {df_tiempos.iloc[1]['Porcentaje']:.1f}%")
                    
                    st.markdown("---")
                    st.markdown("**🎯 Análisis de Eficiencia:**")
                    
                    if stats['assembly_code']:
                        lines_of_code = len([line for line in codigo.split('\n') if line.strip() and not line.strip().startswith('//')])
                        asm_lines = len([line for line in stats['assembly_code'].split('\n') if line.strip() and not line.strip().startswith('#')])
                        
                        if lines_of_code > 0:
                            expansion_ratio = asm_lines / lines_of_code
                            
                            col_eff1, col_eff2, col_eff3 = st.columns(3)
                            
                            with col_eff1:
                                st.metric("📝 Líneas de C", lines_of_code)
                            
                            with col_eff2:
                                st.metric("⚙️ Líneas de ASM", asm_lines)
                            
                            with col_eff3:
                                st.metric("📈 Ratio Expansión", f"{expansion_ratio:.1f}x")
                            
                            if expansion_ratio < 5:
                                efficiency = "🎯 Muy Eficiente"
                                color = "green"
                            elif expansion_ratio < 10:
                                efficiency = "✅ Eficiente"
                                color = "blue"
                            elif expansion_ratio < 20:
                                efficiency = "⚠️ Normal"
                                color = "orange"
                            else:
                                efficiency = "🔄 Mejorable"
                                color = "red"
                            
                            st.markdown(f"**Eficiencia del Compilador:** :{color}[{efficiency}]")
                    
                    st.markdown("---")
                    
                    reporte = f"""REPORTE DE COMPILACIÓN
{'='*50}

INFORMACIÓN GENERAL:
- Fecha: {time.strftime('%Y-%m-%d %H:%M:%S')}
- Líneas de código C: {len([line for line in codigo.split('\n') if line.strip()])}
- Estado: {'Exitoso' if stats['success'] else 'Error'}

TIEMPOS:
- Compilación: {stats['compilation_time']:.3f}s
- Ejecución: {stats['execution_time']:.3f}s
- Total: {stats['compilation_time'] + stats['execution_time']:.3f}s

RESULTADOS:
- Código de salida: {stats['return_code']}
- Líneas de assembly: {len(stats['assembly_code'].split('\n')) if stats['assembly_code'] else 0}

CÓDIGO FUENTE:
{'-'*20}
{codigo}

CÓDIGO ASSEMBLY:
{'-'*20}
{stats['assembly_code'] if stats['assembly_code'] else 'No generado'}

SALIDA DEL PROGRAMA:
{'-'*20}
{stats['execution_output'] if stats['execution_output'] else 'Sin salida'}

ERRORES (si los hay):
{'-'*20}
{stats['errors'] if stats['errors'] else 'Ninguno'}
"""
                    
                    st.download_button(
                        label="📋 Descargar Reporte Completo",
                        data=reporte,
                        file_name=f"reporte_compilacion_{int(time.time())}.txt",
                        mime="text/plain",
                        key="download_report",
                        help="Descargar reporte completo de la compilación"
                    )
            
            if stats["errors"]:
                st.error(stats["errors"])
        
        elif compile_btn and not codigo.strip():
            st.warning("⚠️ Por favor, ingresa código para compilar")
        
        else:
            st.info("""
            👋 **¡Bienvenido al Compilador C!**
            Escribe tu código C en el editor de la izquierda y haz clic en 
            "Compilar y Ejecutar" para ver:
            
            - 🔧 Código assembly x86-64 generado
            - 🖥️ Resultado de la ejecución  
            - 📊 Estadísticas de rendimiento
            - ⚡ Métricas en tiempo real
            
            **Características soportadas:**
            - ✅ Variables y operaciones aritméticas
            - ✅ Punteros y direcciones de memoria  
            - ✅ Estructuras (structs)
            - ✅ Funciones y llamadas
            - ✅ Bucles (for, while)
            - ✅ Condicionales (if, else)
            """)

if __name__ == "__main__":
    main()