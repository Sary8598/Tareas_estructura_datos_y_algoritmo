#ifndef HISTORIAL_SERVICIO_H
#define HISTORIAL_SERVICIO_H

#include "../domain/PaginaWeb.h"
#include "../domain/Nodo.h"
#include "../repository/ListaDobleRepositorio.h"
#include "ValidadorURLServicio.h"
#include "FechaHoraServicio.h"
#include <cstdio>

// Servicio: Gestor del historial de navegacion
class HistorialServicio {
private:
    ListaDobleRepositorio<PaginaWeb> historial;
    Nodo<PaginaWeb>* paginaActual;
    ValidadorURLServicio validador;
    FechaHoraServicio fechaHora;
    
public:
    HistorialServicio() : paginaActual(nullptr) {}
    
    // a) Insertar nueva visita al final
    bool visitarPagina(const char* url) {
        if (!validador.esURLValida(url)) {
            return false;
        }
        
        char fechaActual[30];
        fechaHora.obtenerFechaHoraActual(fechaActual, 30);
        
        PaginaWeb nuevaPagina(url, fechaActual);
        bool exito = historial.insertarAlFinal(nuevaPagina);
        
        if (exito) {
            paginaActual = historial.obtenerCola();
        }
        
        return exito;
    }
    
    // b) Navegar hacia atras
    bool irAtras() {
        if (paginaActual == nullptr || paginaActual->anterior == nullptr) {
            return false;
        }
        
        paginaActual = paginaActual->anterior;
        return true;
    }
    
    // b) Navegar hacia adelante
    bool irAdelante() {
        if (paginaActual == nullptr || paginaActual->siguiente == nullptr) {
            return false;
        }
        
        paginaActual = paginaActual->siguiente;
        return true;
    }
    
    // c) Eliminar URL especifica
    bool eliminarURL(const char* url) {
        Nodo<PaginaWeb>* actual = historial.obtenerCabeza();
        
        while (actual != nullptr) {
            if (actual->dato.esIgualURL(url)) {
                // Si es la pagina actual, mover a otra pagina
                if (actual == paginaActual) {
                    if (actual->siguiente != nullptr) {
                        paginaActual = actual->siguiente;
                    } else if (actual->anterior != nullptr) {
                        paginaActual = actual->anterior;
                    } else {
                        paginaActual = nullptr;
                    }
                }
                
                return historial.eliminarNodo(actual);
            }
            actual = actual->siguiente;
        }
        
        return false;
    }
    
    // Obtener pagina actual
    const PaginaWeb* obtenerPaginaActual() const {
        if (paginaActual == nullptr) {
            return nullptr;
        }
        return &(paginaActual->dato);
    }
    
    // Verificar si puede ir atras
    bool puedeIrAtras() const {
        return paginaActual != nullptr && paginaActual->anterior != nullptr;
    }
    
    // Verificar si puede ir adelante
    bool puedeIrAdelante() const {
        return paginaActual != nullptr && paginaActual->siguiente != nullptr;
    }
    
    // d) Obtener historial en orden cronologico inverso
    void obtenerHistorialInverso(PaginaWeb paginas[], int& cantidad) const {
        cantidad = 0;
        Nodo<PaginaWeb>* actual = historial.obtenerCola();
        
        while (actual != nullptr) {
            paginas[cantidad++] = actual->dato;
            actual = actual->anterior;
        }
    }
    
    // Obtener tamaño del historial
    int obtenerTamanioHistorial() const {
        return historial.obtenerTamanio();
    }
    
    // Limpiar todo el historial
    void limpiarHistorial() {
        historial.limpiar();
        paginaActual = nullptr;
    }
    
    bool historialVacio() const {
        return historial.estaVacia();
    }
};

#endif