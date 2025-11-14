#ifndef MALETA_H
#define MALETA_H

#include <cstring>

// Entidad: Maleta - Representa una maleta en la bodega
class Maleta {
private:
    static const int MAX_ID = 20;
    char identificador[MAX_ID];
    
public:
    Maleta() {
        identificador[0] = '\0';
    }
    
    Maleta(const char* id) {
        establecerIdentificador(id);
    }
    
    void establecerIdentificador(const char* id) {
        if (id != nullptr) {
            strncpy(identificador, id, MAX_ID - 1);
            identificador[MAX_ID - 1] = '\0';
        }
    }
    
    const char* obtenerIdentificador() const {
        return identificador;
    }
    
    bool esIgual(const char* id) const {
        return strcmp(identificador, id) == 0;
    }
    
    bool esVacia() const {
        return identificador[0] == '\0';
    }
};

#endif