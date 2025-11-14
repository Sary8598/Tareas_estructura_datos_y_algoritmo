#ifndef VALIDADOR_MALETA_SERVICIO_H
#define VALIDADOR_MALETA_SERVICIO_H

#include <cstring>

// Servicio: Validador de maletas
class ValidadorMaletaServicio {
public:
    bool esIdentificadorValido(const char* id) const {
        if (id == nullptr || strlen(id) == 0) {
            return false;
        }
        
        // Verificar que tenga al menos un caracter
        if (strlen(id) > 20) {
            return false;
        }
        
        // Verificar que no contenga espacios
        for (int i = 0; id[i] != '\0'; i++) {
            if (id[i] == ' ' || id[i] == '\t' || id[i] == '\n') {
                return false;
            }
        }
        
        return true;
    }
    
    bool esComandoValido(const char* comando) const {
        if (comando == nullptr) {
            return false;
        }
        
        return strcmp(comando, "agregar") == 0 ||
               strcmp(comando, "retirar") == 0 ||
               strcmp(comando, "mostrar") == 0 ||
               strcmp(comando, "limpiar") == 0 ||
               strcmp(comando, "salir") == 0;
    }
};

#endif