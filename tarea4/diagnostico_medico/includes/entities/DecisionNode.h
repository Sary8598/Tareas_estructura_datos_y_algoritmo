#ifndef DECISIONNODE_H
#define DECISIONNODE_H

#include <string>

class DecisionNode {
private:
    std::string question;
    std::string diagnosis;
    DecisionNode* yesNode;
    DecisionNode* noNode;
    bool isQuestionNode;

public:
    DecisionNode(const std::string& questionText);
    DecisionNode(const std::string& diagnosisText, bool isDiagnosis);
    ~DecisionNode();
    
    // Getters
    std::string getQuestion() const;
    std::string getDiagnosis() const;
    DecisionNode* getYesNode() const;
    DecisionNode* getNoNode() const;
    bool isQuestion() const;
    bool isDiagnosisNode() const;
    bool hasYesNode() const;
    bool hasNoNode() const;
    bool isLeaf() const;
    
    // Setters
    void setYesNode(DecisionNode* node);
    void setNoNode(DecisionNode* node);
    void setQuestion(const std::string& questionText);
    void setDiagnosis(const std::string& diagnosisText);
    
    // Utility methods
    std::string toString() const;
};

#endif
