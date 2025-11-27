#ifndef RECOMMENDATIONSERVICE_H
#define RECOMMENDATIONSERVICE_H

#include "repositories/GraphRepository.h"
#include <string>
#include <vector>

class RecommendationService {
private:
    GraphRepository* repository;

public:
    RecommendationService(GraphRepository* repo);
    ~RecommendationService();
    
    bool addProduct(const std::string& id, const std::string& name, double price = 0.0);
    bool recordPurchaseTogether(const std::string& product1Id, const std::string& product2Id);
    
    std::vector<std::string> getRecommendations(const std::string& productId, int depth = 2);
    std::vector<std::string> getPopularProducts(int limit = 5);
    std::vector<std::string> getAllProductsInfo();
    std::vector<std::string> getProductRelationships();
    std::vector<std::string> getStatistics();
    std::string getProductInfo(const std::string& productId);
    
    int getProductCount() const;
    void clearData();
};

#endif
