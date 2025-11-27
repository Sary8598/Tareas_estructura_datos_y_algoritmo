#include "controllers/GraphController.h"
#include "services/DependencyService.h"
#include "repositories/GraphRepository.h"
#include "views/GraphView.h"
#include <iostream>

int main() {
    GraphView::displayWelcome();
    
    try {
        GraphRepository* repository = new GraphRepository();
        DependencyService* service = new DependencyService(repository);
        GraphController* controller = new GraphController(service);
        
        controller->run();
        
        delete controller;
        
    } catch (const std::exception& e) {
        std::cout << "Error critico: " << e.what() << "\n";
        return 1;
    }
    
    GraphView::displayGoodbye();
    return 0;
}
