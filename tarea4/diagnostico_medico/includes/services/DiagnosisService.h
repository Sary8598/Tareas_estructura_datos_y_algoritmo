#ifndef DIAGNOSISSERVICE_H
#define DIAGNOSISSERVICE_H

#include "repositories/DecisionTreeRepository.h"
#include <string>

class DiagnosisService {
private:
    DecisionTreeRepository* repository;
    DecisionNode* currentNode;

public:
    DiagnosisService(DecisionTreeRepository* repo);
    ~DiagnosisService();
    
    // Tree management
    void setupDefaultTree();
    std::string displayDecisionTree() const;
    std::string getTreeInfo() const;
    
    // Diagnosis session
    void startDiagnosis();
    bool answerYes();
    bool answerNo();
    bool isDiagnosisComplete() const;
    bool isDiagnosisInProgress() const;
    std::string getCurrentQuestion() const;
    std::string getCurrentDiagnosis() const;
    void resetDiagnosis();
    
    // Utility methods
    int getTreeSize() const;
    bool isTreeReady() const;
};

#endif
