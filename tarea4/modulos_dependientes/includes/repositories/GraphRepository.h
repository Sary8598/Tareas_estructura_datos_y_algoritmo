#ifndef GRAPHREPOSITORY_H
#define GRAPHREPOSITORY_H

#include "entities/Module.h"
#include <string>
#include <vector>

class GraphRepository {
private:
    static const int MAX_MODULES = 100;
    Module* modules[MAX_MODULES];
    int moduleCount;

    Module* findModuleByName(const std::string& name) const;
    bool hasCycleDFS(Module* current, std::vector<bool>& visited, std::vector<bool>& recursionStack) const;
    void topologicalSortDFS(Module* current, std::vector<bool>& visited, std::vector<std::string>& result) const;

public:
    GraphRepository();
    ~GraphRepository();
    
    bool addModule(const std::string& name);
    bool addDependency(const std::string& fromModule, const std::string& toModule);
    
    Module* getModule(const std::string& name) const;
    std::vector<std::string> getAllModuleNames() const;
    std::vector<std::string> getLoadOrder() const;
    bool hasCycles() const;
    std::vector<std::string> detectCycles() const;
    
    int getModuleCount() const;
    bool moduleExists(const std::string& name) const;
    void clearGraph();
};

#endif
