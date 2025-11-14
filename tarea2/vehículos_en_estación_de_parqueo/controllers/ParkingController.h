#ifndef PARKINGCONTROLLER_H
#define PARKINGCONTROLLER_H

#include "services/ParkingService.h"
#include <chrono>

class ParkingController {
private:
    ParkingService* service;
    std::chrono::microseconds totalProgramTime;

public:
    ParkingController(ParkingService* serv);
    ~ParkingController();
    
    void processUserChoice(int choice);
    void displayMenu();
    void run();
    void displayExecutionTime(const std::string& functionName, 
                             const std::chrono::microseconds& time);
};

#endif