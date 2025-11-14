#include "Almacen.hpp"

void mostrarMenu() {
    std::cout << "\n========== SISTEMA DE INVENTARIO ==========\n"
              << "1. Registrar existencias\n"
              << "2. Detectar productos agotados\n"
              << "3. Mostrar almacen con menor stock\n"
              << "4. Emitir alertas de stock bajo\n"
              << "5. Configurar umbral minimo\n"
              << "6. Mostrar stock general\n"
              << "0. Salir\n"
              << "Seleccione una opcion: ";
}

int main() {
    Almacen sistema;
    int opcion = -1;

    while (true) {
        mostrarMenu();
        if (!(std::cin >> opcion)) {
            std::cerr << "Entrada invalida.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (opcion) {
            case 1: sistema.registrarExistencias(); break;
            case 2: sistema.detectarAgotados(); break;
            case 3: sistema.mostrarMenorStock(); break;
            case 4: sistema.emitirAlertas(); break;
            case 5: sistema.configurarUmbral(); break;
            case 6: sistema.mostrarStockGeneral(); break;
            case 0:
                std::cout << "\nSaliendo del sistema. ¡Hasta luego!\n";
                return 0;
            default:
                std::cout << "Opcion no valida.\n";
                break;
        }
    }
}
