#include "entities/Person.h"
#include <sstream>

Person::Person(const std::string& personName, int personAge, const std::string& rel) 
    : name(personName), age(personAge), relationship(rel),
      father(nullptr), mother(nullptr), spouse(nullptr),
      firstChild(nullptr), nextSibling(nullptr) {}

Person::~Person() {
    // Note: We don't delete family members here to avoid circular deletions
    // Memory management is handled by the repository
}

std::string Person::getName() const {
    return name;
}

int Person::getAge() const {
    return age;
}

std::string Person::getRelationship() const {
    return relationship;
}

Person* Person::getFather() const {
    return father;
}

Person* Person::getMother() const {
    return mother;
}

Person* Person::getSpouse() const {
    return spouse;
}

Person* Person::getFirstChild() const {
    return firstChild;
}

Person* Person::getNextSibling() const {
    return nextSibling;
}

void Person::setFather(Person* parent) {
    father = parent;
}

void Person::setMother(Person* parent) {
    mother = parent;
}

void Person::setSpouse(Person* partner) {
    spouse = partner;
    if (partner != nullptr && partner->getSpouse() != this) {
        partner->setSpouse(this);
    }
}

void Person::addChild(Person* child) {
    if (child == nullptr) return;
    
    // Set this person as parent
    if (child->getFather() == nullptr) {
        child->setFather(this);
    } else if (child->getMother() == nullptr && this->getRelationship() != "Padre") {
        child->setMother(this);
    }
    
    // Add to children linked list
    if (firstChild == nullptr) {
        firstChild = child;
    } else {
        Person* current = firstChild;
        while (current->getNextSibling() != nullptr) {
            current = current->getNextSibling();
        }
        current->setNextSibling(child);
    }
}

void Person::setNextSibling(Person* sibling) {
    nextSibling = sibling;
}

std::string Person::toString() const {
    std::ostringstream oss;
    oss << name << " (" << age << " años)";
    if (!relationship.empty()) {
        oss << " - " << relationship;
    }
    return oss.str();
}

bool Person::hasChildren() const {
    return firstChild != nullptr;
}

bool Person::hasSiblings() const {
    return nextSibling != nullptr;
}

bool Person::isMarried() const {
    return spouse != nullptr;
}
