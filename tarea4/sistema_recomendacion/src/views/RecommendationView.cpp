#include "views/RecommendationView.h"
#include <iostream>

void RecommendationView::displayWelcome() {
    std::cout << "========================================\n";
    std::cout << "    SISTEMA DE RECOMENDACIONES\n";
    std::cout << "========================================\n";
    std::cout << "  Grafo de Productos - BFS Depth 2\n";
    std::cout << "========================================\n";
}

void RecommendationView::displayGoodbye() {
    std::cout << "========================================\n";
    std::cout << "        SISTEMA FINALIZADO\n";
    std::cout << "========================================\n";
}
