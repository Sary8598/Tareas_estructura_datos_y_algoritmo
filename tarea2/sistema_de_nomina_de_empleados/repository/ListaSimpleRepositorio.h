#ifndef LISTA_SIMPLE_REPOSITORIO_H
#define LISTA_SIMPLE_REPOSITORIO_H

#include "../domain/Nodo.h"

// Repositorio: Lista Simplemente Enlazada
template<typename T>
class ListaSimpleRepositorio {
private:
    Nodo<T>* cabeza;
    int tamanio;
    
public:
    ListaSimpleRepositorio() : cabeza(nullptr), tamanio(0) {}
    
    ~ListaSimpleRepositorio() {
        limpiar();
    }
    
    bool estaVacia() const {
        return cabeza == nullptr;
    }
    
    int obtenerTamanio() const {
        return tamanio;
    }
    
    // Insertar al inicio (requisito 1)
    bool insertarAlInicio(const T& dato) {
        Nodo<T>* nuevoNodo = new Nodo<T>(dato);
        
        if (nuevoNodo == nullptr) {
            return false;
        }
        
        nuevoNodo->siguiente = cabeza;
        cabeza = nuevoNodo;
        tamanio++;
        
        return true;
    }
    
    // Obtener cabeza
    Nodo<T>* obtenerCabeza() const {
        return cabeza;
    }
    
    // Recorrer lista y aplicar función
    template<typename Funcion>
    void recorrer(Funcion func) const {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            func(actual->dato);
            actual = actual->siguiente;
        }
    }
    
    // Limpiar toda la lista
    void limpiar() {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            Nodo<T>* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
        cabeza = nullptr;
        tamanio = 0;
    }
};

#endif