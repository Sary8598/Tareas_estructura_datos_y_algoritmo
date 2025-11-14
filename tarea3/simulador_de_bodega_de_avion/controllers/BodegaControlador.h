#ifndef BODEGA_CONTROLADOR_H
#define BODEGA_CONTROLADOR_H

#include "../services/BodegaServicio.h"
#include <cstring>
#include <cstdio>

// Estructura para respuesta del controlador
struct RespuestaControlador {
    bool exito;
    char mensaje[300];
    int datos;
};

class BodegaControlador {
private:
    BodegaServicio servicio;
    
public:
    RespuestaControlador procesarAgregar(const char* identificador) {
        RespuestaControlador respuesta;
        respuesta.datos = 0;
        
        bool exito = servicio.agregarMaleta(identificador);
        
        if (exito) {
            respuesta.exito = true;
            sprintf(respuesta.mensaje, "Maleta %s agregada exitosamente.", identificador);
        } else {
            respuesta.exito = false;
            sprintf(respuesta.mensaje, "Error: No se pudo agregar la maleta %s (puede estar duplicada o ser invalida).", identificador);
        }
        
        return respuesta;
    }
    
    RespuestaControlador procesarRetirar(const char* identificador) {
        RespuestaControlador respuesta;
        
        ResultadoRetiro resultado = servicio.retirarMaleta(identificador);
        
        respuesta.exito = resultado.exito;
        respuesta.datos = resultado.maniobras;
        strcpy(respuesta.mensaje, resultado.mensaje);
        
        return respuesta;
    }
    
    RespuestaControlador procesarMostrar(char listaMaletas[][50], int& cantidad) {
        RespuestaControlador respuesta;
        cantidad = servicio.obtenerCantidadMaletas();
        
        if (cantidad == 0) {
            respuesta.exito = true;
            strcpy(respuesta.mensaje, "La bodega esta vacia.");
            respuesta.datos = 0;
            return respuesta;
        }
        
        // Obtener maletas desde el fondo hasta el tope
        for (int i = 0; i < cantidad; i++) {
            Maleta maleta;
            if (servicio.obtenerMaletaEnPosicion(i, maleta)) {
                strcpy(listaMaletas[i], maleta.obtenerIdentificador());
            }
        }
        
        respuesta.exito = true;
        sprintf(respuesta.mensaje, "Bodega con %d maleta(s).", cantidad);
        respuesta.datos = cantidad;
        
        return respuesta;
    }
    
    RespuestaControlador procesarLimpiar() {
        RespuestaControlador respuesta;
        
        servicio.limpiarBodega();
        
        respuesta.exito = true;
        strcpy(respuesta.mensaje, "Bodega limpiada exitosamente.");
        respuesta.datos = 0;
        
        return respuesta;
    }
    
    bool bodegaEstaVacia() const {
        return servicio.estaVacia();
    }
};

#endif