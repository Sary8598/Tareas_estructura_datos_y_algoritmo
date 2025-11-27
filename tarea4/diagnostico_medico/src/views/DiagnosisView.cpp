#include "views/DiagnosisView.h"
#include <iostream>

void DiagnosisView::displayWelcome() {
    std::cout << "========================================\n";
    std::cout << "     SISTEMA DE DIAGNOSTICO MEDICO\n";
    std::cout << "========================================\n";
    std::cout << "   Arbol de Decision Binario Interactivo\n";
    std::cout << "========================================\n";
    std::cout << "ADVERTENCIA: Sistema educativo solamente\n";
    std::cout << "    Consulte siempre con profesionales de salud\n";
    std::cout << "========================================\n";
}

void DiagnosisView::displayGoodbye() {
    std::cout << "========================================\n";
    std::cout << "        SISTEMA FINALIZADO\n";
    std::cout << "    Cuide su salud y bienestar!\n";
    std::cout << "========================================\n";
}