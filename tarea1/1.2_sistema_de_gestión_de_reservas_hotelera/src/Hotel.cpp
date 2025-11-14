#include "Hotel.h"
#include <iostream>
#include <iomanip>

Hotel::Hotel() : totalHabitaciones(0) {}

void Hotel::agregarHabitacion(int numero, TipoHabitacion tipo, double precio) {
    if (totalHabitaciones >= MAX_HABITACIONES) {
        std::cout << "Hotel lleno. No se pueden agregar mas habitaciones.\n";
        return;
    }
    
    // Verificar que no exista habitacion con el mismo numero
    for (int i = 0; i < totalHabitaciones; ++i) {
        if (habitaciones[i].getNumero() == numero) {
            std::cout << "Ya existe habitacion con numero " << numero << "\n";
            return;
        }
    }
    
    habitaciones[totalHabitaciones] = Habitacion(numero, tipo, precio);
    totalHabitaciones++;
    std::cout << "Habitacion " << numero << " agregada exitosamente.\n";
}

bool Hotel::reservarHabitacion(int numero, const Cliente& cliente) {
    for (int i = 0; i < totalHabitaciones; ++i) {
        if (habitaciones[i].getNumero() == numero) {
            if (habitaciones[i].estaOcupada()) {
                std::cout << "Habitacion " << numero << " ya esta ocupada.\n";
                return false;
            }
            habitaciones[i].reservar(cliente);
            std::cout << "Habitacion " << numero << " reservada para " << cliente.getNombre() << "\n";
            return true;
        }
    }
    std::cout << "Habitacion " << numero << " no encontrada.\n";
    return false;
}

void Hotel::liberarHabitacion(int numero) {
    for (int i = 0; i < totalHabitaciones; ++i) {
        if (habitaciones[i].getNumero() == numero) {
            if (!habitaciones[i].estaOcupada()) {
                std::cout << "Habitacion " << numero << " ya esta disponible.\n";
                return;
            }
            habitaciones[i].liberar();
            std::cout << "Habitacion " << numero << " liberada.\n";
            return;
        }
    }
    std::cout << "Habitacion " << numero << " no encontrada.\n";
}

void Hotel::mostrarDisponiblesPorTipo(TipoHabitacion tipo) const {
    std::string tipoStr;
    switch (tipo) {
        case TipoHabitacion::SENCILLA: tipoStr = "Sencilla"; break;
        case TipoHabitacion::DOBLE: tipoStr = "Doble"; break;
        case TipoHabitacion::SUITE: tipoStr = "Suite"; break;
    }
    
    std::cout << "\n=== Habitaciones " << tipoStr << " Disponibles ===\n";
    bool encontradas = false;
    
    for (int i = 0; i < totalHabitaciones; ++i) {
        if (habitaciones[i].getTipo() == tipo && !habitaciones[i].estaOcupada()) {
            habitaciones[i].mostrarInfo();
            encontradas = true;
        }
    }
    
    if (!encontradas) {
        std::cout << "No hay habitaciones " << tipoStr << " disponibles.\n";
    }
}

Habitacion* Hotel::obtenerMasCaraDisponible() {
    Habitacion* masCaraDisponible = nullptr;
    double precioMaximo = 0.0;
    
    for (int i = 0; i < totalHabitaciones; ++i) {
        if (!habitaciones[i].estaOcupada() && habitaciones[i].getPrecio() > precioMaximo) {
            precioMaximo = habitaciones[i].getPrecio();
            masCaraDisponible = &habitaciones[i];
        }
    }
    
    return masCaraDisponible;
}

double Hotel::calcularIngresoEstimado() const {
    double ingresoTotal = 0.0;
    
    for (int i = 0; i < totalHabitaciones; ++i) {
        if (habitaciones[i].estaOcupada()) {
            ingresoTotal += habitaciones[i].getPrecio();
        }
    }
    
    return ingresoTotal;
}

double Hotel::calcularOcupacionTotal() const {
    if (totalHabitaciones == 0) return 0.0;
    
    int ocupadas = 0;
    for (int i = 0; i < totalHabitaciones; ++i) {
        if (habitaciones[i].estaOcupada()) {
            ocupadas++;
        }
    }
    
    return (static_cast<double>(ocupadas) / totalHabitaciones) * 100.0;
}

void Hotel::mostrarTodasHabitaciones() const {
    std::cout << "\n=== Todas las Habitaciones ===\n";
    for (int i = 0; i < totalHabitaciones; ++i) {
        habitaciones[i].mostrarInfo();
    }
}

void Hotel::mostrarEstadisticas() const {
    std::cout << "\n=== Estadisticas del Hotel ===\n";
    std::cout << "Total habitaciones: " << totalHabitaciones << "\n";
    std::cout << "Ocupacion: " << std::fixed << std::setprecision(1) 
              << calcularOcupacionTotal() << "%\n";
    std::cout << "Ingreso estimado: $" << std::fixed << std::setprecision(2) 
              << calcularIngresoEstimado() << "\n";
    
    Habitacion* masCaraDisponible = const_cast<Hotel*>(this)->obtenerMasCaraDisponible();
    if (masCaraDisponible) {
        std::cout << "Habitacion mas cara disponible: ";
        masCaraDisponible->mostrarInfo();
    } else {
        std::cout << "No hay habitaciones disponibles.\n";
    }
}