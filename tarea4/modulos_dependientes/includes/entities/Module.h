#ifndef MODULE_H
#define MODULE_H

#include <string>
#include <vector>

class Module {
private:
    std::string name;
    std::vector<Module*> dependencies;
    std::vector<Module*> dependents;

public:
    Module(const std::string& moduleName);
    
    std::string getName() const;
    void addDependency(Module* dependency);
    void addDependent(Module* dependent);
    
    const std::vector<Module*>& getDependencies() const;
    const std::vector<Module*>& getDependents() const;
    
    bool hasDependencies() const;
    bool hasDependents() const;
    int getDependencyCount() const;
    int getDependentCount() const;
    
    std::string toString() const;
};

#endif
