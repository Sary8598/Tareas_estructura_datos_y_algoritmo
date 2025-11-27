#include "views/GraphView.h"
#include <iostream>

void GraphView::displayWelcome() {
    std::cout << "========================================\n";
    std::cout << "   SISTEMA DE DEPENDENCIAS DE MODULOS\n";
    std::cout << "========================================\n";
    std::cout << "  Grafo Dirigido - Orden Topologico\n";
    std::cout << "========================================\n";
}

void GraphView::displayGoodbye() {
    std::cout << "========================================\n";
    std::cout << "        SISTEMA FINALIZADO\n";
    std::cout << "========================================\n";
}
