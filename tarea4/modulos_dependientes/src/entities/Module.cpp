#include "entities/Module.h"

Module::Module(const std::string& moduleName) : name(moduleName) {}

std::string Module::getName() const {
    return name;
}

void Module::addDependency(Module* dependency) {
    if (dependency != nullptr && dependency != this) {
        // Check if dependency already exists
        for (Module* existingDep : dependencies) {
            if (existingDep == dependency) {
                return; // Dependency already exists
            }
        }
        dependencies.push_back(dependency);
        dependency->addDependent(this);
    }
}

void Module::addDependent(Module* dependent) {
    if (dependent != nullptr && dependent != this) {
        // Check if dependent already exists
        for (Module* existingDep : dependents) {
            if (existingDep == dependent) {
                return; // Dependent already exists
            }
        }
        dependents.push_back(dependent);
    }
}

const std::vector<Module*>& Module::getDependencies() const {
    return dependencies;
}

const std::vector<Module*>& Module::getDependents() const {
    return dependents;
}

bool Module::hasDependencies() const {
    return !dependencies.empty();
}

bool Module::hasDependents() const {
    return !dependents.empty();
}

int Module::getDependencyCount() const {
    return dependencies.size();
}

int Module::getDependentCount() const {
    return dependents.size();
}

std::string Module::toString() const {
    return name + " (Dependencies: " + std::to_string(dependencies.size()) + 
           ", Dependents: " + std::to_string(dependents.size()) + ")";
}
