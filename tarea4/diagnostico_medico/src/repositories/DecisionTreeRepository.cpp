#include "repositories/DecisionTreeRepository.h"
#include <iostream>
#include <sstream>

DecisionTreeRepository::DecisionTreeRepository() : nodeCount(0), rootNode(nullptr) {
    for (int i = 0; i < MAX_NODES; i++) {
        nodes[i] = nullptr;
    }
}

DecisionTreeRepository::~DecisionTreeRepository() {
    clearTree();
}

void DecisionTreeRepository::preorderTraversal(DecisionNode* node, int depth, std::stringstream& output) const {
    if (node == nullptr) return;
    
    for (int i = 0; i < depth; i++) {
        output << "  ";
    }
    
    if (node->isQuestion()) {
        output << "Q: ";
    } else {
        output << "D: ";
    }
    
    output << node->toString() << "\n";
    
    if (node->hasYesNode()) {
        for (int i = 0; i < depth; i++) {
            output << "  ";
        }
        output << "  Si ->\n";
        preorderTraversal(node->getYesNode(), depth + 1, output);
    }
    
    if (node->hasNoNode()) {
        for (int i = 0; i < depth; i++) {
            output << "  ";
        }
        output << "  No ->\n";
        preorderTraversal(node->getNoNode(), depth + 1, output);
    }
}

void DecisionTreeRepository::deleteSubtree(DecisionNode* node) {
    if (node == nullptr) return;
    
    deleteSubtree(node->getYesNode());
    deleteSubtree(node->getNoNode());
    
    for (int i = 0; i < nodeCount; i++) {
        if (nodes[i] == node) {
            nodes[i] = nullptr;
            for (int j = i; j < nodeCount - 1; j++) {
                nodes[j] = nodes[j + 1];
            }
            nodeCount--;
            break;
        }
    }
    
    delete node;
}

bool DecisionTreeRepository::addNode(DecisionNode* node) {
    if (nodeCount >= MAX_NODES || node == nullptr) {
        return false;
    }
    
    nodes[nodeCount] = node;
    nodeCount++;
    return true;
}

bool DecisionTreeRepository::setRootNode(DecisionNode* node) {
    if (node == nullptr) {
        return false;
    }
    
    rootNode = node;
    bool found = false;
    for (int i = 0; i < nodeCount; i++) {
        if (nodes[i] == node) {
            found = true;
            break;
        }
    }
    if (!found) {
        addNode(node);
    }
    return true;
}

bool DecisionTreeRepository::createQuestionNode(const std::string& question) {
    DecisionNode* newNode = new DecisionNode(question);
    return addNode(newNode);
}

bool DecisionTreeRepository::createDiagnosisNode(const std::string& diagnosis) {
    DecisionNode* newNode = new DecisionNode(diagnosis, true);
    return addNode(newNode);
}

DecisionNode* DecisionTreeRepository::getRootNode() const {
    return rootNode;
}

DecisionNode* DecisionTreeRepository::navigateYes(DecisionNode* currentNode) const {
    if (currentNode == nullptr || !currentNode->hasYesNode()) {
        return nullptr;
    }
    return currentNode->getYesNode();
}

DecisionNode* DecisionTreeRepository::navigateNo(DecisionNode* currentNode) const {
    if (currentNode == nullptr || !currentNode->hasNoNode()) {
        return nullptr;
    }
    return currentNode->getNoNode();
}

std::string DecisionTreeRepository::getTreePreorder() const {
    std::stringstream ss;
    ss << "RECORRIDO PREORDEN DEL ARBOL DE DECISION\n";
    ss << "============================================\n";
    preorderTraversal(rootNode, 0, ss);
    return ss.str();
}

std::string DecisionTreeRepository::getTreeStructure() const {
    std::stringstream ss;
    ss << "ARBOL DE DECISION MEDICO\n";
    ss << "=============================\n";
    
    if (rootNode == nullptr) {
        ss << "El arbol esta vacio.\n";
    } else {
        preorderTraversal(rootNode, 0, ss);
    }
    
    ss << "\nTotal de nodos: " << nodeCount << "\n";
    return ss.str();
}

void DecisionTreeRepository::setupMedicalDecisionTree() {
    clearTree();
    
    DecisionNode* fever = new DecisionNode("Tiene fiebre?");
    DecisionNode* cough = new DecisionNode("Tiene tos?");
    DecisionNode* chestPain = new DecisionNode("Tiene dolor en el pecho?");
    DecisionNode* shortnessBreath = new DecisionNode("Tiene dificultad para respirar?");
    DecisionNode* headache = new DecisionNode("Tiene dolor de cabeza?");
    DecisionNode* soreThroat = new DecisionNode("Tiene dolor de garganta?");
    DecisionNode* fatigue = new DecisionNode("Se siente fatigado?");
    
    DecisionNode* flu = new DecisionNode("Posible gripe o resfriado comun", true);
    DecisionNode* pneumonia = new DecisionNode("Posible neumonia - Consulte urgentemente", true);
    DecisionNode* bronchitis = new DecisionNode("Posible bronquitis", true);
    DecisionNode* covid = new DecisionNode("Posible COVID-19 - Aislese y consulte", true);
    DecisionNode* migraine = new DecisionNode("Posible migrana o dolor de cabeza tensional", true);
    DecisionNode* strep = new DecisionNode("Posible faringitis estreptococica", true);
    DecisionNode* exhaustion = new DecisionNode("Posible agotamiento - Descanse", true);
    DecisionNode* healthy = new DecisionNode("Parece estar saludable - Continue con chequeos regulares", true);
    
    fever->setYesNode(cough);
    fever->setNoNode(headache);
    
    cough->setYesNode(chestPain);
    cough->setNoNode(soreThroat);
    
    headache->setYesNode(fatigue);
    headache->setNoNode(healthy);
    
    chestPain->setYesNode(shortnessBreath);
    chestPain->setNoNode(bronchitis);
    
    soreThroat->setYesNode(strep);
    soreThroat->setNoNode(flu);
    
    fatigue->setYesNode(exhaustion);
    fatigue->setNoNode(migraine);
    
    shortnessBreath->setYesNode(pneumonia);
    shortnessBreath->setNoNode(covid);
    
    addNode(fever);
    addNode(cough);
    addNode(chestPain);
    addNode(shortnessBreath);
    addNode(headache);
    addNode(soreThroat);
    addNode(fatigue);
    addNode(flu);
    addNode(pneumonia);
    addNode(bronchitis);
    addNode(covid);
    addNode(migraine);
    addNode(strep);
    addNode(exhaustion);
    addNode(healthy);
    
    setRootNode(fever);
}

int DecisionTreeRepository::getNodeCount() const {
    return nodeCount;
}

bool DecisionTreeRepository::isTreeEmpty() const {
    return rootNode == nullptr;
}

void DecisionTreeRepository::clearTree() {
    if (rootNode != nullptr) {
        deleteSubtree(rootNode);
    } else {
        for (int i = 0; i < nodeCount; i++) {
            delete nodes[i];
            nodes[i] = nullptr;
        }
        nodeCount = 0;
    }
    rootNode = nullptr;
}