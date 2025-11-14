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
        cout << "COMANDOS DISPONIBLES:" << endl;
        cout << "----------------------------------------" << endl;
        cout << "  agregar [ID]  - Agregar maleta a la bodega" << endl;
        cout << "  retirar [ID]  - Retirar maleta de la bodega" << endl;
        cout << "  mostrar       - Mostrar estado de la bodega" << endl;
        cout << "  limpiar       - Vaciar toda la bodega" << endl;
        cout << "  ayuda         - Mostrar esta ayuda" << endl;
        cout << "  salir         - Salir del programa" << endl;
        cout << "========================================" << endl;
        cout << endl;
    }
    
    void mostrarEjemplos() const {
        cout << "EJEMPLOS DE USO:" << endl;
        cout << "----------------------------------------" << endl;
        cout << "1. Agregar maletas:" << endl;
        cout << "   > agregar M01" << endl;
        cout << "   > agregar M02" << endl;
        cout << "   > agregar M03" << endl;
        cout << endl;
        cout << "2. Retirar maleta (con maniobras):" << endl;
        cout << "   > retirar M02" << endl;
        cout << "   Salida: Maleta M02 retirada con 1 maniobra." << endl;
        cout << endl;
        cout << "3. Mostrar estado:" << endl;
        cout << "   > mostrar" << endl;
        cout << "   Estado actual: M01, M03" << endl;
        cout << endl;
        cout << "4. Retirar maleta del tope (sin maniobras):" << endl;
        cout << "   > retirar M03" << endl;
        cout << "   Salida: Maleta M03 retirada sin maniobras." << endl;
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
    
    void procesarComando(BodegaControlador& controlador, const char* comando, const char* parametro) const {
        if (strcmp(comando, "agregar") == 0) {
            if (strlen(parametro) > 0) {
                procesarComandoAgregar(controlador, parametro);
            } else {
                cout << "✗ Error: Debe especificar el ID de la maleta." << endl;
            }
        }
        else if (strcmp(comando, "retirar") == 0) {
            if (strlen(parametro) > 0) {
                procesarComandoRetirar(controlador, parametro);
            } else {
                cout << "✗ Error: Debe especificar el ID de la maleta." << endl;
            }
        }
        else if (strcmp(comando, "mostrar") == 0) {
            procesarComandoMostrar(controlador);
        }
        else if (strcmp(comando, "limpiar") == 0) {
            procesarComandoLimpiar(controlador);
        }
        else if (strcmp(comando, "ayuda") == 0) {
            mostrarMenu();
            mostrarEjemplos();
        }
        else {
            cout << "✗ Comando no reconocido. Escriba 'ayuda' para ver los comandos disponibles." << endl;
        }
    }
    
    void leerComando(char comando[], char parametro[]) const {
        char linea[MAX_COMANDO];
        cout << endl << "> ";
        cin.getline(linea, MAX_COMANDO);
        
        // Separar comando y parametro
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
        BodegaControlador controlador;
        char comando[MAX_COMANDO];
        char parametro[MAX_COMANDO];
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
        
        cout << endl;
        cout << "========================================" << endl;
        cout << "Gracias por usar el simulador de bodega." << endl;
        cout << "¡Buen vuelo!" << endl;
        cout << "========================================" << endl;
    }
};

#endif