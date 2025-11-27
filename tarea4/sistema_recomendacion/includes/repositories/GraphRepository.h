#ifndef GRAPHREPOSITORY_H
#define GRAPHREPOSITORY_H

#include "entities/Product.h"
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

class GraphRepository {
private:
    static const int MAX_PRODUCTS = 100;
    Product* products[MAX_PRODUCTS];
    int productCount;

    Product* findProductById(const std::string& id) const;
    Product* findProductByName(const std::string& name) const;
    void BFSRecommendations(Product* startProduct, int maxDepth, std::vector<Product*>& recommendations) const;

public:
    GraphRepository();
    ~GraphRepository();
    
    bool addProduct(const std::string& id, const std::string& name, double price = 0.0);
    bool recordPurchaseTogether(const std::string& product1Id, const std::string& product2Id);
    
    Product* getProductById(const std::string& id) const;
    Product* getProductByName(const std::string& name) const;
    std::vector<std::string> getAllProductNames() const;
    std::vector<Product*> getRecommendations(const std::string& productId, int depth = 2) const;
    std::vector<Product*> getPopularProducts(int limit = 5) const;
    
    std::vector<std::string> getProductRelationships() const;
    std::vector<std::string> getStatistics() const;
    
    int getProductCount() const;
    bool productExists(const std::string& id) const;
    void clearGraph();
};

#endif
