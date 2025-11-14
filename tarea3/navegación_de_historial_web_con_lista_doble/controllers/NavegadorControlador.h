#ifndef NAVEGADOR_CONTROLADOR_H
#define NAVEGADOR_CONTROLADOR_H

#include "../services/HistorialServicio.h"
#include "../services/MedidorTiempoServicio.h"
#include <cstring>
#include <cstdio>

// Estructura de respuesta con tiempo
struct RespuestaNavegador {
    bool exito;
    char mensaje[300];
    double tiempoEjecucion;
    int datos;
};

class NavegadorControlador {
private:
    HistorialServicio servicio;
    MedidorTiempoServicio medidor;
    
public:
    RespuestaNavegador procesarVisitar(const char* url) {
        RespuestaNavegador respuesta;
        
        medidor.iniciar();
        bool exito = servicio.visitarPagina(url);
        respuesta.tiempoEjecucion = medidor.detener();
        
        respuesta.exito = exito;
        respuesta.datos = 0;
        
        if (exito) {
            sprintf(respuesta.mensaje, "Pagina visitada: %s", url);
        } else {
            sprintf(respuesta.mensaje, "Error: URL invalida o no se pudo agregar.");
        }
        
        return respuesta;
    }
    
    RespuestaNavegador procesarAtras() {
        RespuestaNavegador respuesta;
        
        medidor.iniciar();
        bool exito = servicio.irAtras();
        respuesta.tiempoEjecucion = medidor.detener();
        
        respuesta.exito = exito;
        respuesta.datos = 0;
        
        if (exito) {
            const PaginaWeb* actual = servicio.obtenerPaginaActual();
            if (actual != nullptr) {
                sprintf(respuesta.mensaje, "Navegado hacia atras: %s", actual->obtenerURL());
            }
        } else {
            sprintf(respuesta.mensaje, "No hay paginas anteriores en el historial.");
        }
        
        return respuesta;
    }
    
    RespuestaNavegador procesarAdelante() {
        RespuestaNavegador respuesta;
        
        medidor.iniciar();
        bool exito = servicio.irAdelante();
        respuesta.tiempoEjecucion = medidor.detener();
        
        respuesta.exito = exito;
        respuesta.datos = 0;
        
        if (exito) {
            const PaginaWeb* actual = servicio.obtenerPaginaActual();
            if (actual != nullptr) {
                sprintf(respuesta.mensaje, "Navegado hacia adelante: %s", actual->obtenerURL());
            }
        } else {
            sprintf(respuesta.mensaje, "No hay paginas siguientes en el historial.");
        }
        
        return respuesta;
    }
    
    RespuestaNavegador procesarEliminar(const char* url) {
        RespuestaNavegador respuesta;
        
        medidor.iniciar();
        bool exito = servicio.eliminarURL(url);
        respuesta.tiempoEjecucion = medidor.detener();
        
        respuesta.exito = exito;
        respuesta.datos = 0;
        
        if (exito) {
            sprintf(respuesta.mensaje, "URL eliminada del historial: %s", url);
        } else {
            sprintf(respuesta.mensaje, "URL no encontrada en el historial.");
        }
        
        return respuesta;
    }
    
    RespuestaNavegador procesarMostrar(PaginaWeb paginas[], int& cantidad) {
        RespuestaNavegador respuesta;
        
        medidor.iniciar();
        servicio.obtenerHistorialInverso(paginas, cantidad);
        respuesta.tiempoEjecucion = medidor.detener();
        
        respuesta.exito = true;
        respuesta.datos = cantidad;
        
        if (cantidad == 0) {
            sprintf(respuesta.mensaje, "El historial esta vacio.");
        } else {
            sprintf(respuesta.mensaje, "Historial con %d pagina(s).", cantidad);
        }
        
        return respuesta;
    }
    
    RespuestaNavegador procesarLimpiar() {
        RespuestaNavegador respuesta;
        
        medidor.iniciar();
        servicio.limpiarHistorial();
        respuesta.tiempoEjecucion = medidor.detener();
        
        respuesta.exito = true;
        respuesta.datos = 0;
        sprintf(respuesta.mensaje, "Historial limpiado completamente.");
        
        return respuesta;
    }
    
    const PaginaWeb* obtenerPaginaActual() const {
        return servicio.obtenerPaginaActual();
    }
    
    bool puedeIrAtras() const {
        return servicio.puedeIrAtras();
    }
    
    bool puedeIrAdelante() const {
        return servicio.puedeIrAdelante();
    }
    
    double obtenerTiempoTotalEjecucion() const {
        return medidor.obtenerTiempoTotal();
    }
};

#endif