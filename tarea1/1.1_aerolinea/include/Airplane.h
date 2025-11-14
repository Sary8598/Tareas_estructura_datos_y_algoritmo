#pragma once
#include <map>
#include "ClassType.h"

class Airplane {
private:
    int totalCapacity_;
    // Distribucion por clase (capacidad absoluta)
    std::map<ClassType, int> classCapacities_;
public:
    // totalCapacity: capacidad total del avion; los porcentajes son fijos:
    // 15% Primera, 25% Segunda, 60% Tercera (se ajusta por redondeo).
    explicit Airplane(int totalCapacity);

    int getTotalCapacity() const noexcept;
    int getCapacityFor(ClassType type) const noexcept;
    // Devuelve el numero de asiento de inicio (1-indexed) para cada clase, para numerar asientos sin solapamiento.
    int getStartSeatFor(ClassType type) const noexcept;
};
