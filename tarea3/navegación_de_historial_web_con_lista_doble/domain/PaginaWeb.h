#ifndef PAGINA_WEB_H
#define PAGINA_WEB_H

#include <cstring>

// Entidad: PaginaWeb - Representa una pagina visitada
class PaginaWeb {
private:
    static const int MAX_URL = 200;
    static const int MAX_FECHA = 30;
    char url[MAX_URL];
    char fechaHora[MAX_FECHA];
    
public:
    PaginaWeb() {
        url[0] = '\0';
        fechaHora[0] = '\0';
    }
    
    PaginaWeb(const char* urlParam, const char* fechaParam) {
        establecerURL(urlParam);
        establecerFechaHora(fechaParam);
    }
    
    void establecerURL(const char* urlParam) {
        if (urlParam != nullptr) {
            strncpy(url, urlParam, MAX_URL - 1);
            url[MAX_URL - 1] = '\0';
        }
    }
    
    void establecerFechaHora(const char* fechaParam) {
        if (fechaParam != nullptr) {
            strncpy(fechaHora, fechaParam, MAX_FECHA - 1);
            fechaHora[MAX_FECHA - 1] = '\0';
        }
    }
    
    const char* obtenerURL() const {
        return url;
    }
    
    const char* obtenerFechaHora() const {
        return fechaHora;
    }
    
    bool esIgualURL(const char* urlParam) const {
        return strcmp(url, urlParam) == 0;
    }
    
    bool esVacia() const {
        return url[0] == '\0';
    }
};

#endif