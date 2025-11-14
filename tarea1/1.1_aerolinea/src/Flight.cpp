#include "Flight.h"
#include <iostream>
#include <stdexcept>
#include <iomanip>

Flight::Flight(int airplaneCapacity, double priceFirst, double priceSecond, double priceThird)
    : airplane_(airplaneCapacity),
      priceFirst_(priceFirst),
      priceSecond_(priceSecond),
      priceThird_(priceThird) {
    createClasses();
}

void Flight::createClasses() {
    // Crear FlightClass para cada clase con su capacidad y rango de asientos
    int startFirst = airplane_.getStartSeatFor(ClassType::First);
    int capFirst = airplane_.getCapacityFor(ClassType::First);
    classes_[ClassType::First] = std::make_unique<FlightClass>("Primera", priceFirst_, capFirst, startFirst);

    int startSecond = airplane_.getStartSeatFor(ClassType::Second);
    int capSecond = airplane_.getCapacityFor(ClassType::Second);
    classes_[ClassType::Second] = std::make_unique<FlightClass>("Segunda", priceSecond_, capSecond, startSecond);

    int startThird = airplane_.getStartSeatFor(ClassType::Third);
    int capThird = airplane_.getCapacityFor(ClassType::Third);
    classes_[ClassType::Third] = std::make_unique<FlightClass>("Tercera", priceThird_, capThird, startThird);
}

bool Flight::sellTicket(ClassType type, const std::string& passengerName) {
    if (passengerName.empty()) {
        throw std::invalid_argument("Nombre del pasajero no puede estar vacio.");
    }
    auto it = classes_.find(type);
    if (it == classes_.end()) {
        throw std::invalid_argument("Tipo de clase invalido.");
    }

    FlightClass* fc = it->second.get();
    return fc->sellTicket(passengerName);
}

int Flight::getSoldSeats(ClassType type) const {
    auto it = classes_.find(type);
    if (it == classes_.end()) return 0;
    return it->second->getSoldSeats();
}

int Flight::getCapacity(ClassType type) const {
    return airplane_.getCapacityFor(type);
}

double Flight::getRevenue(ClassType type) const {
    auto it = classes_.find(type);
    if (it == classes_.end()) return 0.0;
    return it->second->getTotalRevenue();
}

double Flight::getTotalRevenue() const {
    double total = 0.0;
    for (const auto& p : classes_) {
        total += p.second->getTotalRevenue();
    }
    return total;
}

bool Flight::isFull() const {
    int totalSold = 0;
    for (const auto& p : classes_) totalSold += p.second->getSoldSeats();
    return totalSold >= airplane_.getTotalCapacity();
}

void Flight::showSalesByClass() const {
    std::cout << "\n--- Asientos vendidos por clase ---\n";
    for (const auto& p : classes_) {
        const FlightClass* fc = p.second.get();
        std::cout << fc->getName()
                  << " : " << fc->getSoldSeats()
                  << " / " << fc->getCapacity()
                  << " (precio: $" << std::fixed << std::setprecision(2) << fc->getPrice() << ")\n";
    }
}

void Flight::showTotalRevenue() const {
    std::cout << "\n--- Ingreso estimado ---\n";
    for (const auto& p : classes_) {
        const FlightClass* fc = p.second.get();
        std::cout << fc->getName()
                  << " : $" << std::fixed << std::setprecision(2) << fc->getTotalRevenue() << "\n";
    }
    std::cout << "Total: $" << std::fixed << std::setprecision(2) << getTotalRevenue() << "\n";
}
