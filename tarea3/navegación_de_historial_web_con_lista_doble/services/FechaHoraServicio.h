#ifndef FECHA_HORA_SERVICIO_H
#define FECHA_HORA_SERVICIO_H

#include <ctime>
#include <cstdio>

// Servicio: Gestor de fecha y hora
class FechaHoraServicio {
public:
    void obtenerFechaHoraActual(char* buffer, int tamanio) const {
        time_t ahora = time(nullptr);
        struct tm* tiempoLocal = localtime(&ahora);
        
        strftime(buffer, tamanio, "%Y-%m-%d %H:%M:%S", tiempoLocal);
    }
    
    void formatearFechaHora(char* destino, int tamanio) const {
        obtenerFechaHoraActual(destino, tamanio);
    }
};

#endif