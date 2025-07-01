#!/bin/bash

# Script para ejecutar la API del compilador

echo "🚀 Configurando API del Compilador"

# Colores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Función para mostrar mensajes
log() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Verificar si Python está instalado
if ! command -v python3 &> /dev/null; then
    error "Python3 no está instalado"
    exit 1
fi

# Verificar si pip está instalado
if ! command -v pip3 &> /dev/null; then
    error "pip3 no está instalado"
    exit 1
fi

# Verificar si GCC está instalado
if ! command -v gcc &> /dev/null; then
    error "GCC no está instalado. Instálalo con: sudo apt install gcc"
    exit 1
fi

success "Verificaciones básicas pasadas"

# Crear entorno virtual si no existe
if [ ! -d "venv" ]; then
    log "Creando entorno virtual..."
    python3 -m venv venv
fi

# Activar entorno virtual
log "Activando entorno virtual..."
source venv/bin/activate

# Instalar dependencias
log "Instalando dependencias..."
pip install -r requirements.txt

# Verificar que el compilador existe
COMPILER_PATH="./main"
if [ ! -f "$COMPILER_PATH" ]; then
    warning "No se encontró el compilador en $COMPILER_PATH"
    echo "Por favor, asegúrate de que tu compilador esté compilado y en la ruta correcta"
    echo "O modifica COMPILER_EXECUTABLE en main.py"
fi

# Función para manejar Ctrl+C
cleanup() {
    echo -e "\n${YELLOW}Deteniendo servidor...${NC}"
    exit 0
}

trap cleanup INT

# Ejecutar servidor
success "Iniciando servidor FastAPI..."
echo "📡 Servidor disponible en: http://localhost:8000"
echo "📖 Documentación automática en: http://localhost:8000/docs"
echo "🔍 Health check: http://localhost:8000/health"
echo ""
echo "Presiona Ctrl+C para detener el servidor"
echo ""

python main.py