#include "ParkingController.h"
#include <iostream>
#include <limits>

ParkingController::ParkingController(ParkingService* serv) 
    : service(serv), totalProgramTime(std::chrono::microseconds(0)) {}

ParkingController::~ParkingController() {
    delete service;
}

void ParkingController::processUserChoice(int choice) {
    std::chrono::microseconds executionTime;
    
    switch (choice) {
        case 1: {
            std::string plate, time;
            int typeChoice;
            
            std::cout << "Ingrese numero de placa: ";
            std::cin >> plate;
            
            std::cout << "Tipo de vehiculo (1 - Carro, 2 - Moto): ";
            std::cin >> typeChoice;
            
            std::cout << "Hora de entrada (HH:MM): ";
            std::cin >> time;
            
            VehicleType type = (typeChoice == 2) ? VehicleType::MOTORCYCLE : VehicleType::CAR;
            
            if (service->registerVehicle(plate, type, time, executionTime)) {
                std::cout << "Vehiculo registrado exitosamente.\n";
            } else {
                std::cout << "Error: No se pudo registrar el vehiculo. Estacionamiento lleno.\n";
            }
            
            displayExecutionTime("Registrar Vehiculo", executionTime);
            totalProgramTime += executionTime;
            break;
        }
            
        case 2:
            service->displayAllVehicles(executionTime);
            displayExecutionTime("Mostrar Vehiculos", executionTime);
            totalProgramTime += executionTime;
            break;
            
        case 3: {
            int motorcycleCount = service->countMotorcycles(executionTime);
            std::cout << "\nTotal de motocicletas registradas: " << motorcycleCount << "\n";
            displayExecutionTime("Contar Motocicletas", executionTime);
            totalProgramTime += executionTime;
            break;
        }
            
        case 4:
            displayAllExecutionTimes();
            break;
            
        case 5:
            std::cout << "Saliendo del sistema...\n";
            break;
            
        default:
            std::cout << "Opcion invalida. Intente nuevamente.\n";
    }
}

void ParkingController::displayMenu() {
    std::cout << "\n=== SISTEMA DE ESTACIONAMIENTO ===\n";
    std::cout << "1. Registrar vehiculo\n";
    std::cout << "2. Mostrar todos los vehiculos\n";
    std::cout << "3. Contar motocicletas\n";
    std::cout << "4. Listar todos los tiempos de ejecucion\n";
    std::cout << "5. Salir\n";
    std::cout << "Seleccione una opcion: ";
}

void ParkingController::run() {
    auto programStart = std::chrono::high_resolution_clock::now();
    int choice = 0;
    
    do {
        displayMenu();
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada invalida. Por favor ingrese un numero.\n";
            continue;
        }
        
        processUserChoice(choice);
        
    } while (choice != 5);
    
    auto programEnd = std::chrono::high_resolution_clock::now();
    auto totalTime = std::chrono::duration_cast<std::chrono::microseconds>(
        programEnd - programStart);
    
    std::cout << "\nTiempo real total del programa: " << totalTime.count() 
              << " microsegundos\n";
}

void ParkingController::displayExecutionTime(const std::string& functionName, 
                                           const std::chrono::microseconds& time) {
    std::cout << "Tiempo de ejecucion de '" << functionName << "': " 
              << time.count() << " microsegundos\n";
    executionHistory.push_back({functionName, time});
}

void ParkingController::displayAllExecutionTimes() {
    std::cout << "\n=== HISTORIAL DE TIEMPOS DE EJECUCION ===\n";
    for (const auto& record : executionHistory) {
        std::cout << record.operation << ": " << record.time.count() << " microsegundos\n";
    }
    std::cout << "\nTiempo total acumulado: " << totalProgramTime.count() << " microsegundos\n";
}