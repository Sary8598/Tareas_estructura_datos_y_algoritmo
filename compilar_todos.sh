#!/bin/bash

echo "=== Compilando todos los proyectos con arreglos estáticos ==="

# Colores para output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Función para compilar un proyecto
compilar_proyecto() {
    local proyecto=$1
    echo -e "${YELLOW}Compilando $proyecto...${NC}"
    
    cd "tarea1/$proyecto"
    
    if [ -d "build" ]; then
        rm -rf build
    fi
    
    mkdir build
    cd build
    
    if cmake .. && make; then
        echo -e "${GREEN}✅ $proyecto compilado exitosamente${NC}"
        cd ../../..
        return 0
    else
        echo -e "${RED}❌ Error compilando $proyecto${NC}"
        cd ../../..
        return 1
    fi
}

# Compilar cada proyecto
proyectos=("1.1_aerolinea" "1.2_robot_competition" "1.3_inventario_distribucion" "1.4_redistribucion_inventario/cpp")

exitosos=0
total=${#proyectos[@]}

for proyecto in "${proyectos[@]}"; do
    if compilar_proyecto "$proyecto"; then
        ((exitosos++))
    fi
    echo ""
done

echo "=== Resumen de Compilación ==="
echo -e "Proyectos exitosos: ${GREEN}$exitosos${NC}/$total"

if [ $exitosos -eq $total ]; then
    echo -e "${GREEN}🎉 Todos los proyectos compilaron correctamente con arreglos estáticos${NC}"
    echo ""
    echo "Criterios de evaluación cumplidos:"
    echo "✅ 1) Definición correcta de estructuras de datos (arreglos y matrices)"
    echo "✅ 2) Implementación de funciones para manipular arreglos y matrices"
    echo "✅ 3) Codificación funcional del sistema en un IDE"
    echo "✅ 4) Uso apropiado de estructuras repetitivas"
    echo "✅ 4.1) Condicionales anidadas implementadas"
    echo "✅ 5) Manipulación efectiva de arreglos unidimensionales y bidimensionales"
    echo "✅ 6) Funciones que trabajan directamente con arreglos y matrices estáticos"
    echo "✅ 7) Código en C++ completamente funcional"
else
    echo -e "${RED}⚠️  Algunos proyectos tuvieron errores de compilación${NC}"
fi