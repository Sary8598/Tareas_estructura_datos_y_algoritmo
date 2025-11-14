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
        cout << "COMANDOS DISPONIBLES:" << endl;
        cout << "----------------------------------------" << endl;
        cout << "  agregar           - Agregar nuevo empleado" << endl;
        cout << "  calcular          - Calcular todos los salarios netos" << endl;
        cout << "  filtrar [monto]   - Mostrar empleados con salario neto > monto" << endl;
        cout << "  filtrar           - Mostrar empleados con salario neto > RD$50,000" << endl;
        cout << "  limpiar           - Borrar todos los empleados" << endl;
        cout << "  ayuda             - Mostrar esta ayuda" << endl;
        cout << "  salir             - Salir del programa" << endl;
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
        cin.ignore();
        cin.getline(nombre, 100);
        
        cout << "Salario base (RD$): ";
        cin >> salarioBase;
        
        cout << "Porcentaje de descuento (%): ";
        cin >> porcentajeDescuento;
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
    
    void procesarComando(NominaControlador& controlador, const char* comando, const char* parametro) const {
        if (strcmp(comando, "agregar") == 0) {
            procesarAgregar(controlador);
        }
        else if (strcmp(comando, "calcular") == 0) {
            procesarCalcular(controlador);
        }
        else if (strcmp(comando, "filtrar") == 0) {
            double umbral = UMBRAL_DEFECTO;
            
            if (strlen(parametro) > 0) {
                umbral = atof(parametro);
                if (umbral <= 0) {
                    umbral = UMBRAL_DEFECTO;
                }
            }
            
            procesarFiltrar(controlador, umbral);
        }
        else if (strcmp(comando, "limpiar") == 0) {
            procesarLimpiar(controlador);
        }
        else if (strcmp(comando, "ayuda") == 0) {
            mostrarMenu();
            mostrarEjemplos();
        }
        else {
            cout << "✗ Comando no reconocido. Escriba 'ayuda' para ver los comandos." << endl;
        }
    }
    
    void leerComando(char comando[], char parametro[]) const {
        char linea[200];
        cout << endl << "> ";
        cin.getline(linea, 200);
        
        int i = 0;
        int j = 0;
        
        // Saltar espacios iniciales
        while (linea[i] == ' ' || linea[i] == '\t') {
            i++;
        }
        
        // Leer comando
        while (linea[i] != ' ' && linea[i] != '\t' && linea[i] != '\0') {
            comando[j++] = linea[i++];
        }
        comando[j] = '\0';
        
        // Saltar espacios
        while (linea[i] == ' ' || linea[i] == '\t') {
            i++;
        }
        
        // Leer parametro
        j = 0;
        while (linea[i] != '\0') {
            parametro[j++] = linea[i++];
        }
        parametro[j] = '\0';
    }
    
public:
    void ejecutar() {
        NominaControlador controlador;
        char comando[100];
        char parametro[100];
        bool continuar = true;
        
        mostrarBienvenida();
        mostrarMenu();
        mostrarEjemplos();
        
        while (continuar) {
            leerComando(comando, parametro);
            
            if (strcmp(comando, "salir") == 0) {
                continuar = false;
            } else if (strlen(comando) > 0) {
                procesarComando(controlador, comando, parametro);
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