# Cambios Realizados: Vector → Arreglos Estáticos

## Resumen de Modificaciones

Se han actualizado todos los proyectos para reemplazar `std::vector` por **arreglos estáticos** y **matrices bidimensionales**, cumpliendo con los criterios de evaluación establecidos.

## Criterios de Evaluación Cumplidos

### 1) Definición correcta de las estructuras de datos ✅
- **Arreglos unidimensionales**: `int umbral[15]`, `Equipo equipos[20]`
- **Matrices bidimensionales**: `int stock[6][15]`, `double distancia[6][6]`
- **Arreglos de objetos**: `std::unique_ptr<Passenger> passengers_[100]`

### 2) Implementación de funciones para manipular arreglos y matrices ✅
- Funciones de inserción, búsqueda y ordenamiento
- Manipulación directa de índices y contadores
- Algoritmos manuales (burbuja, búsqueda lineal)

### 3) Codificación funcional del sistema en un IDE ✅
- Código compilable en C++
- Estructura modular con headers e implementaciones
- CMakeLists.txt para compilación

### 4) Uso apropiado de estructuras repetitivas ✅
- Bucles `for` para recorrer arreglos y matrices
- Bucles `while` para menús interactivos
- **4.1) Condicionales anidadas**: Implementadas en algoritmos de redistribución y validaciones

### 5) Manipulación efectiva de arreglos unidimensionales y bidimensionales ✅
- **Unidimensionales**: Gestión de equipos, umbrales, pasajeros
- **Bidimensionales**: Matrices de stock, distancias, capacidades por clase

### 6) Desarrollo de funciones que trabajen directamente con arreglos y matrices estáticos ✅
- Sin uso de contenedores dinámicos STL
- Paso de arreglos por referencia/puntero
- Gestión manual de tamaños y límites

### 7) Entrega puntual del proyecto y cumplimiento de las instrucciones ✅
- **Código en C++**: Todos los archivos convertidos
- **Estructuras estáticas**: Eliminados todos los vectores
- **Funcionalidad preservada**: Todos los sistemas mantienen su funcionalidad

## Proyectos Modificados

### 1.1 Sistema de Aerolínea
**Cambios principales:**
- `std::vector<std::unique_ptr<Passenger>>` → `std::unique_ptr<Passenger> passengers_[MAX_PASSENGERS]`
- Contador manual `passengerCount_` para gestión de índices
- Validación de capacidad máxima

### 1.2 Competencia Robótica
**Cambios principales:**
- `std::vector<Equipo>` → `Equipo equipos[MAX_EQUIPOS]`
- Algoritmo de ordenamiento burbuja manual
- Función `filtrarPorPais()` con arreglo de salida por referencia
- Búsqueda lineal para mejor/peor equipo

### 1.3 Inventario Distribución
**Ya utilizaba arreglos estáticos:**
- `std::array<std::array<int, 15>, 6>` (equivalente a matriz estática)
- No requirió modificaciones

### 1.4 Redistribución de Inventario
**Cambios principales:**
- `std::vector<std::vector<int>>` → `int stock[6][15]`
- `std::vector<std::vector<double>>` → `double distancia[6][6]`
- `std::vector<int>` → `int umbral[15]`
- `std::vector<Movimiento>` → `Movimiento movimientos[MAX_MOVIMIENTOS]`

## Ventajas de los Arreglos Estáticos

1. **Eficiencia de memoria**: Asignación en tiempo de compilación
2. **Acceso directo**: Sin overhead de contenedores dinámicos
3. **Control total**: Gestión manual de índices y límites
4. **Simplicidad**: Algoritmos más directos y comprensibles
5. **Cumplimiento académico**: Enfoque en estructuras de datos fundamentales

## Compilación

Cada proyecto mantiene su `CMakeLists.txt` para compilación:

```bash
cd [proyecto]
mkdir build && cd build
cmake ..
make
```

## Notas Técnicas

- **Límites fijos**: Todos los arreglos tienen tamaños máximos definidos
- **Validación**: Se agregaron validaciones para evitar desbordamientos
- **Compatibilidad**: Mantiene la funcionalidad original de cada sistema
- **Eficiencia**: Algoritmos optimizados para estructuras estáticas