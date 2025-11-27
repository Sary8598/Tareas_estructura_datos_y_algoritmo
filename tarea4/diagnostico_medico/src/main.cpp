#include "controllers/DiagnosisController.h"
#include "services/DiagnosisService.h"
#include "repositories/DecisionTreeRepository.h"
#include "views/DiagnosisView.h"
#include <iostream>

int main() {
    DiagnosisView::displayWelcome();
    
    try {
        DecisionTreeRepository* repository = new DecisionTreeRepository();
        DiagnosisService* service = new DiagnosisService(repository);
        DiagnosisController* controller = new DiagnosisController(service);
        
        controller->run();
        
        delete controller;
        
    } catch (const std::exception& e) {
        std::cout << "Error critico: " << e.what() << "\n";
        return 1;
    }
    
    DiagnosisView::displayGoodbye();
    return 0;
}
