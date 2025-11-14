#ifndef NODO_H
#define NODO_H

#include "PaginaWeb.h"

// Nodo de lista doble enlazada
template<typename T>
class Nodo {
public:
    T dato;
    Nodo<T>* siguiente;
    Nodo<T>* anterior;
    
    Nodo() : siguiente(nullptr), anterior(nullptr) {}
    
    Nodo(const T& valor) : dato(valor), siguiente(nullptr), anterior(nullptr) {}
};

#endif