#include "ParkingService.h"
#include <iostream>

ParkingService::ParkingService(ParkingRepository* repo) : repository(repo) {}

ParkingService::~ParkingService() {
    delete repository;
}

bool ParkingService::registerVehicle(const std::string& plate, VehicleType type, const std::string& time,
                                   std::chrono::microseconds& executionTime) {
    auto start = std::chrono::high_resolution_clock::now();
    
    Vehicle* newVehicle = new Vehicle(plate, type, time);
    bool result = repository->addVehicle(newVehicle);
    
    auto end = std::chrono::high_resolution_clock::now();
    executionTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    return result;
}

void ParkingService::displayAllVehicles(std::chrono::microseconds& executionTime) {
    auto start = std::chrono::high_resolution_clock::now();
    
    Vehicle** vehicles = repository->getAllVehicles();
    int count = repository->getVehicleCount();
    
    std::cout << "\n--- VEHICULOS REGISTRADOS ---\n";
    if (count == 0) {
        std::cout << "No hay vehiculos registrados.\n";
    } else {
        for (int i = 0; i < count; i++) {
            std::cout << "Vehiculo " << (i + 1) << ":\n";
            std::cout << "  Placa: " << vehicles[i]->getLicensePlate() << "\n";
            std::cout << "  Tipo: " << vehicles[i]->getTypeString() << "\n";
            std::cout << "  Hora de entrada: " << vehicles[i]->getEntryTime() << "\n";
            std::cout << "------------------------\n";
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    executionTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}

int ParkingService::countMotorcycles(std::chrono::microseconds& executionTime) {
    auto start = std::chrono::high_resolution_clock::now();
    
    int count = repository->getMotorcycleCount();
    
    auto end = std::chrono::high_resolution_clock::now();
    executionTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    return count;
}

int ParkingService::getTotalVehicles() const {
    return repository->getVehicleCount();
}