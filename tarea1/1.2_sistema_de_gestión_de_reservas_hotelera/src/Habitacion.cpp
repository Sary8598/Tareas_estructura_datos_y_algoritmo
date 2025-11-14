#include "Habitacion.h"
#include <iostream>

Habitacion::Habitacion() : numero(0), tipo(TipoHabitacion::SENCILLA), precioPorNoche(0.0), ocupada(false) {}

Habitacion::Habitacion(int numero, TipoHabitacion tipo, double precio)
    : numero(numero), tipo(tipo), precioPorNoche(precio), ocupada(false) {}

int Habitacion::getNumero() const {
    return numero;
}

TipoHabitacion Habitacion::getTipo() const {
    return tipo;
}

double Habitacion::getPrecio() const {
    return precioPorNoche;
}

bool Habitacion::estaOcupada() const {
    return ocupada;
}

const Cliente& Habitacion::getCliente() const {
    return cliente;
}

void Habitacion::reservar(const Cliente& cliente) {
    this->cliente = cliente;
    ocupada = true;
}

void Habitacion::liberar() {
    cliente = Cliente();
    ocupada = false;
}

std::string Habitacion::getTipoString() const {
    switch (tipo) {
        case TipoHabitacion::SENCILLA: return "Sencilla";
        case TipoHabitacion::DOBLE: return "Doble";
        case TipoHabitacion::SUITE: return "Suite";
        default: return "Desconocido";
    }
}

void Habitacion::mostrarInfo() const {
    std::cout << "Hab. " << numero << " | " << getTipoString() 
              << " | $" << precioPorNoche << " | " 
              << (ocupada ? "OCUPADA" : "DISPONIBLE");
    if (ocupada) {
        std::cout << " | ";
        cliente.mostrarInfo();
    }
    std::cout << "\n";
}