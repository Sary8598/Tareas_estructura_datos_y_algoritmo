#pragma once
#include <string>

class Cliente {
private:
    std::string nombre;
    std::string cedula;
    std::string telefono;

public:
    Cliente();
    Cliente(const std::string& nombre, const std::string& cedula, const std::string& telefono);
    
    const std::string& getNombre() const;
    const std::string& getCedula() const;
    const std::string& getTelefono() const;
    
    void mostrarInfo() const;
};