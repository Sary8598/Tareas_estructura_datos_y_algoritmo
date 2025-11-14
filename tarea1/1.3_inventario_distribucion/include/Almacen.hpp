#ifndef ALMACEN_HPP
#define ALMACEN_HPP

#include <iostream>
#include <array>
#include <numeric> // std::accumulate
#include <limits>  // std::numeric_limits

class Almacen {
private:
    static constexpr int NUM_ALMACENES = 6;
    static constexpr int NUM_PRODUCTOS = 15;

    std::array<std::array<int, NUM_PRODUCTOS>, NUM_ALMACENES> stock{};
    int umbralMinimo;

public:
    Almacen();

    void registrarExistencias();
    void detectarAgotados() const;
    void mostrarMenorStock() const;
    void emitirAlertas() const;
    void configurarUmbral();
    void mostrarStockGeneral() const;
};

#endif
