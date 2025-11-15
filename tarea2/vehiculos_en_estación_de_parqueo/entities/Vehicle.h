#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

enum class VehicleType {
    CAR,
    MOTORCYCLE
};

class Vehicle {
private:
    std::string licensePlate;
    VehicleType type;
    std::string entryTime;

public:
    Vehicle(const std::string& plate, VehicleType vehicleType, const std::string& time);
    
    std::string getLicensePlate() const;
    VehicleType getType() const;
    std::string getEntryTime() const;
    std::string getTypeString() const;
};

#endif