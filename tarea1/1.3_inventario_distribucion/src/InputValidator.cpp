#include "InputValidator.hpp"
#include <iostream>
#include <limits>

int InputValidator::solicitarEnteroPositivo(const char* mensaje, int maximo) {
    int valor;
    while (true) {
        std::cout << mensaje;
        if (std::cin >> valor && valor >= 0 && valor <= maximo)
            return valor;

        std::cout << "Valor invalido. Intente nuevamente.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
