#include "services/FamilyTreeService.h"
#include <sstream>

FamilyTreeService::FamilyTreeService(FamilyRepository* repo) : repository(repo) {}

FamilyTreeService::~FamilyTreeService() {
    delete repository;
}

bool FamilyTreeService::addFamilyMember(const std::string& name, int age, const std::string& relationship) {
    return repository->addPerson(name, age, relationship);
}

bool FamilyTreeService::setFamilyRoot(const std::string& name) {
    return repository->setRootPerson(name);
}

bool FamilyTreeService::addParentChild(const std::string& parentName, const std::string& childName) {
    return repository->addParentChildRelationship(parentName, childName);
}

bool FamilyTreeService::addMarriage(const std::string& person1Name, const std::string& person2Name) {
    return repository->addSpouseRelationship(person1Name, person2Name);
}

std::string FamilyTreeService::displayFamilyTree() const {
    return repository->getFamilyTreeFormatted();
}

std::string FamilyTreeService::getTreeInfo() const {
    std::stringstream ss;
    ss << "Informacion del Arbol Familiar:\n";
    ss << "• Total de miembros: " << repository->getMemberCount() << "\n";
    ss << "• Persona raiz: ";
    
    if (repository->getRootPerson() != nullptr) {
        ss << repository->getRootPerson()->toString();
    } else {
        ss << "No establecida";
    }
    
    return ss.str();
}

int FamilyTreeService::getFamilySize() const {
    return repository->getMemberCount();
}

bool FamilyTreeService::hasRoot() const {
    return repository->getRootPerson() != nullptr;
}

void FamilyTreeService::clearFamilyTree() {
    repository->clearTree();
}