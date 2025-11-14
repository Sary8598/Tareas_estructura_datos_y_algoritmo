#include <iostream>
#include <limits>
#include "Flight.h"
#include "ClassType.h"

int readInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            return value;
        } else {
            std::cout << "Entrada invalida. Intente de nuevo.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

std::string readLine(const std::string& prompt) {
    std::string s;
    std::cout << prompt;
    std::getline(std::cin >> std::ws, s);
    return s;
}

int main() {
    try {
        std::cout << "----- Configuracion del vuelo -----\n";
        int capacity = readInt("Capacidad total del avion (ej. 100): ");
        double price1 = 0.0, price2 = 0.0, price3 = 0.0;

        std::cout << "Puede usar precios por defecto o ingresarlos.\n";
        int useDefault = readInt("Usar precios por defecto (1=si, 0=no): ");
        if (useDefault == 1) {
            price1 = 500.0;
            price2 = 300.0;
            price3 = 150.0;
        } else {
            std::cout << "Ingrese precio para Primera: ";
            std::cin >> price1;
            std::cout << "Ingrese precio para Segunda: ";
            std::cin >> price2;
            std::cout << "Ingrese precio para Tercera: ";
            std::cin >> price3;
            if (price1 < 0 || price2 < 0 || price3 < 0) {
                std::cerr << "Precios invalidos. Usando valores por defecto.\n";
                price1 = 500.0; price2 = 300.0; price3 = 150.0;
            }
        }

        Flight flight(capacity, price1, price2, price3);

        int option = -1;
        while (option != 0) {
            std::cout << "\n=== MENU ===\n";
            std::cout << "1 - Vender boleto\n";
            std::cout << "2 - Mostrar asientos vendidos por clase\n";
            std::cout << "3 - Mostrar ingreso estimado por clase y total\n";
            std::cout << "4 - Verificar si vuelo lleno\n";
            std::cout << "0 - Salir\n";
            option = readInt("Seleccione una opcion: ");

            try {
                if (option == 1) {
                    if (flight.isFull()) {
                        std::cout << "El avion esta completo. No se pueden vender mas boletos.\n";
                        continue;
                    }
                    std::string name = readLine("Nombre completo del pasajero: ");
                    if (name.empty()) {
                        std::cout << "Nombre vacio. Operacion cancelada.\n";
                        continue;
                    }
                    int cls = readInt("Clase (1=Primera, 2=Segunda, 3=Tercera): ");
                    if (cls < 1 || cls > 3) {
                        std::cout << "Clase invalida.\n";
                        continue;
                    }
                    bool success = flight.sellTicket(static_cast<ClassType>(cls - 1), name);
                    if (success) std::cout << "Boleto vendido correctamente.\n";
                    else std::cout << "No hay asientos disponibles en esa clase.\n";
                } else if (option == 2) {
                    flight.showSalesByClass();
                } else if (option == 3) {
                    flight.showTotalRevenue();
                } else if (option == 4) {
                    std::cout << (flight.isFull() ? "El vuelo esta lleno.\n" : "Aun hay asientos disponibles.\n");
                } else if (option == 0) {
                    std::cout << "Saliendo...\n";
                } else {
                    std::cout << "Opcion no valida.\n";
                }
            } catch (const std::exception& ex) {
                std::cerr << "Error: " << ex.what() << "\n";
            }
        }

    } catch (const std::exception& ex) {
        std::cerr << "Fallo al iniciar: " << ex.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
