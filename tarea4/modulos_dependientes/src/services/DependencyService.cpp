#include "services/DependencyService.h"
#include <sstream>

DependencyService::DependencyService(GraphRepository* repo) : repository(repo) {}

DependencyService::~DependencyService() {
    delete repository;
}

bool DependencyService::addModule(const std::string& name) {
    return repository->addModule(name);
}

bool DependencyService::addDependency(const std::string& fromModule, const std::string& toModule) {
    return repository->addDependency(fromModule, toModule);
}

std::vector<std::string> DependencyService::getLoadOrder() {
    return repository->getLoadOrder();
}

std::vector<std::string> DependencyService::detectCycles() {
    return repository->detectCycles();
}

std::vector<std::string> DependencyService::getAllModulesInfo() {
    std::vector<std::string> modulesInfo;
    std::vector<std::string> moduleNames = repository->getAllModuleNames();
    
    modulesInfo.push_back("Modulos en el sistema (" + std::to_string(moduleNames.size()) + "):");
    
    for (const std::string& name : moduleNames) {
        Module* module = repository->getModule(name);
        if (module != nullptr) {
            std::stringstream ss;
            ss << "- " << module->toString();
            modulesInfo.push_back(ss.str());
            
            // Show dependencies
            const std::vector<Module*>& dependencies = module->getDependencies();
            if (!dependencies.empty()) {
                ss.str("");
                ss << "  Dependencias: ";
                for (size_t i = 0; i < dependencies.size(); i++) {
                    ss << dependencies[i]->getName();
                    if (i < dependencies.size() - 1) {
                        ss << ", ";
                    }
                }
                modulesInfo.push_back(ss.str());
            }
            
            // Show dependents
            const std::vector<Module*>& dependents = module->getDependents();
            if (!dependents.empty()) {
                ss.str("");
                ss << "  Dependientes: ";
                for (size_t i = 0; i < dependents.size(); i++) {
                    ss << dependents[i]->getName();
                    if (i < dependents.size() - 1) {
                        ss << ", ";
                    }
                }
                modulesInfo.push_back(ss.str());
            }
        }
    }
    
    return modulesInfo;
}

std::string DependencyService::getModuleInfo(const std::string& name) {
    Module* module = repository->getModule(name);
    if (module == nullptr) {
        return "Modulo no encontrado: " + name;
    }
    
    std::stringstream ss;
    ss << "Informacion del modulo " << name << ":\n";
    ss << "- " << module->toString() << "\n";
    
    const std::vector<Module*>& dependencies = module->getDependencies();
    if (!dependencies.empty()) {
        ss << "- Dependencias: ";
        for (size_t i = 0; i < dependencies.size(); i++) {
            ss << dependencies[i]->getName();
            if (i < dependencies.size() - 1) {
                ss << ", ";
            }
        }
        ss << "\n";
    } else {
        ss << "- Sin dependencias\n";
    }
    
    const std::vector<Module*>& dependents = module->getDependents();
    if (!dependents.empty()) {
        ss << "- Dependientes: ";
        for (size_t i = 0; i < dependents.size(); i++) {
            ss << dependents[i]->getName();
            if (i < dependents.size() - 1) {
                ss << ", ";
            }
        }
        ss << "\n";
    } else {
        ss << "- Sin dependientes\n";
    }
    
    return ss.str();
}

int DependencyService::getModuleCount() const {
    return repository->getModuleCount();
}

bool DependencyService::hasCycles() const {
    return repository->hasCycles();
}

void DependencyService::clearGraph() {
    repository->clearGraph();
}
