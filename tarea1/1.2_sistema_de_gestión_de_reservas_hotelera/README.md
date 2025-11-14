# Sistema de Gestión de Reservas Hotelera

## Descripción
Sistema completo de gestión hotelera que automatiza el manejo de habitaciones y reservas usando **arreglos estáticos** y **programación orientada a objetos**.

## Criterios de Evaluación Cumplidos

### 1) Definición correcta de las estructuras de datos
- **Arreglo estático**: `Habitacion habitaciones[MAX_HABITACIONES]` (máximo 50)
- **Enum class**: `TipoHabitacion` para tipos de habitación
- **Clases**: `Cliente`, `Habitacion`, `Hotel`

### 2) Implementación de funciones para manipular arreglos
- `agregarHabitacion()`: Inserción en arreglo con validación
- `reservarHabitacion()`: Búsqueda y modificación
- `mostrarDisponiblesPorTipo()`: Filtrado por criterios
- `obtenerMasCaraDisponible()`: Búsqueda del máximo

### 3) Codificación funcional del sistema en un IDE
- Compilación exitosa con CMake
- Estructura modular (headers/implementaciones)
- Menú interactivo completo

### 4) Uso apropiado de estructuras repetitivas
- **Bucles for**: Recorrido de arreglo de habitaciones
- **Bucles while**: Menú principal y validación de entrada
- **4.1) Condicionales anidadas**: Validaciones múltiples en reservas

### 5) Manipulación efectiva de arreglos unidimensionales
- Arreglo unidimensional de objetos `Habitacion`
- Gestión manual de índices con `totalHabitaciones`
- Acceso directo por posición

### 6) Desarrollo de funciones que trabajen directamente con arreglos estáticos
- Sin uso de contenedores STL dinámicos
- Paso de referencias a objetos del arreglo
- Límite fijo de 50 habitaciones

### 7) Entrega puntual y cumplimiento de instrucciones
- **Código en C++**: Implementación completa
- **Funcionalidades requeridas**: Todas implementadas
- **Compilación exitosa**: CMakeLists.txt incluido

## Funcionalidades Implementadas

### a) Registrar reservas (máximo 50 habitaciones)
```cpp
void agregarHabitacion(int numero, TipoHabitacion tipo, double precio);
bool reservarHabitacion(int numero, const Cliente& cliente);
```

### b) Calcular ocupación total e ingreso estimado
```cpp
double calcularOcupacionTotal() const;    // Porcentaje de ocupación
double calcularIngresoEstimado() const;   // Ingresos por habitaciones ocupadas
```

### c) Mostrar habitaciones disponibles por tipo
```cpp
void mostrarDisponiblesPorTipo(TipoHabitacion tipo) const;
```

### d) Consultar habitación más cara disponible
```cpp
Habitacion* obtenerMasCaraDisponible();
```

## Estructura del Proyecto

```
1.2_sistema_de_gestión de_reservas_hotelera/
├── include/
│   ├── Cliente.h       # Clase para datos del cliente
│   ├── Habitacion.h    # Clase habitación con enum de tipos
│   └── Hotel.h         # Clase principal con arreglo estático
├── src/
│   ├── Cliente.cpp     # Implementación cliente
│   ├── Habitacion.cpp  # Gestión de estados de habitación
│   ├── Hotel.cpp       # Lógica principal del hotel
│   └── main.cpp        # Programa principal con menú
├── CMakeLists.txt      # Configuración de compilación
└── README.md           # Esta documentación
```

## Compilación y Ejecución

```bash
cd "1.2_sistema_de_gestión de_reservas_hotelera"
mkdir build && cd build
cmake ..
make
./hotel_reservas
```

## Características Técnicas

- **Arreglo estático**: 50 habitaciones máximo
- **Tipos de habitación**: Sencilla, Doble, Suite
- **Gestión de estados**: Disponible/Ocupada
- **Validaciones**: Números únicos, entradas válidas
- **Cálculos**: Ocupación porcentual, ingresos totales
- **Búsquedas**: Lineal por número, tipo, precio máximo

## Ejemplo de Uso

1. **Agregar habitaciones**: Número, tipo, precio
2. **Reservar**: Seleccionar habitación + datos cliente
3. **Consultar disponibilidad**: Por tipo de habitación
4. **Ver estadísticas**: Ocupación e ingresos
5. **Habitación premium**: Más cara disponible

El sistema demuestra el uso efectivo de **arreglos estáticos**, **estructuras repetitivas** y **manipulación directa de datos** según los criterios académicos establecidos.