#ifndef VISTA_CONSOLA_H
#define VISTA_CONSOLA_H

#include "../controllers/ConversionControlador.h"
#include <iostream>
using namespace std;

class VistaConsola {
private:
    static const int MAX_EXPRESION = 500;
    
    void mostrarBienvenida() const {
        cout << "========================================" << endl;
        cout << "  CONVERSOR INFIX A POSTFIX" << endl;
        cout << "  Algoritmo Shunting Yard" << endl;
        cout << "========================================" << endl;
        cout << endl;
    }
    
    void mostrarInstrucciones() const {
        cout << "Instrucciones:" << endl;
        cout << "- Use operadores: +, -, *, /, ^" << endl;
        cout << "- Use parentesis: ( )" << endl;
        cout << "- Use operandos: A-Z, a-z, 0-9" << endl;
        cout << endl;
        mostrarEjemplos();
    }
    
    void mostrarEjemplos() const {
        cout << "EJEMPLOS DE USO:" << endl;
        cout << "----------------------------------------" << endl;
        cout << "1. Expresion simple:" << endl;
        cout << "   Infix:   A + B" << endl;
        cout << "   Postfix: A B +" << endl;
        cout << endl;
    }
    
    void leerExpresion(char expresion[]) const {
        cout << "Ingrese la expresion infija: ";
        cin.getline(expresion, MAX_EXPRESION);
    }
    
    void mostrarResultado(const char entrada[], const char salida[]) const {
        cout << endl;
        cout << "========================================" << endl;
        cout << "RESULTADO:" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Expresion Infija:  " << entrada << endl;
        cout << "Expresion Postfija: " << salida << endl;
        cout << "========================================" << endl;
        cout << endl;
    }
    
    void mostrarError() const {
        cout << endl;
        cout << "Error: No se pudo procesar la expresion." << endl;
        cout << endl;
    }
    
    bool preguntarContinuar() const {
        char respuesta;
        cout << "¿Desea convertir otra expresion? (s/n): ";
        cin >> respuesta;
        cin.ignore();
        cout << endl;
        
        return respuesta == 's' || respuesta == 'S';
    }
    
public:
    void ejecutar() {
        ConversionControlador controlador;
        char expresionInfija[MAX_EXPRESION];
        char expresionPostfija[MAX_EXPRESION];
        bool continuar = true;
        
        mostrarBienvenida();
        mostrarInstrucciones();
        
        while (continuar) {
            leerExpresion(expresionInfija);
            
            bool exito = controlador.procesarConversion(expresionInfija, expresionPostfija);
            
            if (exito) {
                mostrarResultado(expresionInfija, expresionPostfija);
            } else {
                mostrarError();
            }
            
            continuar = preguntarContinuar();
        }
        
        cout << "Gracias por usar el conversor. ¡Hasta pronto!" << endl;
    }
};

#endif