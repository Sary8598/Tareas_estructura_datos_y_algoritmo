#ifndef PRECEDENCIA_SERVICIO_H
#define PRECEDENCIA_SERVICIO_H

// Servicio: Gestor de precedencia de operadores
class PrecedenciaServicio {
public:
    int obtenerPrecedencia(char operador) const {
        switch(operador) {
            case '^': return 3;
            case '*':
            case '/': return 2;
            case '+':
            case '-': return 1;
            default: return 0;
        }
    }
    
    bool esAsociativoIzquierda(char operador) const {
        return operador != '^';
    }
    
    bool tieneMayorPrecedencia(char op1, char op2) const {
        int prec1 = obtenerPrecedencia(op1);
        int prec2 = obtenerPrecedencia(op2);
        
        if (prec1 > prec2) {
            return true;
        }
        if (prec1 == prec2 && esAsociativoIzquierda(op1)) {
            return true;
        }
        return false;
    }
};

#endif