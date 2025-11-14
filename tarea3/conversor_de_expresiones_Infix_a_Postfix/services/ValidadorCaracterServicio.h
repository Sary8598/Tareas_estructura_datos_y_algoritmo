#ifndef VALIDADOR_CARACTER_SERVICIO_H
#define VALIDADOR_CARACTER_SERVICIO_H

// Servicio: Validador de caracteres
class ValidadorCaracterServicio {
public:
    bool esOperando(char c) const {
        return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
    }
    
    bool esOperador(char c) const {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
    }
    
    bool esParentesisApertura(char c) const {
        return c == '(';
    }
    
    bool esParentesisCierre(char c) const {
        return c == ')';
    }
    
    bool esEspacioBlanco(char c) const {
        return c == ' ' || c == '\t' || c == '\n';
    }
};

#endif