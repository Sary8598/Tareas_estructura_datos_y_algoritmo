#pragma once
#include <memory>
#include <map>
#include <string>
#include "Airplane.h"
#include "FlightClass.h"
#include "ClassType.h"

class Flight {
private:
    Airplane airplane_;
    std::map<ClassType, std::unique_ptr<FlightClass>> classes_;

    // Precios por clase (puedes ajustar)
    double priceFirst_;
    double priceSecond_;
    double priceThird_;

    void createClasses();

public:
    explicit Flight(int airplaneCapacity,
                    double priceFirst = 500.0,
                    double priceSecond = 300.0,
                    double priceThird = 150.0);

    // Vende boleto; lanza excepcion si nombre invalido o tipo invalido.
    // Retorna true si la venta fue exitosa; false si la clase esta llena.
    bool sellTicket(ClassType type, const std::string& passengerName);

    int getSoldSeats(ClassType type) const;
    int getCapacity(ClassType type) const;
    double getRevenue(ClassType type) const;
    double getTotalRevenue() const;
    bool isFull() const;
    void showSalesByClass() const;
    void showTotalRevenue() const;
};
