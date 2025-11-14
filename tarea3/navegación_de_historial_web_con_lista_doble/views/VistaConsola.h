#ifndef VISTA_CONSOLA_H
#define VISTA_CONSOLA_H

#include "../controllers/NavegadorControlador.h"
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

class VistaConsola {
private:
    static const int MAX_COMANDO = 100;
    static const int MAX_PAGINAS = 1000;
    
    void mostrarBienvenida() const {
        cout << "========================================" << endl;
        cout << "  NAVEGADOR WEB - GESTOR DE HISTORIAL" << endl;
        cout << "  Lista Doblemente Enlazada" << endl;
        cout << "========================================" << endl;
        cout << endl;
    }
    
    void mostrarMenu() const {
        cout << "COMANDOS DISPONIBLES:" << endl;
        cout << "----------------------------------------" << endl;
        cout << "  visitar [URL]  - Visitar una pagina web" << endl;
        cout << "  atras          - Ir a la pagina anterior" << endl;
        cout << "  adelante       - Ir a la pagina siguiente" << endl;
        cout << "  eliminar [URL] - Eliminar URL del historial" << endl;
        cout << "  mostrar        - Ver historial completo" << endl;
        cout << "  actual         - Ver pagina actual" << endl;
        cout << "  limpiar        - Borrar todo el historial" << endl;
        cout << "  ayuda          - Mostrar esta ayuda" << endl;
        cout << "  salir          - Salir del programa" << endl;
        cout << "========================================" << endl;
        cout << endl;
    }
    
    void mostrarEjemplos() const {
        cout << "EJEMPLOS DE USO:" << endl;
        cout << "----------------------------------------" << endl;
        cout << "1. Visitar paginas:" << endl;
        cout << "   > visitar https://google.com" << endl;
        cout << "   > visitar https://facebook.com" << endl;
        cout << "   > visitar https://youtube.com" << endl;
        cout << endl;
        cout << "2. Navegar en el historial:" << endl;
        cout << "   > atras" << endl;
        cout << "   Pagina actual: https://facebook.com" << endl;
        cout << "   > adelante" << endl;
        cout << "   Pagina actual: https://youtube.com" << endl;
        cout << endl;
        cout << "3. Eliminar del historial:" << endl;
        cout << "   > eliminar https://facebook.com" << endl;
        cout << endl;
        cout << "4. Ver historial completo:" << endl;
        cout << "   > mostrar" << endl;
        cout << "   [Muestra historial de ultima a primera]" << endl;
        cout << "========================================" << endl;
        cout << endl;
    }
    
    void mostrarTiempo(double tiempo) const {
        cout << "   [Tiempo: " << tiempo << " ms]" << endl;
    }
    
    void procesarVisitar(NavegadorControlador& controlador, const char* url) const {
        RespuestaNavegador respuesta = controlador.procesarVisitar(url);
        
        if (respuesta.exito) {
            cout << "✓ " << respuesta.mensaje << endl;
        } else {
            cout << "✗ " << respuesta.mensaje << endl;
        }
        mostrarTiempo(respuesta.tiempoEjecucion);
    }
    
    void procesarAtras(NavegadorControlador& controlador) const {
        RespuestaNavegador respuesta = controlador.procesarAtras();
        
        if (respuesta.exito) {
            cout << "← " << respuesta.mensaje << endl;
        } else {
            cout << "✗ " << respuesta.mensaje << endl;
        }
        mostrarTiempo(respuesta.tiempoEjecucion);
    }
    
    void procesarAdelante(NavegadorControlador& controlador) const {
        RespuestaNavegador respuesta = controlador.procesarAdelante();
        
        if (respuesta.exito) {
            cout << "→ " << respuesta.mensaje << endl;
        } else {
            cout << "✗ " << respuesta.mensaje << endl;
        }
        mostrarTiempo(respuesta.tiempoEjecucion);
    }
    
    void procesarEliminar(NavegadorControlador& controlador, const char* url) const {
        RespuestaNavegador respuesta = controlador.procesarEliminar(url);
        
        if (respuesta.exito) {
            cout << "✓ " << respuesta.mensaje << endl;
        } else {
            cout << "✗ " << respuesta.mensaje << endl;
        }
        mostrarTiempo(respuesta.tiempoEjecucion);
    }
    
    void procesarMostrar(NavegadorControlador& controlador) const {
        PaginaWeb paginas[MAX_PAGINAS];
        int cantidad;
        
        RespuestaNavegador respuesta = controlador.procesarMostrar(paginas, cantidad);
        
        if (cantidad == 0) {
            cout << "📄 " << respuesta.mensaje << endl;
            mostrarTiempo(respuesta.tiempoEjecucion);
            return;
        }
        
        cout << endl;
        cout << "========================================" << endl;
        cout << "HISTORIAL DE NAVEGACION" << endl;
        cout << "Orden: Mas reciente a mas antigua" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Total de paginas: " << cantidad << endl;
        cout << endl;
        
        for (int i = 0; i < cantidad; i++) {
            cout << (i + 1) << ". " << paginas[i].obtenerURL() << endl;
            cout << "   Fecha: " << paginas[i].obtenerFechaHora() << endl;
            
            if (i < cantidad - 1) {
                cout << endl;
            }
        }
        
        cout << "========================================" << endl;
        mostrarTiempo(respuesta.tiempoEjecucion);
    }
    
    void procesarActual(NavegadorControlador& controlador) const {
        const PaginaWeb* actual = controlador.obtenerPaginaActual();
        
        cout << endl;
        cout << "========================================" << endl;
        cout << "PAGINA ACTUAL" << endl;
        cout << "----------------------------------------" << endl;
        
        if (actual != nullptr) {
            cout << "URL: " << actual->obtenerURL() << endl;
            cout << "Visitada: " << actual->obtenerFechaHora() << endl;
            cout << endl;
            
            if (controlador.puedeIrAtras()) {
                cout << "← Puede ir ATRAS" << endl;
            }
            if (controlador.puedeIrAdelante()) {
                cout << "→ Puede ir ADELANTE" << endl;
            }
        } else {
            cout << "No hay pagina actual. Visite una pagina primero." << endl;
        }
        
        cout << "========================================" << endl;
    }
    
    void procesarLimpiar(NavegadorControlador& controlador) const {
        RespuestaNavegador respuesta = controlador.procesarLimpiar();
        cout << "✓ " << respuesta.mensaje << endl;
        mostrarTiempo(respuesta.tiempoEjecucion);
    }
    
    void procesarComando(NavegadorControlador& controlador, const char* comando, const char* parametro) const {
        if (strcmp(comando, "visitar") == 0) {
            if (strlen(parametro) > 0) {
                procesarVisitar(controlador, parametro);
            } else {
                cout << "✗ Error: Debe especificar una URL." << endl;
            }
        }
        else if (strcmp(comando, "atras") == 0) {
            procesarAtras(controlador);
        }
        else if (strcmp(comando, "adelante") == 0) {
            procesarAdelante(controlador);
        }
        else if (strcmp(comando, "eliminar") == 0) {
            if (strlen(parametro) > 0) {
                procesarEliminar(controlador, parametro);
            } else {
                cout << "✗ Error: Debe especificar una URL." << endl;
            }
        }
        else if (strcmp(comando, "mostrar") == 0) {
            procesarMostrar(controlador);
        }
        else if (strcmp(comando, "actual") == 0) {
            procesarActual(controlador);
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
        char linea[MAX_COMANDO];
        cout << endl << "> ";
        cin.getline(linea, MAX_COMANDO);
        
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
        NavegadorControlador controlador;
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
        
        double tiempoTotal = controlador.obtenerTiempoTotalEjecucion();
        
        cout << endl;
        cout << "========================================" << endl;
        cout << "ESTADISTICAS DE EJECUCION" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Tiempo total del programa: " << tiempoTotal << " ms" << endl;
        cout << "========================================" << endl;
        cout << endl;
        cout << "Gracias por usar el navegador." << endl;
        cout << "¡Hasta pronto!" << endl;
        cout << "========================================" << endl;
    }
};

#endif