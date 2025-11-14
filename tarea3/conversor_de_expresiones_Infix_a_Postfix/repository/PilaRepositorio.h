#ifndef PILA_REPOSITORIO_H
#define PILA_REPOSITORIO_H

// Implementacion de Pila usando arreglos
template<typename T>
class PilaRepositorio {
private:
    static const int MAX_SIZE = 100;
    T datos[MAX_SIZE];
    int tope;
    
public:
    PilaRepositorio() : tope(-1) {}
    
    bool estaVacia() const {
        return tope == -1;
    }
    
    bool estaLlena() const {
        return tope >= MAX_SIZE - 1;
    }
    
    bool apilar(T elemento) {
        if (estaLlena()) {
            return false;
        }
        datos[++tope] = elemento;
        return true;
    }
    
    bool desapilar(T& elemento) {
        if (estaVacia()) {
            return false;
        }
        elemento = datos[tope--];
        return true;
    }
    
    bool verTope(T& elemento) const {
        if (estaVacia()) {
            return false;
        }
        elemento = datos[tope];
        return true;
    }
    
    void limpiar() {
        tope = -1;
    }
};

#endif