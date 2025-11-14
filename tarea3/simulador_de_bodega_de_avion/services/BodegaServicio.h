#ifndef BODEGA_SERVICIO_H
#define BODEGA_SERVICIO_H

#include "../domain/Maleta.h"
#include "../repository/PilaRepositorio.h"
#include "ValidadorMaletaServicio.h"

#include <cstring>
#include <cstdio>

// Resultado de operacion de retiro
struct ResultadoRetiro {
    bool exito;
    int maniobras;
    char mensaje[200];
};

// Servicio: Gestor de la bodega del avion
class BodegaServicio {
private:
    PilaRepositorio<Maleta> bodegaPrincipal;
    ValidadorMaletaServicio validador;
    
    int buscarPosicionMaleta(const char* id) const {
        int tamanio = bodegaPrincipal.obtenerTamanio();
        
        for (int i = 0; i < tamanio; i++) {
            Maleta maleta;
            if (bodegaPrincipal.obtenerElemento(i, maleta)) {
                if (maleta.esIgual(id)) {
                    return i;
                }
            }
        }
        
        return -1;
    }
    
    int calcularManiobrasPara(int posicion) const {
        int tamanio = bodegaPrincipal.obtenerTamanio();
        return tamanio - posicion - 1;
    }
    
public:
    bool agregarMaleta(const char* id) {
        if (!validador.esIdentificadorValido(id)) {
            return false;
        }
        
        // Verificar si ya existe
        if (buscarPosicionMaleta(id) != -1) {
            return false;
        }
        
        Maleta nuevaMaleta(id);
        return bodegaPrincipal.apilar(nuevaMaleta);
    }
    
    ResultadoRetiro retirarMaleta(const char* id) {
        ResultadoRetiro resultado;
        resultado.exito = false;
        resultado.maniobras = 0;
        strcpy(resultado.mensaje, "");
        
        if (!validador.esIdentificadorValido(id)) {
            strcpy(resultado.mensaje, "Identificador invalido.");
            return resultado;
        }
        
        int posicion = buscarPosicionMaleta(id);
        
        if (posicion == -1) {
            strcpy(resultado.mensaje, "Maleta no encontrada en la bodega.");
            return resultado;
        }
        
        // Pila auxiliar para maniobras
        PilaRepositorio<Maleta> pilaAuxiliar;
        resultado.maniobras = calcularManiobrasPara(posicion);
        
        // Mover maletas superiores a pila auxiliar
        for (int i = 0; i < resultado.maniobras; i++) {
            Maleta maletaTemporal;
            if (bodegaPrincipal.desapilar(maletaTemporal)) {
                pilaAuxiliar.apilar(maletaTemporal);
            }
        }
        
        // Retirar la maleta objetivo
        Maleta maletaObjetivo;
        bodegaPrincipal.desapilar(maletaObjetivo);
        
        // Devolver maletas desde pila auxiliar
        while (!pilaAuxiliar.estaVacia()) {
            Maleta maletaTemporal;
            pilaAuxiliar.desapilar(maletaTemporal);
            bodegaPrincipal.apilar(maletaTemporal);
        }
        
        resultado.exito = true;
        
        if (resultado.maniobras == 0) {
            sprintf(resultado.mensaje, "Maleta %s retirada sin maniobras.", id);
        } else if (resultado.maniobras == 1) {
            sprintf(resultado.mensaje, "Maleta %s retirada con 1 maniobra.", id);
        } else {
            sprintf(resultado.mensaje, "Maleta %s retirada con %d maniobras.", 
                    id, resultado.maniobras);
        }
        
        return resultado;
    }
    
    int obtenerCantidadMaletas() const {
        return bodegaPrincipal.obtenerTamanio();
    }
    
    bool obtenerMaletaEnPosicion(int posicion, Maleta& maleta) const {
        return bodegaPrincipal.obtenerElemento(posicion, maleta);
    }
    
    void limpiarBodega() {
        bodegaPrincipal.limpiar();
    }
    
    bool estaVacia() const {
        return bodegaPrincipal.estaVacia();
    }
};

#endif