#pragma once
#include <string>

class Passenger {
private:
    std::string fullName_;
    int seatNumber_;

public:
    Passenger(const std::string& fullName, int seatNumber);
    const std::string& getFullName() const noexcept;
    int getSeatNumber() const noexcept;
};
