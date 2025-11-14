#include "ParkingRepository.h"
#include <iostream>

ParkingRepository::ParkingRepository() : vehicleCount(0), motorcycleCount(0) {
    for (int i = 0; i < MAX_VEHICLES; i++) {
        vehicles[i] = nullptr;
    }
}

ParkingRepository::~ParkingRepository() {
    clearAll();
}

bool ParkingRepository::addVehicle(Vehicle* vehicle) {
    if (vehicleCount >= MAX_VEHICLES) {
        return false;
    }
    
    vehicles[vehicleCount] = vehicle;
    vehicleCount++;
    
    if (vehicle->getType() == VehicleType::MOTORCYCLE) {
        motorcycleCount++;
    }
    
    return true;
}

Vehicle** ParkingRepository::getAllVehicles() {
    return vehicles;
}

int ParkingRepository::getVehicleCount() const {
    return vehicleCount;
}

int ParkingRepository::getMotorcycleCount() const {
    return motorcycleCount;
}

void ParkingRepository::clearAll() {
    for (int i = 0; i < vehicleCount; i++) {
        delete vehicles[i];
        vehicles[i] = nullptr;
    }
    vehicleCount = 0;
    motorcycleCount = 0;
}