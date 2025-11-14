#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <cstring>

// Entidad: Empleado - Representa un empleado de la empresa
class Empleado {
private:
    static const int MAX_NOMBRE = 100;
    char nombre[MAX_NOMBRE];
    double salarioBase;
    double porcentajeDescuento;
    
public:
    Empleado() : salarioBase(0.0), porcentajeDescuento(0.0) {
        nombre[0] = '\0';
    }
    
    Empleado(const char* nombreParam, double salario, double descuento) {
        establecerNombre(nombreParam);
        salarioBase = salario;
        porcentajeDescuento = descuento;
    }
    
    void establecerNombre(const char* nombreParam) {
        if (nombreParam != nullptr) {
            strncpy(nombre, nombreParam, MAX_NOMBRE - 1);
            nombre[MAX_NOMBRE - 1] = '\0';
        }
    }
    
    void establecerSalarioBase(double salario) {
        salarioBase = salario;
    }
    
    void establecerPorcentajeDescuento(double descuento) {
        porcentajeDescuento = descuento;
    }
    
    const char* obtenerNombre() const {
        return nombre;
    }
    
    double obtenerSalarioBase() const {
        return salarioBase;
    }
    
    double obtenerPorcentajeDescuento() const {
        return porcentajeDescuento;
    }
    
    bool esValido() const {
        return nombre[0] != '\0' && salarioBase > 0;
    }
};

#endif