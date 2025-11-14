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
    
    bool apilar(const T& elemento) {
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
    
    int obtenerTamanio() const {
        return tope + 1;
    }
    
    void limpiar() {
        tope = -1;
    }
    
    // Metodo para acceder a elementos por indice (desde el fondo)
    bool obtenerElemento(int indice, T& elemento) const {
        if (indice < 0 || indice > tope) {
            return false;
        }
        elemento = datos[indice];
        return true;
    }
};

#endif