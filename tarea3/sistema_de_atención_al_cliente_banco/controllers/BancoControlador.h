#ifndef BANCO_CONTROLADOR_H
#define BANCO_CONTROLADOR_H

#include "../services/TurnosServicio.h"
#include "../services/MedidorTiempoServicio.h"
#include <cstring>
#include <cstdio>

// Estructura de respuesta
struct RespuestaBanco {
    bool exito;
    char mensaje[300];
    double tiempoEjecucion;
    int datos;
};

class BancoControlador {
private:
    TurnosServicio servicio;
    MedidorTiempoServicio medidor;
    
public:
    // Registrar nuevo cliente
    RespuestaBanco procesarRegistrar(const char* nombre, const char* asunto) {
        RespuestaBanco respuesta;
        
        medidor.iniciar();
        bool exito = servicio.registrarCliente(nombre, asunto);
        respuesta.tiempoEjecucion = medidor.detener();
        
        respuesta.exito = exito;
        
        if (exito) {
            int turno = servicio.obtenerTotalTurnosGenerados();
            sprintf(respuesta.mensaje, 
                    "Cliente '%s' registrado. Turno: #%d - Asunto: %s", 
                    nombre, turno, asunto);
            respuesta.datos = turno;
        } else {
            sprintf(respuesta.mensaje, "Error: Datos invalidos para el cliente.");
            respuesta.datos = 0;
        }
        
        return respuesta;
    }
    
    // Atender siguiente cliente
    RespuestaBanco procesarAtender() {
        RespuestaBanco respuesta;
        Cliente clienteAtendido;
        
        medidor.iniciar();
        bool exito = servicio.atenderCliente(clienteAtendido);
        respuesta.tiempoEjecucion = medidor.detener();
        
        respuesta.exito = exito;
        
        if (exito) {
            sprintf(respuesta.mensaje, 
                    "Atendiendo a %s: %s (Turno #%d)", 
                    clienteAtendido.obtenerNombre(),
                    clienteAtendido.obtenerAsunto(),
                    clienteAtendido.obtenerNumeroTurno());
            respuesta.datos = clienteAtendido.obtenerNumeroTurno();
        } else {
            sprintf(respuesta.mensaje, "No hay clientes en espera.");
            respuesta.datos = 0;
        }
        
        return respuesta;
    }
    
    // Mostrar fila completa
    RespuestaBanco procesarMostrar(InfoClienteEnFila clientes[], int& cantidad) {
        RespuestaBanco respuesta;
        
        medidor.iniciar();
        servicio.obtenerFilaCompleta(clientes, cantidad);
        respuesta.tiempoEjecucion = medidor.detener();
        
        respuesta.exito = true;
        respuesta.datos = cantidad;
        
        if (cantidad == 0) {
            sprintf(respuesta.mensaje, "No hay clientes en la fila.");
        } else {
            sprintf(respuesta.mensaje, "Clientes en fila: %d", cantidad);
        }
        
        return respuesta;
    }
    
    // Ver siguiente sin atender
    RespuestaBanco procesarVerSiguiente() {
        RespuestaBanco respuesta;
        Cliente siguiente;
        
        medidor.iniciar();
        bool exito = servicio.verSiguienteCliente(siguiente);
        respuesta.tiempoEjecucion = medidor.detener();
        
        respuesta.exito = exito;
        
        if (exito) {
            sprintf(respuesta.mensaje, 
                    "Siguiente: %s - %s (Turno #%d)", 
                    siguiente.obtenerNombre(),
                    siguiente.obtenerAsunto(),
                    siguiente.obtenerNumeroTurno());
            respuesta.datos = siguiente.obtenerNumeroTurno();
        } else {
            sprintf(respuesta.mensaje, "No hay clientes en espera.");
            respuesta.datos = 0;
        }
        
        return respuesta;
    }
    
    RespuestaBanco procesarLimpiar() {
        RespuestaBanco respuesta;
        
        medidor.iniciar();
        servicio.limpiarCola();
        respuesta.tiempoEjecucion = medidor.detener();
        
        respuesta.exito = true;
        respuesta.datos = 0;
        sprintf(respuesta.mensaje, "Cola de turnos limpiada.");
        
        return respuesta;
    }
    
    RespuestaBanco procesarReiniciar() {
        RespuestaBanco respuesta;
        
        medidor.iniciar();
        servicio.reiniciarSistema();
        respuesta.tiempoEjecucion = medidor.detener();
        
        respuesta.exito = true;
        respuesta.datos = 0;
        sprintf(respuesta.mensaje, "Sistema reiniciado completamente.");
        
        return respuesta;
    }
    
    // Estadísticas
    int obtenerCantidadEnFila() const {
        return servicio.obtenerCantidadEnFila();
    }
    
    int obtenerTotalTurnosGenerados() const {
        return servicio.obtenerTotalTurnosGenerados();
    }
    
    int obtenerTotalClientesAtendidos() const {
        return servicio.obtenerTotalClientesAtendidos();
    }
    
    double obtenerTiempoTotalEjecucion() const {
        return medidor.obtenerTiempoTotal();
    }
};

#endif