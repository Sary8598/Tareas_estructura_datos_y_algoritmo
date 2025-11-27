#ifndef DEPENDENCYSERVICE_H
#define DEPENDENCYSERVICE_H

#include "repositories/GraphRepository.h"
#include <string>
#include <vector>

class DependencyService {
private:
    GraphRepository* repository;

public:
    DependencyService(GraphRepository* repo);
    ~DependencyService();
    
    bool addModule(const std::string& name);
    bool addDependency(const std::string& fromModule, const std::string& toModule);
    
    std::vector<std::string> getLoadOrder();
    std::vector<std::string> detectCycles();
    std::vector<std::string> getAllModulesInfo();
    std::string getModuleInfo(const std::string& name);
    
    int getModuleCount() const;
    bool hasCycles() const;
    void clearGraph();
};

#endif
