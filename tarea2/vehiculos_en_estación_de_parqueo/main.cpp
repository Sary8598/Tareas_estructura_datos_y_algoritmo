#include "controllers/ParkingController.h"
#include "services/ParkingService.h"
#include "repositories/ParkingRepository.h"
#include "views/ParkingView.h"

int main() {
    ParkingView::displayWelcomeMessage();
    
    ParkingRepository* repository = new ParkingRepository();
    ParkingService* service = new ParkingService(repository);
    ParkingController* controller = new ParkingController(service);
    
    controller->run();
    
    ParkingView::displayGoodbyeMessage();
    
    delete controller;
    
    return 0;
}