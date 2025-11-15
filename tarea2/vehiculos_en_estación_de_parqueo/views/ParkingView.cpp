#include "ParkingView.h"
#include <iostream>

void ParkingView::displayWelcomeMessage() {
    std::cout << "================================\n";
    std::cout << "  SISTEMA DE ESTACIONAMIENTO\n";
    std::cout << "================================\n";
}

void ParkingView::displayGoodbyeMessage() {
    std::cout << "================================\n";
    std::cout << "  Gracias por usar el sistema\n";
    std::cout << "================================\n";
}