#ifndef MEDIDOR_TIEMPO_SERVICIO_H
#define MEDIDOR_TIEMPO_SERVICIO_H

#include <ctime>

// Servicio: Medidor de tiempo de ejecucion
class MedidorTiempoServicio {
private:
    clock_t tiempoInicio;
    clock_t tiempoFin;
    double tiempoTotal;
    
public:
    MedidorTiempoServicio() : tiempoInicio(0), tiempoFin(0), tiempoTotal(0.0) {}
    
    void iniciar() {
        tiempoInicio = clock();
    }
    
    double detener() {
        tiempoFin = clock();
        double tiempoTranscurrido = static_cast<double>(tiempoFin - tiempoInicio) / CLOCKS_PER_SEC * 1000.0;
        tiempoTotal += tiempoTranscurrido;
        return tiempoTranscurrido;
    }
    
    double obtenerTiempoTotal() const {
        return tiempoTotal;
    }
    
    void reiniciarTotal() {
        tiempoTotal = 0.0;
    }
};

#endif