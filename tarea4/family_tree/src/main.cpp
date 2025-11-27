#include "controllers/FamilyController.h"
#include "services/FamilyTreeService.h"
#include "repositories/FamilyRepository.h"
#include "views/FamilyView.h"
#include <iostream>

int main() {
    FamilyView::displayWelcome();
    
    try {
        FamilyRepository* repository = new FamilyRepository();
        FamilyTreeService* service = new FamilyTreeService(repository);
        FamilyController* controller = new FamilyController(service);
        
        controller->run();
        
        delete controller;
        
    } catch (const std::exception& e) {
        std::cout << "Error critico: " << e.what() << "\n";
        return 1;
    }
    
    FamilyView::displayGoodbye();
    return 0;
}