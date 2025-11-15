#include "Almacen.hpp"

Almacen::Almacen() : umbralMinimo(10) {
    // Inicializamos la matriz con ceros
    for (auto& fila : stock)
        fila.fill(0);
}

void Almacen::registrarExistencias() {
    std::cout << "\n=== Registro de Existencias ===\n";
    for (int i = 0; i < NUM_ALMACENES; ++i) {
        std::cout << "\n>> Almacén " << (i + 1) << ":\n";
        for (int j = 0; j < NUM_PRODUCTOS; ++j) {
            int cantidad;
            std::cout << "   Producto " << (j + 1) << " cantidad: ";
            if (!(std::cin >> cantidad) || cantidad < 0) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cerr << "❌ Entrada inválida. Se establecerá en 0.\n";
                cantidad = 0;
            }
            stock[i][j] = cantidad;
        }
    }
}

void Almacen::detectarAgotados() const {
    std::cout << "\n=== Productos Agotados ===\n";
    bool agotado = false;

    for (int i = 0; i < NUM_ALMACENES; ++i) {
        for (int j = 0; j < NUM_PRODUCTOS; ++j) {
            if (stock[i][j] == 0) {
                std::cout << "⚠️  Almacén " << (i + 1)
                          << " - Producto " << (j + 1)
                          << " está agotado.\n";
                agotado = true;
            }
        }
    }

    if (!agotado)
        std::cout << "✅ No hay productos agotados.\n";
}

void Almacen::mostrarMenorStock() const {
    std::cout << "\n=== Almacén con Menor Stock ===\n";
    int menor = std::numeric_limits<int>::max();
    int indice = -1;

    for (int i = 0; i < NUM_ALMACENES; ++i) {
        int total = std::accumulate(stock[i].begin(), stock[i].end(), 0);
        if (total < menor) {
            menor = total;
            indice = i;
        }
    }

    if (indice >= 0)
        std::cout << "🏭 El Almacén " << (indice + 1)
                  << " tiene el menor stock total con " << menor << " unidades.\n";
}

void Almacen::emitirAlertas() const {
    std::cout << "\n=== Alertas de Stock Bajo (umbral: " << umbralMinimo << ") ===\n";
    bool alerta = false;

    for (int i = 0; i < NUM_ALMACENES; ++i) {
        for (int j = 0; j < NUM_PRODUCTOS; ++j) {
            if (stock[i][j] > 0 && stock[i][j] < umbralMinimo) {
                std::cout << "⚠️  Almacén " << (i + 1)
                          << " - Producto " << (j + 1)
                          << " tiene stock bajo: " << stock[i][j] << "\n";
                alerta = true;
            }
        }
    }

    if (!alerta)
        std::cout << "✅ Todos los productos están por encima del umbral.\n";
}

void Almacen::configurarUmbral() {
    std::cout << "\nIngrese nuevo umbral mínimo: ";
    int nuevo;
    if (!(std::cin >> nuevo) || nuevo <= 0) {
        std::cerr << "❌ Umbral inválido. Se mantiene el valor anterior: " << umbralMinimo << "\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    umbralMinimo = nuevo;
    std::cout << "✅ Umbral actualizado a " << umbralMinimo << "\n";
}

void Almacen::mostrarStockGeneral() const {
    std::cout << "\n=== Resumen de Stock por Almacén ===\n";
    for (int i = 0; i < NUM_ALMACENES; ++i) {
        int total = std::accumulate(stock[i].begin(), stock[i].end(), 0);
        std::cout << "Almacén " << (i + 1) << " → " << total << " unidades totales.\n";
    }
}
