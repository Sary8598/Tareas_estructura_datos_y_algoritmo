#include "Vehicle.h"

Vehicle::Vehicle(const std::string& plate, VehicleType vehicleType, int hour) 
    : licensePlate(plate), type(vehicleType), entryHour(hour) {}

std::string Vehicle::getLicensePlate() const {
    return licensePlate;
}

VehicleType Vehicle::getType() const {
    return type;
}

int Vehicle::getEntryHour() const {
    return entryHour;
}

std::string Vehicle::getTypeString() const {
    return (type == VehicleType::CAR) ? "Carro" : "Motocicleta";
}