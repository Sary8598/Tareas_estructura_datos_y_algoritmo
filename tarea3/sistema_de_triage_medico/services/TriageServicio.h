#ifndef TRIAGE_SERVICIO_H
#define TRIAGE_SERVICIO_H

#include "../domain/Paciente.h"
#include "../repository/ColaRepositorio.h"
#include "ValidadorPacienteServicio.h"
#include <cstdio>

// Estructura para información de paciente en lista de espera
struct InfoPacienteEnEspera {
    char nombre[100];
    char sintoma[200];
    int numeroFicha;
    int posicionEnFila;
};

// Servicio: Gestor de triage médico (FIFO - Sin prioridad)
class TriageServicio {
private:
    ColaRepositorio<Paciente> colaPacientes;
    ValidadorPacienteServicio validador;
    int contadorFichas;
    int pacientesAtendidos;
    
public:
    TriageServicio() : contadorFichas(0), pacientesAtendidos(0) {}
    
    // Registrar nuevo paciente en la cola
    bool registrarPaciente(const char* nombre, const char* sintoma) {
        if (!validador.esPacienteValido(nombre, sintoma)) {
            return false;
        }
        
        contadorFichas++;
        Paciente nuevoPaciente(nombre, sintoma, contadorFichas);
        
        return colaPacientes.encolar(nuevoPaciente);
    }
    
    // Atender siguiente paciente (FIFO)
    bool atenderPaciente(Paciente& pacienteAtendido) {
        if (colaPacientes.estaVacia()) {
            return false;
        }
        
        bool exito = colaPacientes.desencolar(pacienteAtendido);
        
        if (exito) {
            pacientesAtendidos++;
        }
        
        return exito;
    }
    
    // Ver siguiente paciente sin atender
    bool verSiguientePaciente(Paciente& paciente) const {
        return colaPacientes.verFrente(paciente);
    }
    
    // Obtener lista completa de espera
    void obtenerListaEspera(InfoPacienteEnEspera pacientes[], int& cantidad) const {
        cantidad = 0;
        int posicion = 1;
        
        colaPacientes.recorrer([&pacientes, &cantidad, &posicion](const Paciente& paciente) {
            InfoPacienteEnEspera& info = pacientes[cantidad];
            
            strcpy(info.nombre, paciente.obtenerNombre());
            strcpy(info.sintoma, paciente.obtenerSintoma());
            info.numeroFicha = paciente.obtenerNumeroFicha();
            info.posicionEnFila = posicion;
            
            cantidad++;
            posicion++;
        });
    }
    
    int obtenerCantidadEnEspera() const {
        return colaPacientes.obtenerTamanio();
    }
    
    int obtenerTotalFichasGeneradas() const {
        return contadorFichas;
    }
    
    int obtenerTotalPacientesAtendidos() const {
        return pacientesAtendidos;
    }
    
    bool hayPacientesEnEspera() const {
        return !colaPacientes.estaVacia();
    }
    
    void limpiarCola() {
        colaPacientes.limpiar();
    }
    
    void reiniciarSistema() {
        colaPacientes.limpiar();
        contadorFichas = 0;
        pacientesAtendidos = 0;
    }
};

#endif