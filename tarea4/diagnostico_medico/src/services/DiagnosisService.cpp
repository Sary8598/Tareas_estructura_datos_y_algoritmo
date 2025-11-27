#include "services/DiagnosisService.h"
#include <sstream>

DiagnosisService::DiagnosisService(DecisionTreeRepository* repo) 
    : repository(repo), currentNode(nullptr) {}

DiagnosisService::~DiagnosisService() {
    delete repository;
}

void DiagnosisService::setupDefaultTree() {
    repository->setupMedicalDecisionTree();
    currentNode = nullptr;
}

std::string DiagnosisService::displayDecisionTree() const {
    return repository->getTreeStructure();
}

std::string DiagnosisService::getTreeInfo() const {
    std::stringstream ss;
    ss << "Informacion del Arbol de Decision:\n";
    ss << "• Total de nodos: " << repository->getNodeCount() << "\n";
    ss << "• Estado: ";
    
    if (repository->isTreeEmpty()) {
        ss << "Arbol no configurado";
    } else {
        ss << "Arbol listo para diagnostico";
    }
    
    ss << "\n• Diagnostico en curso: ";
    if (isDiagnosisInProgress()) {
        ss << "Si";
    } else {
        ss << "No";
    }
    
    return ss.str();
}

void DiagnosisService::startDiagnosis() {
    currentNode = repository->getRootNode();
}

bool DiagnosisService::answerYes() {
    if (currentNode == nullptr || !currentNode->isQuestion()) {
        return false;
    }
    
    DecisionNode* nextNode = repository->navigateYes(currentNode);
    if (nextNode != nullptr) {
        currentNode = nextNode;
        return true;
    }
    
    return false;
}

bool DiagnosisService::answerNo() {
    if (currentNode == nullptr || !currentNode->isQuestion()) {
        return false;
    }
    
    DecisionNode* nextNode = repository->navigateNo(currentNode);
    if (nextNode != nullptr) {
        currentNode = nextNode;
        return true;
    }
    
    return false;
}

bool DiagnosisService::isDiagnosisComplete() const {
    return currentNode != nullptr && currentNode->isDiagnosisNode();
}

bool DiagnosisService::isDiagnosisInProgress() const {
    return currentNode != nullptr;
}

std::string DiagnosisService::getCurrentQuestion() const {
    if (currentNode == nullptr) {
        return "No hay diagnostico en curso. Inicie uno primero.";
    }
    
    if (currentNode->isQuestion()) {
        return currentNode->getQuestion();
    } else {
        return "Diagnostico completado: " + currentNode->getDiagnosis();
    }
}

std::string DiagnosisService::getCurrentDiagnosis() const {
    if (currentNode == nullptr || !currentNode->isDiagnosisNode()) {
        return "";
    }
    return currentNode->getDiagnosis();
}

void DiagnosisService::resetDiagnosis() {
    currentNode = nullptr;
}

int DiagnosisService::getTreeSize() const {
    return repository->getNodeCount();
}

bool DiagnosisService::isTreeReady() const {
    return !repository->isTreeEmpty();
}