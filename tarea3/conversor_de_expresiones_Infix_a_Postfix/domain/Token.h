#ifndef TOKEN_H
#define TOKEN_H

// Entidad: Token - Representa un elemento de la expresion
struct Token {
    char valor;
    bool esOperador;
    bool esParentesis;
};

#endif