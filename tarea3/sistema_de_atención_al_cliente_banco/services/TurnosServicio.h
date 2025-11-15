#ifndef TURNOS_SERVICIO_H
#define TURNOS_SERVICIO_H

#include "../domain/Cliente.h"
#include "../repository/ColaRepositorio.h"
#include "ValidadorClienteServicio.h"
#include <cstdio>

// Estructura para información de cliente en fila
struct InfoClienteEnFila {
    char nombre[100];
    char asunto[200];
    int numeroTurno;
    int posicionEnFila;
};

// Servicio: Gestor de turnos del banco (FIFO)
class TurnosServicio {
private:
    ColaRepositorio<Cliente> colaTurnos;
    ValidadorClienteServicio validador;
    int contadorTurnos;
    int clientesAtendidos;
    
public:
    TurnosServicio() : contadorTurnos(0), clientesAtendidos(0) {}
    
    // Registrar nuevo cliente en la cola
    bool registrarCliente(const char* nombre, const char* asunto) {
        if (!validador.esClienteValido(nombre, asunto)) {
            return false;
        }
        
        contadorTurnos++;
        Cliente nuevoCliente(nombre, asunto, contadorTurnos);
        
        return colaTurnos.encolar(nuevoCliente);
    }
    
    // Atender siguiente cliente (FIFO)
    bool atenderCliente(Cliente& clienteAtendido) {
        if (colaTurnos.estaVacia()) {
            return false;
        }
        
        bool exito = colaTurnos.desencolar(clienteAtendido);
        
        if (exito) {
            clientesAtendidos++;
        }
        
        return exito;
    }
    
    // Ver siguiente cliente sin atender
    bool verSiguienteCliente(Cliente& cliente) const {
        return colaTurnos.verFrente(cliente);
    }
    
    // Obtener todos los clientes en fila
    void obtenerFilaCompleta(InfoClienteEnFila clientes[], int& cantidad) const {
        cantidad = 0;
        int posicion = 1;
        
        colaTurnos.recorrer([&clientes, &cantidad, &posicion](const Cliente& cliente) {
            InfoClienteEnFila& info = clientes[cantidad];
            
            strcpy(info.nombre, cliente.obtenerNombre());
            strcpy(info.asunto, cliente.obtenerAsunto());
            info.numeroTurno = cliente.obtenerNumeroTurno();
            info.posicionEnFila = posicion;
            
            cantidad++;
            posicion++;
        });
    }
    
    int obtenerCantidadEnFila() const {
        return colaTurnos.obtenerTamanio();
    }
    
    int obtenerTotalTurnosGenerados() const {
        return contadorTurnos;
    }
    
    int obtenerTotalClientesAtendidos() const {
        return clientesAtendidos;
    }
    
    bool hayClientesEnEspera() const {
        return !colaTurnos.estaVacia();
    }
    
    void limpiarCola() {
        colaTurnos.limpiar();
        // No reiniciamos contadorTurnos para mantener historial
    }
    
    void reiniciarSistema() {
        colaTurnos.limpiar();
        contadorTurnos = 0;
        clientesAtendidos = 0;
    }
};

#endif