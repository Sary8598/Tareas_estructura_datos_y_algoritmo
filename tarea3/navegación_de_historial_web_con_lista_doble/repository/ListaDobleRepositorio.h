#ifndef LISTA_DOBLE_REPOSITORIO_H
#define LISTA_DOBLE_REPOSITORIO_H

#include "../domain/Nodo.h"

// Repositorio: Lista Doblemente Enlazada
template<typename T>
class ListaDobleRepositorio {
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;
    int tamanio;
    
public:
    ListaDobleRepositorio() : cabeza(nullptr), cola(nullptr), tamanio(0) {}
    
    ~ListaDobleRepositorio() {
        limpiar();
    }
    
    bool estaVacia() const {
        return cabeza == nullptr;
    }
    
    int obtenerTamanio() const {
        return tamanio;
    }
    
    // Insertar al final (para nuevo historial)
    bool insertarAlFinal(const T& dato) {
        Nodo<T>* nuevoNodo = new Nodo<T>(dato);
        
        if (nuevoNodo == nullptr) {
            return false;
        }
        
        if (estaVacia()) {
            cabeza = cola = nuevoNodo;
        } else {
            cola->siguiente = nuevoNodo;
            nuevoNodo->anterior = cola;
            cola = nuevoNodo;
        }
        
        tamanio++;
        return true;
    }
    
    // Obtener nodo en posicion (0-indexed desde cabeza)
    Nodo<T>* obtenerNodoEnPosicion(int posicion) const {
        if (posicion < 0 || posicion >= tamanio) {
            return nullptr;
        }
        
        Nodo<T>* actual = cabeza;
        for (int i = 0; i < posicion && actual != nullptr; i++) {
            actual = actual->siguiente;
        }
        
        return actual;
    }
    
    // Eliminar nodo especifico
    bool eliminarNodo(Nodo<T>* nodo) {
        if (nodo == nullptr) {
            return false;
        }
        
        if (nodo->anterior != nullptr) {
            nodo->anterior->siguiente = nodo->siguiente;
        } else {
            cabeza = nodo->siguiente;
        }
        
        if (nodo->siguiente != nullptr) {
            nodo->siguiente->anterior = nodo->anterior;
        } else {
            cola = nodo->anterior;
        }
        
        delete nodo;
        tamanio--;
        return true;
    }
    
    // Obtener cabeza
    Nodo<T>* obtenerCabeza() const {
        return cabeza;
    }
    
    // Obtener cola
    Nodo<T>* obtenerCola() const {
        return cola;
    }
    
    // Limpiar toda la lista
    void limpiar() {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            Nodo<T>* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
        cabeza = cola = nullptr;
        tamanio = 0;
    }
};

#endif