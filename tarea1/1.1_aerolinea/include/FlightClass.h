#pragma once
#include <memory>
#include <string>
#include "Passenger.h"

class FlightClass {
private:
    std::string name_;
    double ticketPrice_;
    int capacity_;
    int startSeatNumber_; // numero inicial del rango de asientos para esta clase
    static constexpr int MAX_PASSENGERS = 100;
    std::unique_ptr<Passenger> passengers_[MAX_PASSENGERS];
    int passengerCount_;

public:
    FlightClass(const std::string& name, double price, int capacity, int startSeatNumber);

    // Vende un boleto asignando el siguiente asiento disponible.
    // Retorna true si la venta fue exitosa, false si la clase esta completa.
    bool sellTicket(const std::string& passengerName);

    int getSoldSeats() const noexcept;
    int getCapacity() const noexcept;
    double getTotalRevenue() const noexcept;
    bool isFull() const noexcept;
    const std::string& getName() const noexcept;
    double getPrice() const noexcept;
};
