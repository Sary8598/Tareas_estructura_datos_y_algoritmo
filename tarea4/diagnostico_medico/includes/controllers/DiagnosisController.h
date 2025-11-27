#ifndef DIAGNOSISCONTROLLER_H
#define DIAGNOSISCONTROLLER_H

#include "services/DiagnosisService.h"
#include <string>

class DiagnosisController {
private:
    DiagnosisService* service;

    void displayMainMenu() const;
    void displayDiagnosisMenu() const;
    void processMainChoice(int choice);
    void processDiagnosisChoice(int choice);
    void viewDecisionTree();
    void startNewDiagnosis();
    void continueDiagnosis();
    void showTreeInfo() const;
    void showHelp() const;
    int getValidatedInput() const;
    char getYesNoInput() const;

public:
    DiagnosisController(DiagnosisService* diagService);
    ~DiagnosisController();
    
    void run();
};

#endif
