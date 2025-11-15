#ifndef VISTA_CONSOLA_H
#define VISTA_CONSOLA_H

#include "../controllers/NominaControlador.h"
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

class VistaConsola {
private:
    static const int MAX_EMPLEADOS = 1000;
    static constexpr double UMBRAL_DEFECTO = 50000.0;
    
    void mostrarBienvenida() const {
        cout << "========================================" << endl;
        cout << "  SISTEMA DE NOMINA DE EMPLEADOS" << endl;
        cout << "  Calculo de Salario Neto" << endl;
        cout << "========================================" << endl;
        cout << endl;
    }
    
    void mostrarMenu() const {
        cout << "MENU PRINCIPAL:" << endl;
        cout << "----------------------------------------" << endl;
        cout << "  1. Agregar nuevo empleado" << endl;
        cout << "  2. Calcular todos los salarios netos" << endl;
        cout << "  3. Filtrar empleados (salario > RD$50,000)" << endl;
        cout << "  4. Filtrar empleados (monto personalizado)" << endl;
        cout << "  5. Limpiar todos los empleados" << endl;
        cout << "  6. Mostrar ayuda" << endl;
        cout << "  7. Salir del programa" << endl;
        cout << "========================================" << endl;
        cout << endl;
    }
    
    void mostrarEjemplos() const {
        cout << "EJEMPLOS DE USO:" << endl;
        cout << "----------------------------------------" << endl;
        cout << "1. Agregar empleados:" << endl;
        cout << "   > agregar" << endl;
        cout << "   Nombre: Juan Perez" << endl;
        cout << "   Salario base: 75000" << endl;
        cout << "   Porcentaje de descuento: 15" << endl;
        cout << endl;
        cout << "2. Calcular salarios netos:" << endl;
        cout << "   > calcular" << endl;
        cout << "   [Muestra todos los empleados con calculos]" << endl;
        cout << endl;
        cout << "3. Filtrar por umbral:" << endl;
        cout << "   > filtrar" << endl;
        cout << "   [Muestra empleados con salario neto > RD$50,000]" << endl;
        cout << endl;
        cout << "   > filtrar 100000" << endl;
        cout << "   [Muestra empleados con salario neto > RD$100,000]" << endl;
        cout << "========================================" << endl;
        cout << endl;
    }
    
    void mostrarTiempo(double tiempo) const {
        cout << fixed << setprecision(6);
        cout << "   [Tiempo de ejecucion: " << tiempo << " ms]" << endl;
    }
    
    void leerDatosEmpleado(char nombre[], double& salarioBase, double& porcentajeDescuento) const {
        cout << endl;
        cout << "Ingrese los datos del empleado:" << endl;
        cout << "Nombre: ";
        cin.getline(nombre, 100);
        
        cout << "Salario base (RD$): ";
        cin >> salarioBase;
        
        cout << "Porcentaje de descuento (%): ";
        cin >> porcentajeDescuento;
        cin.ignore(); // Clear buffer after numeric input
    }
    
    void procesarAgregar(NominaControlador& controlador) const {
        char nombre[100];
        double salarioBase, porcentajeDescuento;
        
        leerDatosEmpleado(nombre, salarioBase, porcentajeDescuento);
        
        RespuestaNomina respuesta = controlador.procesarAgregar(nombre, salarioBase, porcentajeDescuento);
        
        cout << endl;
        if (respuesta.exito) {
            cout << "✓ " << respuesta.mensaje << endl;
        } else {
            cout << "✗ " << respuesta.mensaje << endl;
        }
        mostrarTiempo(respuesta.tiempoEjecucion);
    }
    
    void mostrarTablaEmpleados(EmpleadoConSalario empleados[], int cantidad) const {
        cout << endl;
        cout << "========================================================================================================" << endl;
        cout << left << setw(25) << "NOMBRE" 
             << right << setw(15) << "SALARIO BASE" 
             << setw(12) << "DESC. %" 
             << setw(15) << "DESCUENTO" 
             << setw(18) << "SALARIO NETO" << endl;
        cout << "========================================================================================================" << endl;
        
        cout << fixed << setprecision(2);
        
        for (int i = 0; i < cantidad; i++) {
            cout << left << setw(25) << empleados[i].nombre
                 << right << setw(15) << empleados[i].salarioBase
                 << setw(12) << empleados[i].porcentajeDescuento
                 << setw(15) << empleados[i].montoDescuento
                 << setw(18) << empleados[i].salarioNeto << endl;
        }
        
        cout << "========================================================================================================" << endl;
    }
    
    void procesarCalcular(NominaControlador& controlador) const {
        EmpleadoConSalario empleados[MAX_EMPLEADOS];
        int cantidad;
        
        RespuestaNomina respuesta = controlador.procesarCalcularTodos(empleados, cantidad);
        
        if (cantidad == 0) {
            cout << endl;
            cout << "ℹ " << respuesta.mensaje << endl;
            mostrarTiempo(respuesta.tiempoEjecucion);
            return;
        }
        
        cout << endl;
        cout << "CALCULO DE SALARIOS NETOS" << endl;
        cout << "Total de empleados: " << cantidad << endl;
        
        mostrarTablaEmpleados(empleados, cantidad);
        
        // Calcular estadisticas
        double totalSalarioBase = 0.0;
        double totalDescuentos = 0.0;
        double totalSalarioNeto = 0.0;
        
        for (int i = 0; i < cantidad; i++) {
            totalSalarioBase += empleados[i].salarioBase;
            totalDescuentos += empleados[i].montoDescuento;
            totalSalarioNeto += empleados[i].salarioNeto;
        }
        
        cout << endl;
        cout << "RESUMEN FINANCIERO:" << endl;
        cout << "Total Salario Base:  RD$ " << fixed << setprecision(2) << totalSalarioBase << endl;
        cout << "Total Descuentos:    RD$ " << totalDescuentos << endl;
        cout << "Total Salario Neto:  RD$ " << totalSalarioNeto << endl;
        
        mostrarTiempo(respuesta.tiempoEjecucion);
    }
    
    void procesarFiltrar(NominaControlador& controlador, double umbral) const {
        EmpleadoConSalario empleados[MAX_EMPLEADOS];
        int cantidad;
        
        RespuestaNomina respuesta = controlador.procesarEmpleadosSobreUmbral(umbral, empleados, cantidad);
        
        cout << endl;
        cout << "FILTRO: SALARIOS NETOS > RD$" << fixed << setprecision(2) << umbral << endl;
        cout << respuesta.mensaje << endl;
        
        if (cantidad > 0) {
            mostrarTablaEmpleados(empleados, cantidad);
        }
        
        mostrarTiempo(respuesta.tiempoEjecucion);
    }
    
    void procesarLimpiar(NominaControlador& controlador) const {
        RespuestaNomina respuesta = controlador.procesarLimpiar();
        cout << endl;
        cout << "✓ " << respuesta.mensaje << endl;
        mostrarTiempo(respuesta.tiempoEjecucion);
    }
    
    void procesarOpcion(NominaControlador& controlador, int opcion) const {
        switch (opcion) {
            case 1:
                procesarAgregar(controlador);
                break;
            case 2:
                procesarCalcular(controlador);
                break;
            case 3:
                procesarFiltrar(controlador, UMBRAL_DEFECTO);
                break;
            case 4: {
                cout << "Ingrese el monto minimo: RD$";
                double umbral;
                cin >> umbral;
                cin.ignore();
                if (umbral <= 0) umbral = UMBRAL_DEFECTO;
                procesarFiltrar(controlador, umbral);
                break;
            }
            case 5:
                procesarLimpiar(controlador);
                break;
            case 6:
                mostrarMenu();
                mostrarEjemplos();
                break;
            default:
                cout << "✗ Opcion invalida. Seleccione del 1 al 7." << endl;
                break;
        }
    }
    
    int leerOpcion() const {
        int opcion;
        cout << endl << "Seleccione una opcion (1-7): ";
        cin >> opcion;
        cin.ignore(); // Clear buffer
        return opcion;
    }
    
public:
    void ejecutar() {
        NominaControlador controlador;
        int opcion;
        bool continuar = true;
        
        mostrarBienvenida();
        mostrarMenu();
        
        while (continuar) {
            opcion = leerOpcion();
            
            if (opcion == 7) {
                continuar = false;
            } else {
                procesarOpcion(controlador, opcion);
                if (continuar) {
                    cout << endl;
                    mostrarMenu();
                }
            }
        }
        
        double tiempoTotal = controlador.obtenerTiempoTotalEjecucion();
        
        cout << endl;
        cout << "========================================" << endl;
        cout << "ESTADISTICAS DE EJECUCION" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Empleados registrados: " << controlador.obtenerCantidadEmpleados() << endl;
        cout << "Tiempo total del programa: " << fixed << setprecision(6) << tiempoTotal << " ms" << endl;
        cout << "========================================" << endl;
        cout << endl;
        cout << "Gracias por usar el sistema de nomina." << endl;
        cout << "¡Hasta pronto!" << endl;
        cout << "========================================" << endl;
    }
};

#endif