#ifndef CONSULTORIO_CONTROLADOR_H
#define CONSULTORIO_CONTROLADOR_H

#include "../services/TriageServicio.h"
#include "../services/MedidorTiempoServicio.h"
#include <cstring>
#include <cstdio>

// Estructura de respuesta
struct RespuestaConsultorio {
    bool exito;
    char mensaje[300];
    double tiempoEjecucion;
    int datos;
};

class ConsultorioControlador {
private:
    TriageServicio servicio;
    MedidorTiempoServicio medidor;
    
public:
    // Registrar nuevo paciente
    RespuestaConsultorio procesarNuevoPaciente(const char* nombre, const char* sintoma) {
        RespuestaConsultorio respuesta;
        
        medidor.iniciar();
        bool exito = servicio.registrarPaciente(nombre, sintoma);
        respuesta.tiempoEjecucion = medidor.detener();
        
        respuesta.exito = exito;
        
        if (exito) {
            int ficha = servicio.obtenerTotalFichasGeneradas();
            sprintf(respuesta.mensaje, 
                    "Paciente '%s' registrado. Ficha: #%d - Sintoma: %s", 
                    nombre, ficha, sintoma);
            respuesta.datos = ficha;
        } else {
            sprintf(respuesta.mensaje, "Error: Datos invalidos para el paciente.");
            respuesta.datos = 0;
        }
        
        return respuesta;
    }
    
    // Atender siguiente paciente
    RespuestaConsultorio procesarAtender() {
        RespuestaConsultorio respuesta;
        Paciente pacienteAtendido;
        
        medidor.iniciar();
        bool exito = servicio.atenderPaciente(pacienteAtendido);
        respuesta.tiempoEjecucion = medidor.detener();
        
        respuesta.exito = exito;
        
        if (exito) {
            sprintf(respuesta.mensaje, 
                    "Paciente atendido: %s - %s", 
                    pacienteAtendido.obtenerNombre(),
                    pacienteAtendido.obtenerSintoma());
            respuesta.datos = pacienteAtendido.obtenerNumeroFicha();
        } else {
            sprintf(respuesta.mensaje, "No hay pacientes en la sala de espera.");
            respuesta.datos = 0;
        }
        
        return respuesta;
    }
    
    // Mostrar lista de espera
    RespuestaConsultorio procesarListaEspera(InfoPacienteEnEspera pacientes[], int& cantidad) {
        RespuestaConsultorio respuesta;
        
        medidor.iniciar();
        servicio.obtenerListaEspera(pacientes, cantidad);
        respuesta.tiempoEjecucion = medidor.detener();
        
        respuesta.exito = true;
        respuesta.datos = cantidad;
        
        if (cantidad == 0) {
            sprintf(respuesta.mensaje, "No hay pacientes en la sala de espera.");
        } else {
            sprintf(respuesta.mensaje, "Pacientes en espera: %d", cantidad);
        }
        
        return respuesta;
    }
    
    // Ver siguiente sin atender
    RespuestaConsultorio procesarVerSiguiente() {
        RespuestaConsultorio respuesta;
        Paciente siguiente;
        
        medidor.iniciar();
        bool exito = servicio.verSiguientePaciente(siguiente);
        respuesta.tiempoEjecucion = medidor.detener();
        
        respuesta.exito = exito;
        
        if (exito) {
            sprintf(respuesta.mensaje, 
                    "Siguiente: %s - %s (Ficha #%d)", 
                    siguiente.obtenerNombre(),
                    siguiente.obtenerSintoma(),
                    siguiente.obtenerNumeroFicha());
            respuesta.datos = siguiente.obtenerNumeroFicha();
        } else {
            sprintf(respuesta.mensaje, "No hay pacientes en espera.");
            respuesta.datos = 0;
        }
        
        return respuesta;
    }
    
    RespuestaConsultorio procesarLimpiar() {
        RespuestaConsultorio respuesta;
        
        medidor.iniciar();
        servicio.limpiarCola();
        respuesta.tiempoEjecucion = medidor.detener();
        
        respuesta.exito = true;
        respuesta.datos = 0;
        sprintf(respuesta.mensaje, "Lista de espera limpiada.");
        
        return respuesta;
    }
    
    RespuestaConsultorio procesarReiniciar() {
        RespuestaConsultorio respuesta;
        
        medidor.iniciar();
        servicio.reiniciarSistema();
        respuesta.tiempoEjecucion = medidor.detener();
        
        respuesta.exito = true;
        respuesta.datos = 0;
        sprintf(respuesta.mensaje, "Sistema reiniciado completamente.");
        
        return respuesta;
    }
    
    // Estadísticas
    int obtenerCantidadEnEspera() const {
        return servicio.obtenerCantidadEnEspera();
    }
    
    int obtenerTotalFichasGeneradas() const {
        return servicio.obtenerTotalFichasGeneradas();
    }
    
    int obtenerTotalPacientesAtendidos() const {
        return servicio.obtenerTotalPacientesAtendidos();
    }
    
    double obtenerTiempoTotalEjecucion() const {
        return medidor.obtenerTiempoTotal();
    }
};

#endif