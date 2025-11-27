#ifndef FAMILYTREESERVICE_H
#define FAMILYTREESERVICE_H

#include "repositories/FamilyRepository.h"
#include <string>

class FamilyTreeService {
private:
    FamilyRepository* repository;

public:
    FamilyTreeService(FamilyRepository* repo);
    ~FamilyTreeService();
    
    bool addFamilyMember(const std::string& name, int age, const std::string& relationship);
    bool setFamilyRoot(const std::string& name);
    bool addParentChild(const std::string& parentName, const std::string& childName);
    bool addMarriage(const std::string& person1Name, const std::string& person2Name);
    
    std::string displayFamilyTree() const;
    std::string getTreeInfo() const;
    int getFamilySize() const;
    bool hasRoot() const;
    void clearFamilyTree();
};

#endif
