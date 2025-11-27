#ifndef DECISIONTREEREPOSITORY_H
#define DECISIONTREEREPOSITORY_H

#include "entities/DecisionNode.h"
#include <string>

class DecisionTreeRepository {
private:
    static const int MAX_NODES = 50;
    DecisionNode* nodes[MAX_NODES];
    int nodeCount;
    DecisionNode* rootNode;

    void preorderTraversal(DecisionNode* node, int depth, std::stringstream& output) const;
    void deleteSubtree(DecisionNode* node);

public:
    DecisionTreeRepository();
    ~DecisionTreeRepository();
    
    // Tree construction methods
    bool addNode(DecisionNode* node);
    bool setRootNode(DecisionNode* node);
    bool createQuestionNode(const std::string& question);
    bool createDiagnosisNode(const std::string& diagnosis);
    
    // Tree navigation methods
    DecisionNode* getRootNode() const;
    DecisionNode* navigateYes(DecisionNode* currentNode) const;
    DecisionNode* navigateNo(DecisionNode* currentNode) const;
    
    // Tree display methods
    std::string getTreePreorder() const;
    std::string getTreeStructure() const;
    
    // Medical decision tree setup
    void setupMedicalDecisionTree();
    
    // Utility methods
    int getNodeCount() const;
    bool isTreeEmpty() const;
    void clearTree();
};

#endif
