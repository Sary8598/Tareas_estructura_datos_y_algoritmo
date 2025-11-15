#ifndef VISTA_CONSOLA_H
#define VISTA_CONSOLA_H

#include "../controllers/BancoControlador.h"
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

class VistaConsola {
private:
    static const int MAX_CLIENTES = 1000;
    
    void mostrarBienvenida() const {
        cout << "========================================" << endl;
        cout << "  SISTEMA DE TURNOS BANCARIOS" << endl;
        cout << "  Atencion por Orden de Llegada (FIFO)" << endl;
        cout << "========================================" << endl;
        cout << endl;
    }
    
    void mostrarMenu() const {
        cout << "\nOPCIONES DISPONIBLES:" << endl;
        cout << "----------------------------------------" << endl;
        cout << "  1 - Registrar nuevo cliente" << endl;
        cout << "  2 - Atender siguiente cliente" << endl;
        cout << "  3 - Ver todos los clientes en fila" << endl;
        cout << "  0 - Salir del programa" << endl;
        cout << "========================================" << endl;
        cout << endl;
    }
    
    void leerDatosCliente(char nombre[], char asunto[]) const {
        cout << endl;
        cout << "Datos del cliente:" << endl;
        cout << "Nombre: ";
        cin.getline(nombre, 100);
        
        cout << "Asunto: ";
        cin.getline(asunto, 200);
    }
    
    void procesarRegistrar(BancoControlador& controlador) const {
        char nombre[100];
        char asunto[200];
        
        leerDatosCliente(nombre, asunto);
        
        RespuestaBanco respuesta = controlador.procesarRegistrar(nombre, asunto);
        
        cout << endl;
        if (respuesta.exito) {
            cout << "✓ " << respuesta.mensaje << endl;
            cout << "   Clientes en fila: " << controlador.obtenerCantidadEnFila() << endl;
        } else {
            cout << "✗ " << respuesta.mensaje << endl;
        }
    }
    
    void procesarAtender(BancoControlador& controlador) const {
        RespuestaBanco respuesta = controlador.procesarAtender();
        
        cout << endl;
        if (respuesta.exito) {
            cout << "🏦 " << respuesta.mensaje << endl;
            cout << "   Clientes restantes en fila: " << controlador.obtenerCantidadEnFila() << endl;
        } else {
            cout << "ℹ " << respuesta.mensaje << endl;
        }
    }
    
    void procesarMostrar(BancoControlador& controlador) const {
        InfoClienteEnFila clientes[MAX_CLIENTES];
        int cantidad;
        
        RespuestaBanco respuesta = controlador.procesarMostrar(clientes, cantidad);
        
        if (cantidad == 0) {
            cout << endl;
            cout << "ℹ " << respuesta.mensaje << endl;
            return;
        }
        
        cout << endl;
        cout << "========================================================================================================" << endl;
        cout << "FILA DE ESPERA - ORDEN FIFO (First In First Out)" << endl;
        cout << "========================================================================================================" << endl;
        cout << left << setw(8) << "POS." 
             << setw(10) << "TURNO" 
             << setw(30) << "NOMBRE"
             << setw(50) << "ASUNTO" << endl;
        cout << "========================================================================================================" << endl;
        
        for (int i = 0; i < cantidad; i++) {
            cout << left << setw(8) << clientes[i].posicionEnFila
                 << setw(10) << clientes[i].numeroTurno
                 << setw(30) << clientes[i].nombre
                 << setw(50) << clientes[i].asunto << endl;
        }
        
        cout << "========================================================================================================" << endl;
        cout << "Total en fila: " << cantidad << " cliente(s)" << endl;
        
        if (cantidad > 0) {
            cout << endl;
            cout << "→ SIGUIENTE A ATENDER: " << clientes[0].nombre << " (Turno #" << clientes[0].numeroTurno << ")" << endl;
        }
        
    }
    
    void procesarSiguiente(BancoControlador& controlador) const {
        RespuestaBanco respuesta = controlador.procesarVerSiguiente();
        
        cout << endl;
        if (respuesta.exito) {
            cout << "→ " << respuesta.mensaje << endl;
        } else {
            cout << "ℹ " << respuesta.mensaje << endl;
        }
    }
    
    void procesarEstadisticas(BancoControlador& controlador) const {
        cout << endl;
        cout << "========================================" << endl;
        cout << "ESTADISTICAS DEL SISTEMA" << endl;
        cout << "========================================" << endl;
        cout << "Turnos generados:       " << controlador.obtenerTotalTurnosGenerados() << endl;
        cout << "Clientes atendidos:     " << controlador.obtenerTotalClientesAtendidos() << endl;
        cout << "Clientes en espera:     " << controlador.obtenerCantidadEnFila() << endl;
        cout << "Tiempo total ejecucion: " << fixed << setprecision(6) 
             << controlador.obtenerTiempoTotalEjecucion() << " ms" << endl;
        cout << "========================================" << endl;
    }
    
    void procesarLimpiar(BancoControlador& controlador) const {
        RespuestaBanco respuesta = controlador.procesarLimpiar();
        cout << endl;
        cout << "✓ " << respuesta.mensaje << endl;
    }
    
    void procesarReiniciar(BancoControlador& controlador) const {
        RespuestaBanco respuesta = controlador.procesarReiniciar();
        cout << endl;
        cout << "✓ " << respuesta.mensaje << endl;
    }
    
    void procesarOpcion(BancoControlador& controlador, int opcion) const {
        switch (opcion) {
            case 1:
                procesarRegistrar(controlador);
                break;
            case 2:
                procesarAtender(controlador);
                break;
            case 3:
                procesarMostrar(controlador);
                break;
            case 0:
                mostrarMenu();
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
        cin.ignore(); // Limpiar buffer
        return opcion;
    }
    
public:
    void ejecutar() {
        BancoControlador controlador;
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
        cout << "Turnos generados:       " << controlador.obtenerTotalTurnosGenerados() << endl;
        cout << "Clientes atendidos:     " << controlador.obtenerTotalClientesAtendidos() << endl;
        cout << "Tiempo total ejecucion: " << fixed << setprecision(6) 
             << controlador.obtenerTiempoTotalEjecucion() << " ms" << endl;
        cout << "========================================" << endl;
        cout << "Gracias por usar el Sistema de Turnos Bancarios!" << endl;
    }
};

#endif