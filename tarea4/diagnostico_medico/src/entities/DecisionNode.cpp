#include "entities/DecisionNode.h"

DecisionNode::DecisionNode(const std::string& questionText) 
    : question(questionText), diagnosis(""), yesNode(nullptr), noNode(nullptr), isQuestionNode(true) {}

DecisionNode::DecisionNode(const std::string& diagnosisText, bool isDiagnosis) 
    : question(""), diagnosis(diagnosisText), yesNode(nullptr), noNode(nullptr), isQuestionNode(false) {}

DecisionNode::~DecisionNode() {
    // Note: Memory management handled by repository to avoid circular deletions
}

std::string DecisionNode::getQuestion() const {
    return question;
}

std::string DecisionNode::getDiagnosis() const {
    return diagnosis;
}

DecisionNode* DecisionNode::getYesNode() const {
    return yesNode;
}

DecisionNode* DecisionNode::getNoNode() const {
    return noNode;
}

bool DecisionNode::isQuestion() const {
    return isQuestionNode;
}

bool DecisionNode::isDiagnosisNode() const {
    return !isQuestionNode;
}

bool DecisionNode::hasYesNode() const {
    return yesNode != nullptr;
}

bool DecisionNode::hasNoNode() const {
    return noNode != nullptr;
}

bool DecisionNode::isLeaf() const {
    return yesNode == nullptr && noNode == nullptr;
}

void DecisionNode::setYesNode(DecisionNode* node) {
    yesNode = node;
}

void DecisionNode::setNoNode(DecisionNode* node) {
    noNode = node;
}

void DecisionNode::setQuestion(const std::string& questionText) {
    question = questionText;
    isQuestionNode = true;
}

void DecisionNode::setDiagnosis(const std::string& diagnosisText) {
    diagnosis = diagnosisText;
    isQuestionNode = false;
}

std::string DecisionNode::toString() const {
    if (isQuestionNode) {
        return " " + question;
    } else {
        return " Diagnóstico: " + diagnosis;
    }
}
