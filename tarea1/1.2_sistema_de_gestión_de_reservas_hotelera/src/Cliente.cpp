#include "Cliente.h"
#include <iostream>

Cliente::Cliente() : nombre(""), cedula(""), telefono("") {}

Cliente::Cliente(const std::string& nombre, const std::string& cedula, const std::string& telefono)
    : nombre(nombre), cedula(cedula), telefono(telefono) {}

const std::string& Cliente::getNombre() const {
    return nombre;
}

const std::string& Cliente::getCedula() const {
    return cedula;
}

const std::string& Cliente::getTelefono() const {
    return telefono;
}

void Cliente::mostrarInfo() const {
    std::cout << "Cliente: " << nombre << " | Cedula: " << cedula << " | Tel: " << telefono;
}