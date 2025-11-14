#ifndef NOMINA_CONTROLADOR_H
#define NOMINA_CONTROLADOR_H

#include "../services/NominaServicio.h"
#include "../services/MedidorTiempoServicio.h"
#include <cstring>
#include <cstdio>

// Estructura de respuesta con tiempo
struct RespuestaNomina {
    bool exito;
    char mensaje[300];
    double tiempoEjecucion;
    int cantidad;
};

class NominaControlador {
private:
    NominaServicio servicio;
    MedidorTiempoServicio medidor;
    
public:
    // 1. Agregar empleado al inicio
    RespuestaNomina procesarAgregar(const char* nombre, double salarioBase, double porcentajeDescuento) {
        RespuestaNomina respuesta;
        
        medidor.iniciar();
        bool exito = servicio.agregarEmpleado(nombre, salarioBase, porcentajeDescuento);
        respuesta.tiempoEjecucion = medidor.detener();
        
        respuesta.exito = exito;
        respuesta.cantidad = 0;
        
        if (exito) {
            sprintf(respuesta.mensaje, 
                    "Empleado '%s' agregado exitosamente (Salario: RD$%.2f, Descuento: %.1f%%).", 
                    nombre, salarioBase, porcentajeDescuento);
        } else {
            sprintf(respuesta.mensaje, "Error: Datos invalidos para el empleado.");
        }
        
        return respuesta;
    }
    
    // 2. Calcular salarios netos de todos
    RespuestaNomina procesarCalcularTodos(EmpleadoConSalario resultados[], int& cantidad) {
        RespuestaNomina respuesta;
        
        medidor.iniciar();
        servicio.calcularTodosSalariosNetos(resultados, cantidad);
        respuesta.tiempoEjecucion = medidor.detener();
        
        respuesta.exito = true;
        respuesta.cantidad = cantidad;
        
        if (cantidad == 0) {
            sprintf(respuesta.mensaje, "No hay empleados registrados.");
        } else {
            sprintf(respuesta.mensaje, "Salarios calculados para %d empleado(s).", cantidad);
        }
        
        return respuesta;
    }
    
    // 3. Mostrar empleados con salario neto > RD$50,000
    RespuestaNomina procesarEmpleadosSobreUmbral(double umbral, EmpleadoConSalario resultados[], int& cantidad) {
        RespuestaNomina respuesta;
        
        medidor.iniciar();
        servicio.obtenerEmpleadosSobreUmbral(umbral, resultados, cantidad);
        respuesta.tiempoEjecucion = medidor.detener();
        
        respuesta.exito = true;
        respuesta.cantidad = cantidad;
        
        if (cantidad == 0) {
            sprintf(respuesta.mensaje, "No hay empleados con salario neto superior a RD$%.2f", umbral);
        } else {
            sprintf(respuesta.mensaje, "%d empleado(s) con salario neto superior a RD$%.2f", cantidad, umbral);
        }
        
        return respuesta;
    }
    
    RespuestaNomina procesarLimpiar() {
        RespuestaNomina respuesta;
        
        medidor.iniciar();
        servicio.limpiarNomina();
        respuesta.tiempoEjecucion = medidor.detener();
        
        respuesta.exito = true;
        respuesta.cantidad = 0;
        sprintf(respuesta.mensaje, "Nomina limpiada exitosamente.");
        
        return respuesta;
    }
    
    int obtenerCantidadEmpleados() const {
        return servicio.obtenerCantidadEmpleados();
    }
    
    double obtenerTiempoTotalEjecucion() const {
        return medidor.obtenerTiempoTotal();
    }
};

#endif