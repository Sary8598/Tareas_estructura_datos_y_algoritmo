#ifndef RECOMMENDATIONCONTROLLER_H
#define RECOMMENDATIONCONTROLLER_H

#include "services/RecommendationService.h"
#include <string>

class RecommendationController {
private:
    RecommendationService* service;

    void displayMenu() const;
    void processChoice(int choice);
    void addProduct();
    void recordPurchase();
    void getRecommendations();
    void showPopularProducts();
    void showAllProducts();
    void showProductRelationships();
    void showStatistics();
    void showProductInfo();
    void showHelp() const;
    void showExample() const;
    int getValidatedInput() const;
    double getValidatedPrice() const;

public:
    RecommendationController(RecommendationService* recService);
    ~RecommendationController();
    
    void run();
};

#endif
