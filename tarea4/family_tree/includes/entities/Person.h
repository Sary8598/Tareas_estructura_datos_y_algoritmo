#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
private:
    std::string name;
    int age;
    std::string relationship;
    Person* father;
    Person* mother;
    Person* spouse;
    Person* firstChild;
    Person* nextSibling;

public:
    Person(const std::string& personName, int personAge, const std::string& rel = "");
    ~Person();
    
    // Getters
    std::string getName() const;
    int getAge() const;
    std::string getRelationship() const;
    Person* getFather() const;
    Person* getMother() const;
    Person* getSpouse() const;
    Person* getFirstChild() const;
    Person* getNextSibling() const;
    
    // Setters
    void setFather(Person* parent);
    void setMother(Person* parent);
    void setSpouse(Person* partner);
    void addChild(Person* child);
    void setNextSibling(Person* sibling);
    
    // Utility methods
    std::string toString() const;
    bool hasChildren() const;
    bool hasSiblings() const;
    bool isMarried() const;
};

#endif
