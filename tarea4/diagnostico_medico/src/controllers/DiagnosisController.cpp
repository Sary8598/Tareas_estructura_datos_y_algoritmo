#include "controllers/DiagnosisController.h"
#include <iostream>
#include <limits>
#include <cctype>

DiagnosisController::DiagnosisController(DiagnosisService* diagService) 
    : service(diagService) {}

DiagnosisController::~DiagnosisController() {
    delete service;
}

void DiagnosisController::displayMainMenu() const {
    std::cout << "\n=== SISTEMA DE DIAGNOSTICO MEDICO ===\n";
    std::cout << "1. Ver arbol de decision completo\n";
    std::cout << "2. Iniciar nuevo diagnostico\n";
    std::cout << "3. Informacion del sistema\n";
    std::cout << "4. Mostrar ayuda\n";
    std::cout << "5. Salir\n";
    std::cout << "Seleccione una opcion (1-5): ";
}

void DiagnosisController::displayDiagnosisMenu() const {
    std::cout << "\n--- DIAGNOSTICO EN CURSO ---\n";
    std::cout << "Pregunta actual:\n";
    std::cout << "  " << service->getCurrentQuestion() << "\n\n";
    std::cout << "1. Responder SI\n";
    std::cout << "2. Responder NO\n";
    std::cout << "3. Reiniciar diagnostico\n";
    std::cout << "4. Volver al menu principal\n";
    std::cout << "Seleccione una opcion (1-4): ";
}

void DiagnosisController::processMainChoice(int choice) {
    switch (choice) {
        case 1:
            viewDecisionTree();
            break;
        case 2:
            startNewDiagnosis();
            break;
        case 3:
            showTreeInfo();
            break;
        case 4:
            showHelp();
            break;
        case 5:
            std::cout << "Saliendo del sistema de diagnostico...\n";
            break;
        default:
            std::cout << "Opcion invalida. Por favor seleccione 1-5.\n";
    }
}

void DiagnosisController::processDiagnosisChoice(int choice) {
    switch (choice) {
        case 1:
            if (service->answerYes()) {
                if (service->isDiagnosisComplete()) {
                    std::cout << "\nDIAGNOSTICO COMPLETADO\n";
                    std::cout << service->getCurrentDiagnosis() << "\n";
                    std::cout << "\nRecuerde: Este es solo un diagnostico preliminar.\n";
                    std::cout << "   Consulte siempre con un profesional de la salud.\n";
                }
            } else {
                std::cout << "No se puede avanzar con la respuesta SI.\n";
            }
            break;
        case 2:
            if (service->answerNo()) {
                if (service->isDiagnosisComplete()) {
                    std::cout << "\nDIAGNOSTICO COMPLETADO\n";
                    std::cout << service->getCurrentDiagnosis() << "\n";
                    std::cout << "\nRecuerde: Este es solo un diagnostico preliminar.\n";
                    std::cout << "   Consulte siempre con un profesional de la salud.\n";
                }
            } else {
                std::cout << "No se puede avanzar con la respuesta NO.\n";
            }
            break;
        case 3:
            service->resetDiagnosis();
            std::cout << "Diagnostico reiniciado.\n";
            break;
        case 4:
            service->resetDiagnosis();
            std::cout << "Volviendo al menu principal...\n";
            break;
        default:
            std::cout << "Opcion invalida. Por favor seleccione 1-4.\n";
    }
}

void DiagnosisController::viewDecisionTree() {
    std::cout << "\n" << service->displayDecisionTree() << "\n";
}

void DiagnosisController::startNewDiagnosis() {
    if (!service->isTreeReady()) {
        std::cout << "El arbol de decision no esta configurado.\n";
        return;
    }
    
    service->startDiagnosis();
    std::cout << "\nINICIANDO DIAGNOSTICO MEDICO\n";
    std::cout << "Responda las preguntas con SI o NO\n";
    std::cout << "===================================\n";
    
    continueDiagnosis();
}

void DiagnosisController::continueDiagnosis() {
    int choice = 0;
    
    while (service->isDiagnosisInProgress() && !service->isDiagnosisComplete()) {
        displayDiagnosisMenu();
        choice = getValidatedInput();
        
        if (choice == 4) {
            break;
        }
        
        processDiagnosisChoice(choice);
        
        if (service->isDiagnosisComplete()) {
            std::cout << "\nPresione Enter para volver al menu principal...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        }
    }
}

void DiagnosisController::showTreeInfo() const {
    std::cout << "\n" << service->getTreeInfo() << "\n";
}

void DiagnosisController::showHelp() const {
    std::cout << "\n=== AYUDA - SISTEMA DE DIAGNOSTICO MEDICO ===\n";
    std::cout << "Este sistema utiliza un arbol de decision binario para\n";
    std::cout << "proporcionar diagnosticos medicos preliminares.\n\n";
    std::cout << "FUNCIONALIDADES:\n";
    std::cout << "• Ver arbol completo: Muestra toda la estructura de decision\n";
    std::cout << "• Diagnostico interactivo: Responde preguntas SI/NO\n";
    std::cout << "• Recorrido preorden: Muestra el flujo de decisiones\n\n";
    std::cout << "INSTRUCCIONES:\n";
    std::cout << "1. El sistema hace preguntas sobre sintomas\n";
    std::cout << "2. Responda SI o NO honestamente\n";
    std::cout << "3. Siga las preguntas hasta llegar a un diagnostico\n";
    std::cout << "4. El diagnostico es PRELIMINAR - consulte a un medico\n\n";
    std::cout << "ADVERTENCIA: Este es un sistema educativo.\n";
    std::cout << "    No sustituye la consulta con profesionales de la salud.\n";
}

int DiagnosisController::getValidatedInput() const {
    int choice;
    std::cin >> choice;
    
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }
    
    return choice;
}

char DiagnosisController::getYesNoInput() const {
    char response;
    std::cin >> response;
    response = std::toupper(response);
    
    if (response != 'S' && response != 'N') {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return 'X'; // Invalid
    }
    
    return response;
}

void DiagnosisController::run() {
    service->setupDefaultTree();
    
    int choice = 0;
    
    std::cout << "Sistema de Diagnostico Medico Iniciado\n";
    std::cout << "Arbol de decision configurado automaticamente.\n";
    
    do {
        displayMainMenu();
        choice = getValidatedInput();
        
        if (choice == -1) {
            std::cout << "Entrada invalida. Por favor ingrese un numero.\n";
            continue;
        }
        
        processMainChoice(choice);
        
    } while (choice != 5);
}