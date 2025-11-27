#ifndef FAMILYREPOSITORY_H
#define FAMILYREPOSITORY_H

#include "entities/Person.h"
#include <string>

class FamilyRepository {
private:
    static const int MAX_FAMILY_MEMBERS = 50;
    Person* familyMembers[MAX_FAMILY_MEMBERS];
    int memberCount;
    Person* rootPerson;

    Person* findPersonByName(const std::string& name) const;
    bool isPersonInTree(Person* person, Person* root) const;
    void preorderTraversal(Person* node, int depth, std::stringstream& output) const;
    void deleteSubtree(Person* node);

public:
    FamilyRepository();
    ~FamilyRepository();
    
    bool addPerson(const std::string& name, int age, const std::string& relationship);
    bool setRootPerson(const std::string& name);
    bool addParentChildRelationship(const std::string& parentName, const std::string& childName);
    bool addSpouseRelationship(const std::string& person1Name, const std::string& person2Name);
    
    Person* getRootPerson() const;
    Person* getPerson(const std::string& name) const;
    std::string getFamilyTreePreorder() const;
    std::string getFamilyTreeFormatted() const;
    
    int getMemberCount() const;
    bool isTreeEmpty() const;
    void clearTree();
};

#endif
