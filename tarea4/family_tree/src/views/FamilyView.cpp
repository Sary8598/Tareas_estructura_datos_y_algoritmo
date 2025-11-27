#include "views/FamilyView.h"
#include <iostream>

void FamilyView::displayWelcome() {
    std::cout << "========================================\n";
    std::cout << "          ARBOL GENEALOGICO  \n";
    std::cout << "========================================\n";
    std::cout << "  Sistema de Relaciones Familiares\n";
    std::cout << "      (Hasta nivel de abuelos)\n";
    std::cout << "========================================\n";
}

void FamilyView::displayGoodbye() {
    std::cout << "========================================\n";
    std::cout << "          SISTEMA FINALIZADO\n";
    std::cout << "========================================\n";
}