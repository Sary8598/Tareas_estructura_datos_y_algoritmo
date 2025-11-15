#ifndef VALIDADOR_PACIENTE_SERVICIO_H
#define VALIDADOR_PACIENTE_SERVICIO_H

#include <cstring>

// Servicio: Validador de datos de pacientes
class ValidadorPacienteServicio {
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
    
    bool esSintomaValido(const char* sintoma) const {
        if (sintoma == nullptr || strlen(sintoma) == 0) {
            return false;
        }
        
        if (strlen(sintoma) > 200) {
            return false;
        }
        
        // Verificar que no sea solo espacios
        bool tieneCaracteres = false;
        for (int i = 0; sintoma[i] != '\0'; i++) {
            if (sintoma[i] != ' ' && sintoma[i] != '\t') {
                tieneCaracteres = true;
                break;
            }
        }
        
        return tieneCaracteres;
    }
    
    bool esPacienteValido(const char* nombre, const char* sintoma) const {
        return esNombreValido(nombre) && esSintomaValido(sintoma);
    }
};

#endif