#include "repositories/GraphRepository.h"
#include <algorithm>
#include <sstream>
#include <unordered_set>
#include <iomanip> 

GraphRepository::GraphRepository() : productCount(0) {
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        products[i] = nullptr;
    }
}

GraphRepository::~GraphRepository() {
    clearGraph();
}

Product* GraphRepository::findProductById(const std::string& id) const {
    for (int i = 0; i < productCount; i++) {
        if (products[i] != nullptr && products[i]->getId() == id) {
            return products[i];
        }
    }
    return nullptr;
}

Product* GraphRepository::findProductByName(const std::string& name) const {
    for (int i = 0; i < productCount; i++) {
        if (products[i] != nullptr && products[i]->getName() == name) {
            return products[i];
        }
    }
    return nullptr;
}

void GraphRepository::BFSRecommendations(Product* startProduct, int maxDepth, std::vector<Product*>& recommendations) const {
    if (startProduct == nullptr || maxDepth <= 0) return;
    
    std::queue<std::pair<Product*, int>> queue;
    std::unordered_set<std::string> visited;
    
    queue.push(std::make_pair(startProduct, 0));
    visited.insert(startProduct->getId());
    
    while (!queue.empty()) {
        std::pair<Product*, int> currentPair = queue.front();
        Product* current = currentPair.first;
        int depth = currentPair.second;
        queue.pop();
        
        if (depth > 0 && depth <= maxDepth) {
            recommendations.push_back(current);
        }
        
        if (depth < maxDepth) {
            for (Product* neighbor : current->getRelatedProducts()) {
                if (visited.find(neighbor->getId()) == visited.end()) {
                    visited.insert(neighbor->getId());
                    queue.push(std::make_pair(neighbor, depth + 1));
                }
            }
        }
    }
}

bool GraphRepository::addProduct(const std::string& id, const std::string& name, double price) {
    if (productCount >= MAX_PRODUCTS || id.empty() || name.empty()) {
        return false;
    }
    
    if (findProductById(id) != nullptr) {
        return false;
    }
    
    products[productCount] = new Product(id, name, price);
    productCount++;
    return true;
}

bool GraphRepository::recordPurchaseTogether(const std::string& product1Id, const std::string& product2Id) {
    if (product1Id == product2Id) {
        return false;
    }
    
    Product* product1 = findProductById(product1Id);
    Product* product2 = findProductById(product2Id);
    
    if (product1 == nullptr || product2 == nullptr) {
        return false;
    }
    
    product1->incrementPurchaseCount();
    product2->incrementPurchaseCount();
    
    product1->addRelatedProduct(product2);
    product2->addRelatedProduct(product1);
    
    return true;
}

Product* GraphRepository::getProductById(const std::string& id) const {
    return findProductById(id);
}

Product* GraphRepository::getProductByName(const std::string& name) const {
    return findProductByName(name);
}

std::vector<std::string> GraphRepository::getAllProductNames() const {
    std::vector<std::string> names;
    for (int i = 0; i < productCount; i++) {
        if (products[i] != nullptr) {
            names.push_back(products[i]->getName() + " (" + products[i]->getId() + ")");
        }
    }
    return names;
}

std::vector<Product*> GraphRepository::getRecommendations(const std::string& productId, int depth) const {
    std::vector<Product*> recommendations;
    Product* startProduct = findProductById(productId);
    
    if (startProduct != nullptr) {
        BFSRecommendations(startProduct, depth, recommendations);
    }
    
    return recommendations;
}

std::vector<Product*> GraphRepository::getPopularProducts(int limit) const {
    std::vector<Product*> allProducts;
    for (int i = 0; i < productCount; i++) {
        if (products[i] != nullptr) {
            allProducts.push_back(products[i]);
        }
    }
    
    std::sort(allProducts.begin(), allProducts.end(), 
        [](Product* a, Product* b) {
            return a->getPurchaseCount() > b->getPurchaseCount();
        });
    
    if (limit > 0 && limit < static_cast<int>(allProducts.size())) {
        allProducts.resize(limit);
    }
    
    return allProducts;
}

std::vector<std::string> GraphRepository::getProductRelationships() const {
    std::vector<std::string> relationships;
    
    relationships.push_back("Relaciones entre productos:");
    
    for (int i = 0; i < productCount; i++) {
        if (products[i] != nullptr && products[i]->hasRelatedProducts()) {
            std::stringstream ss;
            ss << products[i]->getName() << " se compra con: ";
            
            const std::vector<Product*>& related = products[i]->getRelatedProducts();
            for (size_t j = 0; j < related.size(); j++) {
                ss << related[j]->getName();
                if (j < related.size() - 1) {
                    ss << ", ";
                }
            }
            relationships.push_back(ss.str());
        }
    }
    
    if (relationships.size() == 1) {
        relationships.push_back("No hay relaciones registradas");
    }
    
    return relationships;
}

std::vector<std::string> GraphRepository::getStatistics() const {
    std::vector<std::string> stats;
    
    stats.push_back("Estadisticas del sistema:");
    stats.push_back("Total de productos: " + std::to_string(productCount));
    
    int totalPurchases = 0;
    int productsWithRelations = 0;
    
    for (int i = 0; i < productCount; i++) {
        if (products[i] != nullptr) {
            totalPurchases += products[i]->getPurchaseCount();
            if (products[i]->hasRelatedProducts()) {
                productsWithRelations++;
            }
        }
    }
    
    stats.push_back("Total de compras registradas: " + std::to_string(totalPurchases));
    stats.push_back("Productos con relaciones: " + std::to_string(productsWithRelations));
    
    if (productCount > 0) {
        double avgPurchases = static_cast<double>(totalPurchases) / productCount;
        std::stringstream ss;
        ss << "Compras promedio por producto: " << std::fixed << std::setprecision(2) << avgPurchases;
        stats.push_back(ss.str());
    }
    
    return stats;
}

int GraphRepository::getProductCount() const {
    return productCount;
}

bool GraphRepository::productExists(const std::string& id) const {
    return findProductById(id) != nullptr;
}

void GraphRepository::clearGraph() {
    for (int i = 0; i < productCount; i++) {
        delete products[i];
        products[i] = nullptr;
    }
    productCount = 0;
}
