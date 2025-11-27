#include "repositories/FamilyRepository.h"
#include <iostream>
#include <sstream>
#include <iomanip>

FamilyRepository::FamilyRepository() : memberCount(0), rootPerson(nullptr) {
    for (int i = 0; i < MAX_FAMILY_MEMBERS; i++) {
        familyMembers[i] = nullptr;
    }
}

FamilyRepository::~FamilyRepository() {
    clearTree();
}

Person* FamilyRepository::findPersonByName(const std::string& name) const {
    for (int i = 0; i < memberCount; i++) {
        if (familyMembers[i] != nullptr && familyMembers[i]->getName() == name) {
            return familyMembers[i];
        }
    }
    return nullptr;
}

bool FamilyRepository::isPersonInTree(Person* person, Person* root) const {
    if (root == nullptr || person == nullptr) return false;
    if (root == person) return true;
    
    Person* child = root->getFirstChild();
    while (child != nullptr) {
        if (isPersonInTree(person, child)) return true;
        child = child->getNextSibling();
    }
    
    return false;
}

void FamilyRepository::preorderTraversal(Person* node, int depth, std::stringstream& output) const {
    if (node == nullptr) return;
    
    for (int i = 0; i < depth; i++) {
        output << "  ";
    }
    
    output << "• " << node->toString() << "\n";
    
    if (node->getSpouse() != nullptr && node->getSpouse()->getName() > node->getName()) {
        for (int i = 0; i < depth; i++) {
            output << "  ";
        }
        output << "  Esposo/a: " << node->getSpouse()->toString() << "\n";
    }
    
    Person* child = node->getFirstChild();
    while (child != nullptr) {
        preorderTraversal(child, depth + 1, output);
        child = child->getNextSibling();
    }
}

void FamilyRepository::deleteSubtree(Person* node) {
    if (node == nullptr) return;
    
    Person* child = node->getFirstChild();
    while (child != nullptr) {
        Person* nextChild = child->getNextSibling();
        deleteSubtree(child);
        child = nextChild;
    }
    
    for (int i = 0; i < memberCount; i++) {
        if (familyMembers[i] == node) {
            familyMembers[i] = nullptr;
            for (int j = i; j < memberCount - 1; j++) {
                familyMembers[j] = familyMembers[j + 1];
            }
            memberCount--;
            break;
        }
    }
    
    delete node;
}

bool FamilyRepository::addPerson(const std::string& name, int age, const std::string& relationship) {
    if (memberCount >= MAX_FAMILY_MEMBERS || name.empty()) {
        return false;
    }
    
    if (findPersonByName(name) != nullptr) {
        return false;
    }
    
    familyMembers[memberCount] = new Person(name, age, relationship);
    memberCount++;
    return true;
}

bool FamilyRepository::setRootPerson(const std::string& name) {
    Person* person = findPersonByName(name);
    if (person == nullptr) {
        return false;
    }
    
    rootPerson = person;
    return true;
}

bool FamilyRepository::addParentChildRelationship(const std::string& parentName, const std::string& childName) {
    Person* parent = findPersonByName(parentName);
    Person* child = findPersonByName(childName);
    
    if (parent == nullptr || child == nullptr) {
        return false;
    }
    
    parent->addChild(child);
    return true;
}

bool FamilyRepository::addSpouseRelationship(const std::string& person1Name, const std::string& person2Name) {
    Person* person1 = findPersonByName(person1Name);
    Person* person2 = findPersonByName(person2Name);
    
    if (person1 == nullptr || person2 == nullptr) {
        return false;
    }
    
    person1->setSpouse(person2);
    return true;
}

Person* FamilyRepository::getRootPerson() const {
    return rootPerson;
}

Person* FamilyRepository::getPerson(const std::string& name) const {
    return findPersonByName(name);
}

std::string FamilyRepository::getFamilyTreePreorder() const {
    std::stringstream ss;
    ss << "Recorrido Preorden del Arbol Familiar:\n";
    ss << "=====================================\n";
    preorderTraversal(rootPerson, 0, ss);
    return ss.str();
}

std::string FamilyRepository::getFamilyTreeFormatted() const {
    std::stringstream ss;
    ss << "ARBOL GENEALOGICO\n";
    ss << "=====================\n";
    
    if (rootPerson == nullptr) {
        ss << "El arbol esta vacio. Establezca una persona raiz primero.\n";
    } else {
        preorderTraversal(rootPerson, 0, ss);
    }
    
    ss << "\nTotal de miembros: " << memberCount << "\n";
    return ss.str();
}

int FamilyRepository::getMemberCount() const {
    return memberCount;
}

bool FamilyRepository::isTreeEmpty() const {
    return rootPerson == nullptr;
}

void FamilyRepository::clearTree() {
    if (rootPerson != nullptr) {
        deleteSubtree(rootPerson);
    } else {
        for (int i = 0; i < memberCount; i++) {
            delete familyMembers[i];
            familyMembers[i] = nullptr;
        }
    }
    memberCount = 0;
    rootPerson = nullptr;
}