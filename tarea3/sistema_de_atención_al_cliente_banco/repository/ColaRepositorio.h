#ifndef COLA_REPOSITORIO_H
#define COLA_REPOSITORIO_H

#include "../domain/Nodo.h"

// Repositorio: Cola (FIFO - First In First Out)
template<typename T>
class ColaRepositorio {
private:
    Nodo<T>* frente;
    Nodo<T>* final;
    int tamanio;
    
public:
    ColaRepositorio() : frente(nullptr), final(nullptr), tamanio(0) {}
    
    ~ColaRepositorio() {
        limpiar();
    }
    
    bool estaVacia() const {
        return frente == nullptr;
    }
    
    int obtenerTamanio() const {
        return tamanio;
    }
    
    // Encolar (agregar al final)
    bool encolar(const T& dato) {
        Nodo<T>* nuevoNodo = new Nodo<T>(dato);
        
        if (nuevoNodo == nullptr) {
            return false;
        }
        
        if (estaVacia()) {
            frente = final = nuevoNodo;
        } else {
            final->siguiente = nuevoNodo;
            final = nuevoNodo;
        }
        
        tamanio++;
        return true;
    }
    
    // Desencolar (remover del frente)
    bool desencolar(T& dato) {
        if (estaVacia()) {
            return false;
        }
        
        Nodo<T>* temp = frente;
        dato = frente->dato;
        frente = frente->siguiente;
        
        if (frente == nullptr) {
            final = nullptr;
        }
        
        delete temp;
        tamanio--;
        return true;
    }
    
    // Ver frente sin remover
    bool verFrente(T& dato) const {
        if (estaVacia()) {
            return false;
        }
        
        dato = frente->dato;
        return true;
    }
    
    // Recorrer cola (para mostrar)
    template<typename Funcion>
    void recorrer(Funcion func) const {
        Nodo<T>* actual = frente;
        while (actual != nullptr) {
            func(actual->dato);
            actual = actual->siguiente;
        }
    }
    
    // Limpiar toda la cola
    void limpiar() {
        T temp;
        while (!estaVacia()) {
            desencolar(temp);
        }
    }
};

#endif