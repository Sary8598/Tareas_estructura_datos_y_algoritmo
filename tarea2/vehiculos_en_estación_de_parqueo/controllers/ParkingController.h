#ifndef PARKINGCONTROLLER_H
#define PARKINGCONTROLLER_H

#include "services/ParkingService.h"
#include <chrono>
#include <vector>
#include <string>

struct ExecutionRecord {
    std::string operation;
    std::chrono::microseconds time;
};

class ParkingController {
private:
    ParkingService* service;
    std::chrono::microseconds totalProgramTime;
    std::vector<ExecutionRecord> executionHistory;

public:
    ParkingController(ParkingService* serv);
    ~ParkingController();
    
    void processUserChoice(int choice);
    void displayMenu();
    void run();
    void displayExecutionTime(const std::string& functionName, 
                             const std::chrono::microseconds& time);
    void displayAllExecutionTimes();
};

#endif