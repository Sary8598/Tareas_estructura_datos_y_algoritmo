#include "controllers/GraphController.h"
#include <iostream>
#include <limits>

GraphController::GraphController(DependencyService* graphService) 
    : service(graphService) {}

GraphController::~GraphController() {
    delete service;
}

void GraphController::displayMenu() const {
    std::cout << "\n=== SISTEMA DE DEPENDENCIAS DE MODULOS ===\n";
    std::cout << "1. Agregar modulo\n";
    std::cout << "2. Agregar dependencia (A -> B)\n";
    std::cout << "3. Mostrar orden de carga (DFS)\n";
    std::cout << "4. Detectar ciclos de dependencia\n";
    std::cout << "5. Mostrar todos los modulos\n";
    std::cout << "6. Mostrar informacion de modulo\n";
    std::cout << "7. Mostrar ayuda\n";
    std::cout << "8. Mostrar ejemplo\n";
    std::cout << "9. Salir\n";
    std::cout << "Seleccione una opcion (1-9): ";
}

void GraphController::processChoice(int choice) {
    switch (choice) {
        case 1:
            addModule();
            break;
        case 2:
            addDependency();
            break;
        case 3:
            showLoadOrder();
            break;
        case 4:
            detectCycles();
            break;
        case 5:
            showAllModules();
            break;
        case 6:
            showModuleInfo();
            break;
        case 7:
            showHelp();
            break;
        case 8:
            showExample();
            break;
        case 9:
            std::cout << "Saliendo del sistema de dependencias...\n";
            break;
        default:
            std::cout << "Opcion invalida. Por favor seleccione 1-9.\n";
    }
}

void GraphController::addModule() {
    std::string name;
    std::cout << "Ingrese el nombre del modulo: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, name);
    
    if (name.empty()) {
        std::cout << "Error: El nombre no puede estar vacio\n";
        return;
    }
    
    if (service->addModule(name)) {
        std::cout << "Modulo agregado exitosamente: " << name << "\n";
    } else {
        std::cout << "Error: No se pudo agregar el modulo (nombre duplicado o limite alcanzado)\n";
    }
}

void GraphController::addDependency() {
    std::string fromModule, toModule;
    
    std::cout << "Ingrese el modulo origen (A en A -> B): ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, fromModule);
    
    std::cout << "Ingrese el modulo destino (B en A -> B): ";
    std::getline(std::cin, toModule);
    
    if (fromModule.empty() || toModule.empty()) {
        std::cout << "Error: Los nombres de modulos no pueden estar vacios\n";
        return;
    }
    
    if (service->addDependency(fromModule, toModule)) {
        std::cout << "Dependencia agregada: " << fromModule << " -> " << toModule << "\n";
    } else {
        std::cout << "Error: No se pudo agregar la dependencia\n";
        std::cout << "(Modulos no existen o dependencia circular directa)\n";
    }
}

void GraphController::showLoadOrder() {
    std::vector<std::string> loadOrder = service->getLoadOrder();
    
    std::cout << "\n=== ORDEN DE CARGA (DFS) ===\n";
    if (loadOrder.empty()) {
        std::cout << "No hay modulos en el sistema\n";
    } else if (service->hasCycles()) {
        std::cout << "No se puede calcular el orden de carga debido a ciclos\n";
    } else {
        std::cout << "Orden de carga (de primero a ultimo):\n";
        for (size_t i = 0; i < loadOrder.size(); i++) {
            std::cout << i + 1 << ". " << loadOrder[i] << "\n";
        }
    }
}

void GraphController::detectCycles() {
    std::vector<std::string> cycleInfo = service->detectCycles();
    
    std::cout << "\n=== DETECCION DE CICLOS ===\n";
    for (const std::string& info : cycleInfo) {
        std::cout << info << "\n";
    }
}

void GraphController::showAllModules() {
    std::vector<std::string> modulesInfo = service->getAllModulesInfo();
    
    std::cout << "\n=== TODOS LOS MODULOS ===\n";
    for (const std::string& info : modulesInfo) {
        std::cout << info << "\n";
    }
}

void GraphController::showModuleInfo() {
    std::string name;
    std::cout << "Ingrese el nombre del modulo: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, name);
    
    if (name.empty()) {
        std::cout << "Error: El nombre no puede estar vacio\n";
        return;
    }
    
    std::string info = service->getModuleInfo(name);
    std::cout << "\n" << info << "\n";
}

void GraphController::showHelp() const {
    std::cout << "\n=== AYUDA - SISTEMA DE DEPENDENCIAS ===\n";
    std::cout << "Este sistema gestiona dependencias entre modulos usando un grafo dirigido.\n\n";
    std::cout << "CONCEPTOS:\n";
    std::cout << "- Modulo: Un componente del sistema (clase, funcion, paquete)\n";
    std::cout << "- Dependencia A -> B: A depende de B (B debe cargarse antes que A)\n";
    std::cout << "- Orden de carga: Orden topologico usando DFS\n";
    std::cout << "- Ciclo: Cuando A depende de B y B depende de A (directa o indirectamente)\n\n";
    std::cout << "FUNCIONALIDADES:\n";
    std::cout << "1. Agregar modulo: Anade un nuevo modulo al sistema\n";
    std::cout << "2. Agregar dependencia: Establece que A depende de B\n";
    std::cout << "3. Orden de carga: Muestra el orden correcto para cargar los modulos\n";
    std::cout << "4. Detectar ciclos: Verifica si hay dependencias circulares\n";
    std::cout << "5. Mostrar modulos: Lista todos los modulos y sus relaciones\n";
    std::cout << "6. Info modulo: Muestra informacion detallada de un modulo\n";
}

void GraphController::showExample() const {
    std::cout << "\n=== EJEMPLO DE USO ===\n";
    std::cout << "Modulos: A, B, C, D, E\n";
    std::cout << "Dependencias:\n";
    std::cout << "  A -> B (A depende de B)\n";
    std::cout << "  A -> C\n";
    std::cout << "  B -> D\n";
    std::cout << "  C -> D\n";
    std::cout << "  D -> E\n";
    std::cout << "Orden de carga esperado: E, D, B, C, A\n";
    std::cout << "O: E, D, C, B, A (ambos son validos)\n\n";
    std::cout << "Ejemplo con ciclo:\n";
    std::cout << "  A -> B\n";
    std::cout << "  B -> C\n";
    std::cout << "  C -> A  (CICLO!)\n";
}

int GraphController::getValidatedInput() const {
    int choice;
    std::cin >> choice;
    
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }
    
    return choice;
}

void GraphController::run() {
    int choice = 0;
    
    std::cout << "Sistema de Gestion de Dependencias Iniciado\n";
    
    do {
        displayMenu();
        choice = getValidatedInput();
        
        if (choice == -1) {
            std::cout << "Entrada invalida. Por favor ingrese un numero.\n";
            continue;
        }
        
        processChoice(choice);
        
    } while (choice != 9);
}
