#include <iostream>
#include <limits>
#include "Hotel.h"

void limpiarEntrada() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int leerEntero(const std::string& prompt) {
    int valor;
    while (true) {
        std::cout << prompt;
        if (std::cin >> valor) {
            return valor;
        }
        std::cout << "Entrada invalida. Intente nuevamente.\n";
        limpiarEntrada();
    }
}

double leerDouble(const std::string& prompt) {
    double valor;
    while (true) {
        std::cout << prompt;
        if (std::cin >> valor && valor >= 0) {
            return valor;
        }
        std::cout << "Entrada invalida. Intente nuevamente.\n";
        limpiarEntrada();
    }
}

std::string leerString(const std::string& prompt) {
    std::string valor;
    std::cout << prompt;
    limpiarEntrada();
    std::getline(std::cin, valor);
    return valor;
}

void inicializarHotel(Hotel& hotel) {
    // Habitaciones predefinidas para demostracion
    hotel.agregarHabitacion(101, TipoHabitacion::SENCILLA, 80.0);
    hotel.agregarHabitacion(102, TipoHabitacion::SENCILLA, 85.0);
    hotel.agregarHabitacion(201, TipoHabitacion::DOBLE, 120.0);
    hotel.agregarHabitacion(202, TipoHabitacion::DOBLE, 125.0);
    hotel.agregarHabitacion(301, TipoHabitacion::SUITE, 200.0);
    hotel.agregarHabitacion(302, TipoHabitacion::SUITE, 250.0);
}

int main() {
    Hotel hotel;
    inicializarHotel(hotel);
    
    int opcion;
    
    while (true) {
        std::cout << "\n=== SISTEMA DE GESTION HOTELERA ===\n";
        std::cout << "1. Agregar habitacion\n";
        std::cout << "2. Reservar habitacion\n";
        std::cout << "3. Liberar habitacion\n";
        std::cout << "4. Mostrar habitaciones disponibles por tipo\n";
        std::cout << "5. Consultar habitacion mas cara disponible\n";
        std::cout << "6. Mostrar estadisticas\n";
        std::cout << "7. Mostrar todas las habitaciones\n";
        std::cout << "0. Salir\n";
        
        opcion = leerEntero("Seleccione opcion: ");
        
        switch (opcion) {
            case 1: {
                int numero = leerEntero("Numero de habitacion: ");
                int tipoInt = leerEntero("Tipo (0=Sencilla, 1=Doble, 2=Suite): ");
                
                if (tipoInt < 0 || tipoInt > 2) {
                    std::cout << "Tipo invalido.\n";
                    break;
                }
                
                double precio = leerDouble("Precio por noche: $");
                hotel.agregarHabitacion(numero, static_cast<TipoHabitacion>(tipoInt), precio);
                break;
            }
            
            case 2: {
                int numero = leerEntero("Numero de habitacion a reservar: ");
                std::string nombre = leerString("Nombre del cliente: ");
                std::string cedula = leerString("Cedula: ");
                std::string telefono = leerString("Telefono: ");
                
                Cliente cliente(nombre, cedula, telefono);
                hotel.reservarHabitacion(numero, cliente);
                break;
            }
            
            case 3: {
                int numero = leerEntero("Numero de habitacion a liberar: ");
                hotel.liberarHabitacion(numero);
                break;
            }
            
            case 4: {
                int tipoInt = leerEntero("Tipo (0=Sencilla, 1=Doble, 2=Suite): ");
                if (tipoInt >= 0 && tipoInt <= 2) {
                    hotel.mostrarDisponiblesPorTipo(static_cast<TipoHabitacion>(tipoInt));
                } else {
                    std::cout << "Tipo invalido.\n";
                }
                break;
            }
            
            case 5: {
                Habitacion* masCaraDisponible = hotel.obtenerMasCaraDisponible();
                if (masCaraDisponible) {
                    std::cout << "\nHabitacion mas cara disponible:\n";
                    masCaraDisponible->mostrarInfo();
                } else {
                    std::cout << "No hay habitaciones disponibles.\n";
                }
                break;
            }
            
            case 6:
                hotel.mostrarEstadisticas();
                break;
                
            case 7:
                hotel.mostrarTodasHabitaciones();
                break;
                
            case 0:
                std::cout << "Saliendo del sistema...\n";
                return 0;
                
            default:
                std::cout << "Opcion invalida.\n";
                break;
        }
    }
    
    return 0;
}