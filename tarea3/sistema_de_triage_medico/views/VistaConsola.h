#ifndef VISTA_CONSOLA_H
#define VISTA_CONSOLA_H

#include "../controllers/ConsultorioControlador.h"
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

class VistaConsola {
private:
    static const int MAX_PACIENTES = 1000;
    
    void mostrarBienvenida() const {
        cout << "========================================" << endl;
        cout << "  SISTEMA DE TRIAGE MEDICO" << endl;
        cout << "  Atencion por Orden de Llegada" << endl;
        cout << "  (Sin Sistema de Prioridades)" << endl;
        cout << "========================================" << endl;
        cout << endl;
    }
    
    void mostrarMenu() const {
        cout << "\nOPCIONES DISPONIBLES:" << endl;
        cout << "----------------------------------------" << endl;
        cout << "  1 - Registrar nuevo paciente" << endl;
        cout << "  2 - Atender siguiente paciente" << endl;
        cout << "  3 - Ver lista de espera completa" << endl;
        cout << "  0 - Salir del programa" << endl;
        cout << "========================================" << endl;
        cout << endl;
    }
    
    void leerDatosPaciente(char nombre[], char sintoma[]) const {
        cout << endl;
        cout << "Datos del paciente:" << endl;
        cout << "Nombre: ";
        cin.getline(nombre, 100);
        
        cout << "Sintoma: ";
        cin.getline(sintoma, 200);
    }
    
    void procesarNuevoPaciente(ConsultorioControlador& controlador) const {
        char nombre[100];
        char sintoma[200];
        
        leerDatosPaciente(nombre, sintoma);
        
        RespuestaConsultorio respuesta = controlador.procesarNuevoPaciente(nombre, sintoma);
        
        cout << endl;
        if (respuesta.exito) {
            cout << "✓ " << respuesta.mensaje << endl;
            cout << "   Pacientes en espera: " << controlador.obtenerCantidadEnEspera() << endl;
        } else {
            cout << "✗ " << respuesta.mensaje << endl;
        }
    }
    
    void procesarAtender(ConsultorioControlador& controlador) const {
        RespuestaConsultorio respuesta = controlador.procesarAtender();
        
        cout << endl;
        if (respuesta.exito) {
            cout << " " << respuesta.mensaje << endl;
            cout << "   Pacientes restantes en espera: " << controlador.obtenerCantidadEnEspera() << endl;
        } else {
            cout << "ℹ " << respuesta.mensaje << endl;
        }
    }
    
    void procesarListaEspera(ConsultorioControlador& controlador) const {
        InfoPacienteEnEspera pacientes[MAX_PACIENTES];
        int cantidad;
        
        RespuestaConsultorio respuesta = controlador.procesarListaEspera(pacientes, cantidad);
        
        if (cantidad == 0) {
            cout << endl;
            cout << "ℹ " << respuesta.mensaje << endl;
            return;
        }
        
        cout << endl;
        cout << "========================================================================================================" << endl;
        cout << "LISTA DE ESPERA" << endl;
        cout << "========================================================================================================" << endl;
        cout << left << setw(8) << "POS." 
             << setw(10) << "FICHA" 
             << setw(30) << "NOMBRE"
             << setw(50) << "SINTOMA" << endl;
        cout << "========================================================================================================" << endl;
        
        for (int i = 0; i < cantidad; i++) {
            cout << left << setw(8) << pacientes[i].posicionEnFila
                 << setw(10) << pacientes[i].numeroFicha
                 << setw(30) << pacientes[i].nombre
                 << setw(50) << pacientes[i].sintoma << endl;
        }
        
        cout << "========================================================================================================" << endl;
        cout << "Total en espera: " << cantidad << " paciente(s)" << endl;
        
        if (cantidad > 0) {
            cout << endl;
            cout << "→ SIGUIENTE A ATENDER: " << pacientes[0].nombre << " (Ficha #" << pacientes[0].numeroFicha << ")" << endl;
        }
        
    }
    
    void procesarSiguiente(ConsultorioControlador& controlador) const {
        RespuestaConsultorio respuesta = controlador.procesarVerSiguiente();
        
        cout << endl;
        if (respuesta.exito) {
            cout << "→ " << respuesta.mensaje << endl;
        } else {
            cout << "ℹ " << respuesta.mensaje << endl;
        }
    }
    
    void procesarEstadisticas(ConsultorioControlador& controlador) const {
        cout << endl;
        cout << "========================================" << endl;
        cout << "ESTADISTICAS DEL CONSULTORIO" << endl;
        cout << "========================================" << endl;
        cout << "Fichas generadas:       " << controlador.obtenerTotalFichasGeneradas() << endl;
        cout << "Pacientes atendidos:    " << controlador.obtenerTotalPacientesAtendidos() << endl;
        cout << "Pacientes en espera:    " << controlador.obtenerCantidadEnEspera() << endl;
        cout << "Tiempo total ejecucion: " << fixed << setprecision(6) 
             << controlador.obtenerTiempoTotalEjecucion() << " ms" << endl;
        cout << "========================================" << endl;
    }
    
    void procesarLimpiar(ConsultorioControlador& controlador) const {
        RespuestaConsultorio respuesta = controlador.procesarLimpiar();
        cout << endl;
        cout << "✓ " << respuesta.mensaje << endl;
    }
    
    void procesarReiniciar(ConsultorioControlador& controlador) const {
        RespuestaConsultorio respuesta = controlador.procesarReiniciar();
        cout << endl;
        cout << "✓ " << respuesta.mensaje << endl;
    }
    
    void procesarOpcion(ConsultorioControlador& controlador, int opcion) const {
        switch (opcion) {
            case 1:
                procesarNuevoPaciente(controlador);
                break;
            case 2:
                procesarAtender(controlador);
                break;
            case 3:
                procesarListaEspera(controlador);
                break;
            default:
                cout << "✗ Opcion no valida. Presione 8 para ver las opciones." << endl;
                break;
        }
    }
    
    int leerOpcion() const {
        int opcion;
        cout << endl << "Seleccione una opcion (0-3): ";
        cin >> opcion;
        cin.ignore();
        return opcion;
    }
    
public:
    void ejecutar() {
        ConsultorioControlador controlador;
        int opcion;
        bool continuar = true;
        
        mostrarBienvenida();
        
        while (continuar) {
            mostrarMenu();
            opcion = leerOpcion();
            
            if (opcion == 0) {
                continuar = false;
            } else {
                procesarOpcion(controlador, opcion);
            }
        }
        
        cout << endl;
        cout << "========================================" << endl;
        cout << "RESUMEN FINAL" << endl;
        cout << "========================================" << endl;
        cout << "Total de fichas generadas: " << controlador.obtenerTotalFichasGeneradas() << endl;
        cout << "Total de pacientes atendidos: " << controlador.obtenerTotalPacientesAtendidos() << endl;
        cout << "Pacientes sin atender: " << controlador.obtenerCantidadEnEspera() << endl;
        cout << "Tiempo total: " << fixed << setprecision(6) 
             << controlador.obtenerTiempoTotalEjecucion() << " ms" << endl;
        cout << "========================================" << endl;
        cout << endl;
        cout << "Gracias por usar el sistema de triage." << endl;
        cout << "¡Que tenga un excelente dia!" << endl;
        cout << "========================================" << endl;
    }
};

#endif