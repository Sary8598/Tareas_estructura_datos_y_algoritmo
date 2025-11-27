#include "repositories/GraphRepository.h"
#include <algorithm>
#include <sstream>

GraphRepository::GraphRepository() : moduleCount(0) {
    for (int i = 0; i < MAX_MODULES; i++) {
        modules[i] = nullptr;
    }
}

GraphRepository::~GraphRepository() {
    clearGraph();
}

Module* GraphRepository::findModuleByName(const std::string& name) const {
    for (int i = 0; i < moduleCount; i++) {
        if (modules[i] != nullptr && modules[i]->getName() == name) {
            return modules[i];
        }
    }
    return nullptr;
}

bool GraphRepository::hasCycleDFS(Module* current, std::vector<bool>& visited, std::vector<bool>& recursionStack) const {
    if (current == nullptr) return false;
    
    int currentIndex = -1;
    for (int i = 0; i < moduleCount; i++) {
        if (modules[i] == current) {
            currentIndex = i;
            break;
        }
    }
    if (currentIndex == -1) return false;
    
    if (!visited[currentIndex]) {
        visited[currentIndex] = true;
        recursionStack[currentIndex] = true;
        
        for (Module* dependency : current->getDependencies()) {
            int depIndex = -1;
            for (int i = 0; i < moduleCount; i++) {
                if (modules[i] == dependency) {
                    depIndex = i;
                    break;
                }
            }
            
            if (depIndex != -1) {
                if (!visited[depIndex] && hasCycleDFS(dependency, visited, recursionStack)) {
                    return true;
                } else if (recursionStack[depIndex]) {
                    return true;
                }
            }
        }
    }
    
    recursionStack[currentIndex] = false;
    return false;
}

void GraphRepository::topologicalSortDFS(Module* current, std::vector<bool>& visited, std::vector<std::string>& result) const {
    if (current == nullptr) return;
    
    int currentIndex = -1;
    for (int i = 0; i < moduleCount; i++) {
        if (modules[i] == current) {
            currentIndex = i;
            break;
        }
    }
    if (currentIndex == -1 || visited[currentIndex]) return;
    
    visited[currentIndex] = true;
    
    for (Module* dependency : current->getDependencies()) {
        topologicalSortDFS(dependency, visited, result);
    }
    
    result.push_back(current->getName());
}

bool GraphRepository::addModule(const std::string& name) {
    if (moduleCount >= MAX_MODULES || name.empty()) {
        return false;
    }
    
    if (findModuleByName(name) != nullptr) {
        return false; // Module already exists
    }
    
    modules[moduleCount] = new Module(name);
    moduleCount++;
    return true;
}

bool GraphRepository::addDependency(const std::string& fromModule, const std::string& toModule) {
    if (fromModule == toModule) {
        return false; // Self-dependency not allowed
    }
    
    Module* from = findModuleByName(fromModule);
    Module* to = findModuleByName(toModule);
    
    if (from == nullptr || to == nullptr) {
        return false;
    }
    
    from->addDependency(to);
    return true;
}

Module* GraphRepository::getModule(const std::string& name) const {
    return findModuleByName(name);
}

std::vector<std::string> GraphRepository::getAllModuleNames() const {
    std::vector<std::string> names;
    for (int i = 0; i < moduleCount; i++) {
        if (modules[i] != nullptr) {
            names.push_back(modules[i]->getName());
        }
    }
    return names;
}

std::vector<std::string> GraphRepository::getLoadOrder() const {
    std::vector<std::string> result;
    std::vector<bool> visited(moduleCount, false);
    
    for (int i = 0; i < moduleCount; i++) {
        if (!visited[i]) {
            topologicalSortDFS(modules[i], visited, result);
        }
    }
    
    std::reverse(result.begin(), result.end());
    return result;
}

bool GraphRepository::hasCycles() const {
    if (moduleCount == 0) return false;
    
    std::vector<bool> visited(moduleCount, false);
    std::vector<bool> recursionStack(moduleCount, false);
    
    for (int i = 0; i < moduleCount; i++) {
        if (!visited[i]) {
            if (hasCycleDFS(modules[i], visited, recursionStack)) {
                return true;
            }
        }
    }
    
    return false;
}

std::vector<std::string> GraphRepository::detectCycles() const {
    std::vector<std::string> cycles;
    
    if (hasCycles()) {
        cycles.push_back("Se detectaron ciclos en las dependencias");
        cycles.push_back("El grafo no puede tener un orden de carga valido");
    } else {
        cycles.push_back("No se detectaron ciclos en las dependencias");
    }
    
    return cycles;
}

int GraphRepository::getModuleCount() const {
    return moduleCount;
}

bool GraphRepository::moduleExists(const std::string& name) const {
    return findModuleByName(name) != nullptr;
}

void GraphRepository::clearGraph() {
    for (int i = 0; i < moduleCount; i++) {
        delete modules[i];
        modules[i] = nullptr;
    }
    moduleCount = 0;
}
