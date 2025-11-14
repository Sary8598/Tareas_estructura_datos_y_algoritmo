# Sistema de Historial Web con Lista Doblemente Enlazada

## Descripción
Navegador web que implementa historial de navegación usando lista doblemente enlazada con capacidad de navegación bidireccional.

## Funcionalidades Implementadas

### a) Insertar nueva visita al final ✅
- URL y fecha/hora automática
- Inserción al final de la lista
- Actualización de página actual

### b) Navegación adelante/atrás ✅
- Navegación bidireccional desde página actual
- Punteros next/prev para movimiento
- Control de límites

### c) Eliminar URL específica ✅
- Búsqueda por URL exacta
- Eliminación con reconexión de enlaces
- Actualización de página actual si necesario

### d) Historial cronológico inverso ✅
- Orden de última a primera visita
- Recorrido desde tail hacia head
- Arreglos estáticos para presentación

### e) Medición de tiempos ✅
- Tiempo de inserción
- Tiempo de eliminación
- Tiempo de obtener historial
- Tiempo de navegación
- Tiempo total del programa

## Arquitectura Implementada

### Capas
- **HistoryRepository**: Lista doblemente enlazada con navegación
- **HistoryService**: Lógica de negocio y generación de fecha/hora
- **HistoryController**: Intermediario puro
- **HistoryView**: Manejo completo de UI

### Principios SOLID
- **S**: Responsabilidad única por capa
- **O**: Extensible mediante interfaces
- **L**: Sustitución de interfaces
- **I**: Interfaces segregadas
- **D**: Inversión de dependencias

## Estructuras de Datos

### WebPage
```cpp
struct WebPage {
    std::string url;
    std::string datetime;
    WebPage* next;
    WebPage* prev;
};
```

### PageArray (Arreglo Estático)
```cpp
struct PageArray {
    WebPage* pages[MAX_PAGES];
    int count;
};
```

### Navegación
- **current**: Puntero a página actual
- **navigateForward()**: current = current->next
- **navigateBackward()**: current = current->prev

## Funciones de Navegación

### Inserción al Final
```cpp
tail->next = newPage;
newPage->prev = tail;
tail = current = newPage;
```

### Navegación Bidireccional
```cpp
// Hacia adelante
if (current && current->next) {
    current = current->next;
}

// Hacia atrás
if (current && current->prev) {
    current = current->prev;
}
```

### Historial Inverso
```cpp
WebPage* temp = tail;
while (temp) {
    // Agregar a arreglo
    temp = temp->prev;  // De último a primero
}
```

## Compilación y Ejecución

```bash
make          # Compilar programa principal
make run      # Ejecutar programa interactivo
make demo     # Compilar y ejecutar demostración
make clean    # Limpiar archivos
```

## Complejidad Temporal
- **Inserción**: O(1) - al final de la lista
- **Navegación**: O(1) - acceso directo por punteros
- **Eliminación**: O(n) - busca por URL
- **Historial**: O(n) - recorre toda la lista
- **Espacio**: O(1) - arreglos estáticos