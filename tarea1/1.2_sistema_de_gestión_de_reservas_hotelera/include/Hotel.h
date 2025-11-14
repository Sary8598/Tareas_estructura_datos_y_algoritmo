#pragma once
#include "Habitacion.h"

class Hotel {
private:
    static constexpr int MAX_HABITACIONES = 50;
    Habitacion habitaciones[MAX_HABITACIONES];
    int totalHabitaciones;

public:
    Hotel();
    
    void agregarHabitacion(int numero, TipoHabitacion tipo, double precio);
    bool reservarHabitacion(int numero, const Cliente& cliente);
    void liberarHabitacion(int numero);
    
    void mostrarDisponiblesPorTipo(TipoHabitacion tipo) const;
    Habitacion* obtenerMasCaraDisponible();
    double calcularIngresoEstimado() const;
    double calcularOcupacionTotal() const;
    
    void mostrarTodasHabitaciones() const;
    void mostrarEstadisticas() const;
};