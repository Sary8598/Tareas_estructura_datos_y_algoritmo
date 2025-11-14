#include "FlightClass.h"
#include <stdexcept>

FlightClass::FlightClass(const std::string& name, double price, int capacity, int startSeatNumber)
    : name_(name), ticketPrice_(price), capacity_(capacity), startSeatNumber_(startSeatNumber), passengerCount_(0) {
    if (capacity_ < 0) throw std::invalid_argument("Capacidad negativa para FlightClass");
    if (startSeatNumber_ <= 0) throw std::invalid_argument("startSeatNumber debe ser > 0");
    if (capacity_ > MAX_PASSENGERS) throw std::invalid_argument("Capacidad excede el maximo permitido");
    
    // Inicializar arreglo de pasajeros
    for (int i = 0; i < MAX_PASSENGERS; ++i) {
        passengers_[i] = nullptr;
    }
}

bool FlightClass::sellTicket(const std::string& passengerName) {
    if (passengerName.empty()) throw std::invalid_argument("Nombre del pasajero no puede estar vacio.");
    if (isFull()) return false;

    int seatNumber = startSeatNumber_ + passengerCount_;
    passengers_[passengerCount_] = std::make_unique<Passenger>(passengerName, seatNumber);
    passengerCount_++;
    return true;
}

int FlightClass::getSoldSeats() const noexcept {
    return passengerCount_;
}

int FlightClass::getCapacity() const noexcept {
    return capacity_;
}

double FlightClass::getTotalRevenue() const noexcept {
    return ticketPrice_ * getSoldSeats();
}

bool FlightClass::isFull() const noexcept {
    return passengerCount_ >= capacity_;
}

const std::string& FlightClass::getName() const noexcept {
    return name_;
}

double FlightClass::getPrice() const noexcept {
    return ticketPrice_;
}
