#ifndef PARKINGREPOSITORY_H
#define PARKINGREPOSITORY_H

#include "entities/Vehicle.h"

class ParkingRepository {
private:
    static const int MAX_VEHICLES = 100;
    Vehicle* vehicles[MAX_VEHICLES];
    int vehicleCount;
    int motorcycleCount;

public:
    ParkingRepository();
    ~ParkingRepository();
    
    bool addVehicle(Vehicle* vehicle);
    Vehicle** getAllVehicles();
    int getVehicleCount() const;
    int getMotorcycleCount() const;
    void clearAll();
};

#endif