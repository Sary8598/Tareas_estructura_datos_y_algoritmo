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
    int entryHour;

public:
    Vehicle(const std::string& plate, VehicleType vehicleType, int hour);
    
    std::string getLicensePlate() const;
    VehicleType getType() const;
    int getEntryHour() const;
    std::string getTypeString() const;
};

#endif