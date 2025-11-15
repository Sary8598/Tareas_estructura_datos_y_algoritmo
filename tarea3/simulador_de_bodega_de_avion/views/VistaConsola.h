#ifndef VISTA_CONSOLA_H
#define VISTA_CONSOLA_H

#include "../controllers/BodegaControlador.h"
#include <iostream>
#include <cstring>
using namespace std;

class VistaConsola {
private:
    static const int MAX_COMANDO = 100;
    static const int MAX_MALETAS = 100;
    
    void mostrarBienvenida() const {
        cout << "========================================" << endl;
        cout << "  SIMULADOR DE BODEGA DE AVION" << endl;
        cout << "  Sistema de Gestion de Equipaje" << endl;
        cout << "========================================" << endl;
        cout << endl;
    }
    
    void mostrarMenu() const {
        cout << "\nOPCIONES DISPONIBLES:" << endl;
        cout << "----------------------------------------" << endl;
        cout << "  1 - Agregar maleta a la bodega" << endl;
        cout << "  2 - Retirar maleta con maniobra" << endl;
        cout << "  3 - Mostrar estado de la bodega" << endl;
        cout << "  4 - Vaciar toda la bodega" << endl;
        cout << "  0 - Salir del programa" << endl;
        cout << "========================================" << endl;
        cout << endl;
    }
    
    void procesarComandoAgregar(BodegaControlador& controlador, const char* identificador) const {
        RespuestaControlador respuesta = controlador.procesarAgregar(identificador);
        
        if (respuesta.exito) {
            cout << "✓ " << respuesta.mensaje << endl;
        } else {
            cout << "✗ " << respuesta.mensaje << endl;
        }
    }
    
    void procesarComandoRetirar(BodegaControlador& controlador, const char* identificador) const {
        RespuestaControlador respuesta = controlador.procesarRetirar(identificador);
        
        if (respuesta.exito) {
            cout << "✓ " << respuesta.mensaje << endl;
        } else {
            cout << "✗ " << respuesta.mensaje << endl;
        }
    }
    
    void procesarComandoMostrar(BodegaControlador& controlador) const {
        char listaMaletas[MAX_MALETAS][50];
        int cantidad;
        
        RespuestaControlador respuesta = controlador.procesarMostrar(listaMaletas, cantidad);
        
        if (cantidad == 0) {
            cout << respuesta.mensaje << endl;
            return;
        }
        
        cout << endl;
        cout << "========================================" << endl;
        cout << "ESTADO DE LA BODEGA" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Cantidad de maletas: " << cantidad << endl;
        cout << endl;
        cout << "Estado actual: ";
        
        for (int i = 0; i < cantidad; i++) {
            cout << listaMaletas[i];
            if (i < cantidad - 1) {
                cout << ", ";
            }
        }
        cout << endl;
        
        cout << endl;
        cout << "Visualizacion (TOPE arriba):" << endl;
        cout << "  [TOPE]" << endl;
        
        for (int i = cantidad - 1; i >= 0; i--) {
            cout << "  | " << listaMaletas[i] << " |" << endl;
        }
        
        cout << "  [FONDO]" << endl;
        cout << "========================================" << endl;
    }
    
    void procesarComandoLimpiar(BodegaControlador& controlador) const {
        RespuestaControlador respuesta = controlador.procesarLimpiar();
        cout << "✓ " << respuesta.mensaje << endl;
    }
    
    void procesarOpcion(BodegaControlador& controlador, int opcion) const {
        char identificador[50];
        
        switch (opcion) {
            case 1:
                cout << "Ingrese ID de la maleta: ";
                cin.getline(identificador, 50);
                procesarComandoAgregar(controlador, identificador);
                break;
            case 2:
                cout << "Ingrese ID de la maleta a retirar: ";
                cin.getline(identificador, 50);
                procesarComandoRetirar(controlador, identificador);
                break;
            case 3:
                procesarComandoMostrar(controlador);
                break;
            case 4:
                procesarComandoLimpiar(controlador);
                break;
            default:
                cout << "✗ Opcion no valida. Presione 5 para ver las opciones." << endl;
                break;
        }
    }
    
    int leerOpcion() const {
        int opcion;
        cout << endl << "Seleccione una opcion (0-4): ";
        cin >> opcion;
        cin.ignore();
        return opcion;
    }
    
public:
    void ejecutar() {
        BodegaControlador controlador;
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
        cout << "Gracias por usar el simulador de bodega." << endl;
        cout << "¡Buen vuelo!" << endl;
        cout << "========================================" << endl;
    }
};

#endif