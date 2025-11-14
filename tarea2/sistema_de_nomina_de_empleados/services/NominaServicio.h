#ifndef NOMINA_SERVICIO_H
#define NOMINA_SERVICIO_H

#include "../domain/Empleado.h"
#include "../repository/ListaSimpleRepositorio.h"
#include "ValidadorEmpleadoServicio.h"
#include "CalculadoraSalarioServicio.h"

// Estructura para empleado con salario calculado
struct EmpleadoConSalario {
    char nombre[100];
    double salarioBase;
    double porcentajeDescuento;
    double montoDescuento;
    double salarioNeto;
};

// Servicio: Gestor de nómina de empleados
class NominaServicio {
private:
    ListaSimpleRepositorio<Empleado> empleados;
    ValidadorEmpleadoServicio validador;
    CalculadoraSalarioServicio calculadora;
    
public:
    // 1. Insertar empleado al inicio
    bool agregarEmpleado(const char* nombre, double salarioBase, double porcentajeDescuento) {
        if (!validador.esEmpleadoValido(nombre, salarioBase, porcentajeDescuento)) {
            return false;
        }
        
        Empleado nuevoEmpleado(nombre, salarioBase, porcentajeDescuento);
        return empleados.insertarAlInicio(nuevoEmpleado);
    }
    
    // 2. Calcular salario neto para todos
    void calcularTodosSalariosNetos(EmpleadoConSalario resultados[], int& cantidad) const {
        cantidad = 0;
        
        empleados.recorrer([this, &resultados, &cantidad](const Empleado& emp) {
            EmpleadoConSalario& resultado = resultados[cantidad];
            
            strcpy(resultado.nombre, emp.obtenerNombre());
            resultado.salarioBase = emp.obtenerSalarioBase();
            resultado.porcentajeDescuento = emp.obtenerPorcentajeDescuento();
            resultado.montoDescuento = calculadora.calcularMontoDescuento(emp);
            resultado.salarioNeto = calculadora.calcularSalarioNeto(emp);
            
            cantidad++;
        });
    }
    
    // 3. Obtener empleados con salario neto superior al umbral
    void obtenerEmpleadosSobreUmbral(double umbral, EmpleadoConSalario resultados[], int& cantidad) const {
        cantidad = 0;
        
        empleados.recorrer([this, umbral, &resultados, &cantidad](const Empleado& emp) {
            if (calculadora.superaUmbral(emp, umbral)) {
                EmpleadoConSalario& resultado = resultados[cantidad];
                
                strcpy(resultado.nombre, emp.obtenerNombre());
                resultado.salarioBase = emp.obtenerSalarioBase();
                resultado.porcentajeDescuento = emp.obtenerPorcentajeDescuento();
                resultado.montoDescuento = calculadora.calcularMontoDescuento(emp);
                resultado.salarioNeto = calculadora.calcularSalarioNeto(emp);
                
                cantidad++;
            }
        });
    }
    
    int obtenerCantidadEmpleados() const {
        return empleados.obtenerTamanio();
    }
    
    bool estaVacia() const {
        return empleados.estaVacia();
    }
    
    void limpiarNomina() {
        empleados.limpiar();
    }
};

#endif