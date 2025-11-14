#ifndef VALIDADOR_URL_SERVICIO_H
#define VALIDADOR_URL_SERVICIO_H

#include <cstring>

// Servicio: Validador de URLs
class ValidadorURLServicio {
public:
    bool esURLValida(const char* url) const {
        if (url == nullptr || strlen(url) == 0) {
            return false;
        }
        
        if (strlen(url) > 200) {
            return false;
        }
        
        // Verificar que comience con protocolo o sea una URL valida
        if (strncmp(url, "http://", 7) == 0 ||
            strncmp(url, "https://", 8) == 0 ||
            strncmp(url, "www.", 4) == 0 ||
            strchr(url, '.') != nullptr) {
            return true;
        }
        
        return false;
    }
};

#endif