#ifndef CONVERSION_CONTROLADOR_H
#define CONVERSION_CONTROLADOR_H

#include "../services/ConversionServicio.h"
#include <cstring>

class ConversionControlador {
private:
    ConversionServicio servicio;
    
public:
    bool procesarConversion(const char entrada[], char salida[]) {
        if (entrada == nullptr || salida == nullptr) {
            return false;
        }
        
        if (strlen(entrada) == 0) {
            salida[0] = '\0';
            return false;
        }
        
        return servicio.convertirInfixAPostfix(entrada, salida);
    }
};

#endif