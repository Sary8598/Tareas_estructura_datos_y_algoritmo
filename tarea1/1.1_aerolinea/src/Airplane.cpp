#include "Airplane.h"
#include <stdexcept>
#include <cmath>

Airplane::Airplane(int totalCapacity)
    : totalCapacity_(totalCapacity) {
    if (totalCapacity_ <= 0) throw std::invalid_argument("La capacidad total debe ser > 0");

    // Porcentajes fijos
    const double pFirst = 0.15;
    const double pSecond = 0.25;
    const double pThird = 0.60;

    // Calculo inicial por piso (se usa round para mejor aproximacion), luego ajuste por diferencia
    int capFirst = static_cast<int>(std::round(totalCapacity_ * pFirst));
    int capSecond = static_cast<int>(std::round(totalCapacity_ * pSecond));
    int capThird = totalCapacity_ - (capFirst + capSecond);

    // En casos raros de redondeo negativo o 0, asegurar al menos 0 y ajustar
    if (capThird < 0) capThird = 0;

    classCapacities_[ClassType::First] = capFirst;
    classCapacities_[ClassType::Second] = capSecond;
    classCapacities_[ClassType::Third] = capThird;
}

int Airplane::getTotalCapacity() const noexcept {
    return totalCapacity_;
}

int Airplane::getCapacityFor(ClassType type) const noexcept {
    auto it = classCapacities_.find(type);
    if (it == classCapacities_.end()) return 0;
    return it->second;
}

int Airplane::getStartSeatFor(ClassType type) const noexcept {
    // Primera empieza en 1, la segunda en 1 + capPrimera, tercera en 1 + capPrimera + capSegunda
    int start = 1;
    if (type == ClassType::First) return start;

    start += getCapacityFor(ClassType::First);
    if (type == ClassType::Second) return start;

    start += getCapacityFor(ClassType::Second);
    // Third
    return start;
}
