#ifndef CONVERSION_SERVICIO_H
#define CONVERSION_SERVICIO_H

#include "../repository/PilaRepositorio.h"
#include "ValidadorCaracterServicio.h"
#include "PrecedenciaServicio.h"
#include <cstring>

// Servicio: Conversor principal (Algoritmo Shunting Yard)
class ConversionServicio {
private:
    ValidadorCaracterServicio validador;
    PrecedenciaServicio precedencia;
    
    void procesarOperando(char c, char salida[], int& indiceSalida) const {
        salida[indiceSalida++] = c;
        salida[indiceSalida++] = ' ';
    }
    
    void procesarOperador(char c, PilaRepositorio<char>& pila, char salida[], int& indiceSalida) const {
        char tope;
        
        while (pila.verTope(tope) && tope != '(' && 
               precedencia.tieneMayorPrecedencia(tope, c)) {
            pila.desapilar(tope);
            salida[indiceSalida++] = tope;
            salida[indiceSalida++] = ' ';
        }
        
        pila.apilar(c);
    }
    
    void procesarParentesisApertura(PilaRepositorio<char>& pila) const {
        pila.apilar('(');
    }
    
    void procesarParentesisCierre(PilaRepositorio<char>& pila, char salida[], int& indiceSalida) const {
        char tope;
        
        while (pila.verTope(tope) && tope != '(') {
            pila.desapilar(tope);
            salida[indiceSalida++] = tope;
            salida[indiceSalida++] = ' ';
        }
        
        if (pila.verTope(tope) && tope == '(') {
            pila.desapilar(tope);
        }
    }
    
    void vaciarPila(PilaRepositorio<char>& pila, char salida[], int& indiceSalida) const {
        char tope;
        
        while (pila.verTope(tope)) {
            pila.desapilar(tope);
            if (tope != '(') {
                salida[indiceSalida++] = tope;
                salida[indiceSalida++] = ' ';
            }
        }
    }
    
public:
    bool convertirInfixAPostfix(const char entrada[], char salida[]) const {
        PilaRepositorio<char> pilaOperadores;
        int indiceSalida = 0;
        int i = 0;
        
        while (entrada[i] != '\0') {
            char caracterActual = entrada[i];
            
            if (validador.esEspacioBlanco(caracterActual)) {
                i++;
                continue;
            }
            
            if (validador.esOperando(caracterActual)) {
                procesarOperando(caracterActual, salida, indiceSalida);
            }
            else if (validador.esOperador(caracterActual)) {
                procesarOperador(caracterActual, pilaOperadores, salida, indiceSalida);
            }
            else if (validador.esParentesisApertura(caracterActual)) {
                procesarParentesisApertura(pilaOperadores);
            }
            else if (validador.esParentesisCierre(caracterActual)) {
                procesarParentesisCierre(pilaOperadores, salida, indiceSalida);
            }
            
            i++;
        }
        
        vaciarPila(pilaOperadores, salida, indiceSalida);
        
        if (indiceSalida > 0 && salida[indiceSalida - 1] == ' ') {
            indiceSalida--;
        }
        
        salida[indiceSalida] = '\0';
        return true;
    }
};

#endif