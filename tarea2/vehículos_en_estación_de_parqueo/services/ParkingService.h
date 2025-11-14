#ifndef PARKINGSERVICE_H
#define PARKINGSERVICE_H

#include "repositories/ParkingRepository.h"
#include <chrono>

class ParkingService {
private:
    ParkingRepository* repository;

public:
    ParkingService(ParkingRepository* repo);
    ~ParkingService();
    
    bool registerVehicle(const std::string& plate, VehicleType type, int hour, 
                        std::chrono::microseconds& executionTime);
    void displayAllVehicles(std::chrono::microseconds& executionTime);
    int countMotorcycles(std::chrono::microseconds& executionTime);
    int getTotalVehicles() const;
};

#endif