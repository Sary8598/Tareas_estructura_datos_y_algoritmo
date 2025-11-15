#ifndef VALIDADOR_CLIENTE_SERVICIO_H
#define VALIDADOR_CLIENTE_SERVICIO_H

#include <cstring>

// Servicio: Validador de datos de clientes
class ValidadorClienteServicio {
public:
    bool esNombreValido(const char* nombre) const {
        if (nombre == nullptr || strlen(nombre) == 0) {
            return false;
        }
        
        if (strlen(nombre) > 100) {
            return false;
        }
        
        // Verificar que no sea solo espacios
        bool tieneCaracteres = false;
        for (int i = 0; nombre[i] != '\0'; i++) {
            if (nombre[i] != ' ' && nombre[i] != '\t') {
                tieneCaracteres = true;
                break;
            }
        }
        
        return tieneCaracteres;
    }
    
    bool esAsuntoValido(const char* asunto) const {
        if (asunto == nullptr || strlen(asunto) == 0) {
            return false;
        }
        
        if (strlen(asunto) > 200) {
            return false;
        }
        
        // Verificar que no sea solo espacios
        bool tieneCaracteres = false;
        for (int i = 0; asunto[i] != '\0'; i++) {
            if (asunto[i] != ' ' && asunto[i] != '\t') {
                tieneCaracteres = true;
                break;
            }
        }
        
        return tieneCaracteres;
    }
    
    bool esClienteValido(const char* nombre, const char* asunto) const {
        return esNombreValido(nombre) && esAsuntoValido(asunto);
    }
};

#endif