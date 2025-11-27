#ifndef GRAPHCONTROLLER_H
#define GRAPHCONTROLLER_H

#include "services/DependencyService.h"
#include <string>

class GraphController {
private:
    DependencyService* service;

    void displayMenu() const;
    void processChoice(int choice);
    void addModule();
    void addDependency();
    void showLoadOrder();
    void detectCycles();
    void showAllModules();
    void showModuleInfo();
    void showHelp() const;
    void showExample() const;
    int getValidatedInput() const;

public:
    GraphController(DependencyService* graphService);
    ~GraphController();
    
    void run();
};

#endif
