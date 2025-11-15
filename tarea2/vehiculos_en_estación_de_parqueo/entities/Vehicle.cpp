#include "Vehicle.h"

Vehicle::Vehicle(const std::string& plate, VehicleType vehicleType, const std::string& time) 
    : licensePlate(plate), type(vehicleType), entryTime(time) {}

std::string Vehicle::getLicensePlate() const {
    return licensePlate;
}

VehicleType Vehicle::getType() const {
    return type;
}

std::string Vehicle::getEntryTime() const {
    return entryTime;
}

std::string Vehicle::getTypeString() const {
    return (type == VehicleType::CAR) ? "Carro" : "Motocicleta";
}