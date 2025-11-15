#ifndef PACIENTE_H
#define PACIENTE_H

#include <cstring>

// Entidad: Paciente - Representa un paciente en la sala de espera
class Paciente {
private:
    static const int MAX_NOMBRE = 100;
    static const int MAX_SINTOMA = 200;
    char nombre[MAX_NOMBRE];
    char sintoma[MAX_SINTOMA];
    int numeroFicha;
    
public:
    Paciente() : numeroFicha(0) {
        nombre[0] = '\0';
        sintoma[0] = '\0';
    }
    
    Paciente(const char* nombreParam, const char* sintomaParam, int ficha) {
        establecerNombre(nombreParam);
        establecerSintoma(sintomaParam);
        numeroFicha = ficha;
    }
    
    void establecerNombre(const char* nombreParam) {
        if (nombreParam != nullptr) {
            strncpy(nombre, nombreParam, MAX_NOMBRE - 1);
            nombre[MAX_NOMBRE - 1] = '\0';
        }
    }
    
    void establecerSintoma(const char* sintomaParam) {
        if (sintomaParam != nullptr) {
            strncpy(sintoma, sintomaParam, MAX_SINTOMA - 1);
            sintoma[MAX_SINTOMA - 1] = '\0';
        }
    }
    
    void establecerNumeroFicha(int ficha) {
        numeroFicha = ficha;
    }
    
    const char* obtenerNombre() const {
        return nombre;
    }
    
    const char* obtenerSintoma() const {
        return sintoma;
    }
    
    int obtenerNumeroFicha() const {
        return numeroFicha;
    }
    
    bool esValido() const {
        return nombre[0] != '\0' && sintoma[0] != '\0';
    }
};

#endif