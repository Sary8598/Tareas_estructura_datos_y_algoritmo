#include "Passenger.h"
#include <stdexcept>

Passenger::Passenger(const std::string& fullName, int seatNumber)
    : fullName_(fullName), seatNumber_(seatNumber) {
    if (fullName.empty()) {
        throw std::invalid_argument("Nombre del pasajero no puede estar vacio.");
    }
    if (seatNumber <= 0) {
        throw std::invalid_argument("Numero de asiento invalido.");
    }
}

const std::string& Passenger::getFullName() const noexcept {
    return fullName_;
}

int Passenger::getSeatNumber() const noexcept {
    return seatNumber_;
}
