#ifndef FAMILYCONTROLLER_H
#define FAMILYCONTROLLER_H

#include "services/FamilyTreeService.h"
#include <string>

class FamilyController {
private:
    FamilyTreeService* service;

    void displayMenu() const;
    void processChoice(int choice);
    void addFamilyMember();
    void setRootPerson();
    void addParentChild();
    void addMarriage();
    void viewFamilyTree();
    void showTreeInfo() const;
    void showHelp() const;
    void showExample() const;
    int getValidatedInput() const;
    int getValidatedAge() const;

public:
    FamilyController(FamilyTreeService* familyService);
    ~FamilyController();
    
    void run();
};

#endif
