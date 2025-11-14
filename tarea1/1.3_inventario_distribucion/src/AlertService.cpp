#include "AlertService.hpp"
#include <iostream>

void AlertService::mostrarAlertas(const Almacen& almacen) {
    auto alertas = almacen.obtenerAlertas();
    if (alertas.empty()) {
        std::cout << "No hay alertas activas.\n";
        return;
    }

    std::cout << "\nProductos por debajo del umbral:\n";
    for (const auto& [almacenIdx, productoIdx] : alertas) {
        std::cout << " - Almacen " << (almacenIdx + 1)
                  << ", Producto " << (productoIdx + 1)
                  << " (Stock: " << almacen.getStock(almacenIdx, productoIdx) << ")\n";
    }
}
