#include "controllers/RecommendationController.h"
#include "services/RecommendationService.h"
#include "repositories/GraphRepository.h"
#include "views/RecommendationView.h"
#include <iostream>

int main() {
    RecommendationView::displayWelcome();
    
    try {
        GraphRepository* repository = new GraphRepository();
        RecommendationService* service = new RecommendationService(repository);
        RecommendationController* controller = new RecommendationController(service);
        
        controller->run();
        
        delete controller;
        
    } catch (const std::exception& e) {
        std::cout << "Error critico: " << e.what() << "\n";
        return 1;
    }
    
    RecommendationView::displayGoodbye();
    return 0;
}
