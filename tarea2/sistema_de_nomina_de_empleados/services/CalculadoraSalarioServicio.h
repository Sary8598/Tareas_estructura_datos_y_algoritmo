#ifndef CALCULADORA_SALARIO_SERVICIO_H
#define CALCULADORA_SALARIO_SERVICIO_H

#include "../domain/Empleado.h"

// Servicio: Calculadora de salario neto
class CalculadoraSalarioServicio {
public:
    // Calcular salario neto (requisito 2)
    double calcularSalarioNeto(const Empleado& empleado) const {
        double salarioBase = empleado.obtenerSalarioBase();
        double porcentajeDescuento = empleado.obtenerPorcentajeDescuento();
        
        double montoDescuento = salarioBase * (porcentajeDescuento / 100.0);
        double salarioNeto = salarioBase - montoDescuento;
        
        return salarioNeto;
    }
    
    double calcularMontoDescuento(const Empleado& empleado) const {
        double salarioBase = empleado.obtenerSalarioBase();
        double porcentajeDescuento = empleado.obtenerPorcentajeDescuento();
        
        return salarioBase * (porcentajeDescuento / 100.0);
    }
    
    // Verificar si supera umbral (requisito 3)
    bool superaUmbral(const Empleado& empleado, double umbral) const {
        return calcularSalarioNeto(empleado) > umbral;
    }
};

#endif