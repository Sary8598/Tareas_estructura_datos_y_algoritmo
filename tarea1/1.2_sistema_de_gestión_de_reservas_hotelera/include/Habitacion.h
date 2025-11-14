#pragma once
#include <string>
#include "Cliente.h"

enum class TipoHabitacion {
    SENCILLA = 0,
    DOBLE = 1,
    SUITE = 2
};

class Habitacion {
private:
    int numero;
    TipoHabitacion tipo;
    double precioPorNoche;
    bool ocupada;
    Cliente cliente;

public:
    Habitacion();
    Habitacion(int numero, TipoHabitacion tipo, double precio);
    
    int getNumero() const;
    TipoHabitacion getTipo() const;
    double getPrecio() const;
    bool estaOcupada() const;
    const Cliente& getCliente() const;
    
    void reservar(const Cliente& cliente);
    void liberar();
    std::string getTipoString() const;
    void mostrarInfo() const;
};