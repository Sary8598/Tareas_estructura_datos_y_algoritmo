#ifndef CLIENTE_H
#define CLIENTE_H

#include <cstring>

// Entidad: Cliente - Representa un cliente en la fila del banco
class Cliente {
private:
    static const int MAX_NOMBRE = 100;
    static const int MAX_ASUNTO = 200;
    char nombre[MAX_NOMBRE];
    char asunto[MAX_ASUNTO];
    int numeroTurno;
    
public:
    Cliente() : numeroTurno(0) {
        nombre[0] = '\0';
        asunto[0] = '\0';
    }
    
    Cliente(const char* nombreParam, const char* asuntoParam, int turno) {
        establecerNombre(nombreParam);
        establecerAsunto(asuntoParam);
        numeroTurno = turno;
    }
    
    void establecerNombre(const char* nombreParam) {
        if (nombreParam != nullptr) {
            strncpy(nombre, nombreParam, MAX_NOMBRE - 1);
            nombre[MAX_NOMBRE - 1] = '\0';
        }
    }
    
    void establecerAsunto(const char* asuntoParam) {
        if (asuntoParam != nullptr) {
            strncpy(asunto, asuntoParam, MAX_ASUNTO - 1);
            asunto[MAX_ASUNTO - 1] = '\0';
        }
    }
    
    void establecerNumeroTurno(int turno) {
        numeroTurno = turno;
    }
    
    const char* obtenerNombre() const {
        return nombre;
    }
    
    const char* obtenerAsunto() const {
        return asunto;
    }
    
    int obtenerNumeroTurno() const {
        return numeroTurno;
    }
    
    bool esValido() const {
        return nombre[0] != '\0' && asunto[0] != '\0';
    }
};

#endif