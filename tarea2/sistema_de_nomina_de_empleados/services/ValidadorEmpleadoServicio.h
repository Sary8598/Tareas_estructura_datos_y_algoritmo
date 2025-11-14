#ifndef VALIDADOR_EMPLEADO_SERVICIO_H
#define VALIDADOR_EMPLEADO_SERVICIO_H

#include <cstring>

// Servicio: Validador de datos de empleados
class ValidadorEmpleadoServicio {
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
    
    bool esSalarioValido(double salario) const {
        return salario > 0 && salario <= 10000000.0; // Limite razonable
    }
    
    bool esPorcentajeValido(double porcentaje) const {
        return porcentaje >= 0.0 && porcentaje <= 100.0;
    }
    
    bool esEmpleadoValido(const char* nombre, double salario, double porcentaje) const {
        return esNombreValido(nombre) && 
               esSalarioValido(salario) && 
               esPorcentajeValido(porcentaje);
    }
};

#endif