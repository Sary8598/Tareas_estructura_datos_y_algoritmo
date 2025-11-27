#include "controllers/FamilyController.h"
#include <iostream>
#include <limits>

FamilyController::FamilyController(FamilyTreeService* familyService) 
    : service(familyService) {}

FamilyController::~FamilyController() {
    delete service;
}

void FamilyController::displayMenu() const {
    std::cout << "\n=== ÁRBOL GENEALÓGICO FAMILIAR ===\n";
    std::cout << "1. Agregar miembro familiar\n";
    std::cout << "2. Establecer persona raíz\n";
    std::cout << "3. Agregar relación padre/hijo\n";
    std::cout << "4. Agregar matrimonio\n";
    std::cout << "5. Ver árbol familiar\n";
    std::cout << "6. Información del árbol\n";
    std::cout << "7. Mostrar ayuda\n";
    std::cout << "8. Mostrar ejemplo\n";
    std::cout << "9. Salir\n";
    std::cout << "Seleccione una opción (1-9): ";
}

void FamilyController::processChoice(int choice) {
    switch (choice) {
        case 1:
            addFamilyMember();
            break;
        case 2:
            setRootPerson();
            break;
        case 3:
            addParentChild();
            break;
        case 4:
            addMarriage();
            break;
        case 5:
            viewFamilyTree();
            break;
        case 6:
            showTreeInfo();
            break;
        case 7:
            showHelp();
            break;
        case 8:
            showExample();
            break;
        case 9:
            std::cout << "Saliendo del sistema de árbol genealógico...\n";
            break;
        default:
            std::cout << "Opción inválida. Por favor seleccione 1-9.\n";
    }
}

void FamilyController::addFamilyMember() {
    std::string name, relationship;
    int age;
    
    std::cout << "Ingrese el nombre: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, name);
    
    if (name.empty()) {
        std::cout << "Error: El nombre no puede estar vacío\n";
        return;
    }
    
    std::cout << "Ingrese la edad: ";
    age = getValidatedAge();
    
    std::cout << "Ingrese la relación familiar (opcional, ej: Abuelo, Padre, etc.): ";
    std::getline(std::cin, relationship);
    
    if (service->addFamilyMember(name, age, relationship)) {
        std::cout << "Miembro familiar agregado: " << name << "\n";
    } else {
        std::cout << "Error: No se pudo agregar el miembro (nombre duplicado o límite alcanzado)\n";
    }
}

void FamilyController::setRootPerson() {
    std::string name;
    
    std::cout << "Ingrese el nombre de la persona raíz: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, name);
    
    if (service->setFamilyRoot(name)) {
        std::cout << "Persona raíz establecida: " << name << "\n";
    } else {
        std::cout << "Error: No se encontró la persona '" << name << "'\n";
    }
}

void FamilyController::addParentChild() {
    std::string parentName, childName;
    
    std::cout << "Ingrese el nombre del padre/madre: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, parentName);
    
    std::cout << "Ingrese el nombre del hijo/a: ";
    std::getline(std::cin, childName);
    
    if (service->addParentChild(parentName, childName)) {
        std::cout << "Relación padre-hijo establecida: " << parentName << " -> " << childName << "\n";
    } else {
        std::cout << "Error: No se pudo establecer la relación\n";
    }
}

void FamilyController::addMarriage() {
    std::string person1Name, person2Name;
    
    std::cout << "Ingrese el nombre del primer cónyuge: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, person1Name);
    
    std::cout << "Ingrese el nombre del segundo cónyuge: ";
    std::getline(std::cin, person2Name);
    
    if (service->addMarriage(person1Name, person2Name)) {
        std::cout << "Matrimonio establecido: " << person1Name << " " << person2Name << "\n";
    } else {
        std::cout << "Error: No se pudo establecer el matrimonio\n";
    }
}

void FamilyController::viewFamilyTree() {
    std::cout << "\n" << service->displayFamilyTree() << "\n";
}

void FamilyController::showTreeInfo() const {
    std::cout << "\n" << service->getTreeInfo() << "\n";
}

void FamilyController::showHelp() const {
    std::cout << "\n=== AYUDA - ÁRBOL GENEALÓGICO ===\n";
    std::cout << "Este sistema permite construir árboles genealógicos hasta el nivel de abuelos.\n\n";
    std::cout << "CONCEPTOS:\n";
    std::cout << "• Persona Raíz: El punto de partida del árbol (ej: el abuelo)\n";
    std::cout << "• Relaciones: Padre-Hijo y Matrimonio\n";
    std::cout << "• Recorrido Preorden: Raíz -> Hijos (de izquierda a derecha)\n\n";
    std::cout << "INSTRUCCIONES:\n";
    std::cout << "1. Agregue todos los miembros familiares\n";
    std::cout << "2. Establezca una persona raíz\n";
    std::cout << "3. Establezca las relaciones padre-hijo\n";
    std::cout << "4. Establezca los matrimonios\n";
    std::cout << "5. Visualice el árbol en preorden\n";
}

void FamilyController::showExample() const {
    std::cout << "\n=== EJEMPLO DE ÁRBOL GENEALÓGICO ===\n";
    std::cout << "Miembros:\n";
    std::cout << "• Juan (75) - Abuelo\n";
    std::cout << "• Maria (72) - Abuela\n";
    std::cout << "• Carlos (50) - Padre\n";
    std::cout << "• Ana (48)\n";
    std::cout << "• Pedro (25)\n";
    std::cout << "• Laura (22)\n\n";
    std::cout << "Relaciones:\n";
    std::cout << "• Raíz: Juan\n";
    std::cout << "• Matrimonio: Juan 💍 Maria\n";
    std::cout << "• Padre-Hijo: Juan -> Carlos\n";
    std::cout << "• Matrimonio: Carlos 💍 Ana\n";
    std::cout << "• Padre-Hijo: Carlos -> Pedro\n";
    std::cout << "• Padre-Hijo: Carlos -> Laura\n";
}

int FamilyController::getValidatedInput() const {
    int choice;
    std::cin >> choice;
    
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }
    
    return choice;
}

int FamilyController::getValidatedAge() const {
    int age;
    if (!(std::cin >> age) || age < 0 || age > 150) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return 0;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return age;
}

void FamilyController::run() {
    int choice = 0;
    
    std::cout << "Sistema de Árbol Genealógico Iniciado\n";
    
    do {
        displayMenu();
        choice = getValidatedInput();
        
        if (choice == -1) {
            std::cout << "❌ Entrada inválida. Por favor ingrese un número.\n";
            continue;
        }
        
        processChoice(choice);
        
    } while (choice != 9);
}
