#include "services/RecommendationService.h"
#include <sstream>

RecommendationService::RecommendationService(GraphRepository* repo) : repository(repo) {}

RecommendationService::~RecommendationService() {
    delete repository;
}

bool RecommendationService::addProduct(const std::string& id, const std::string& name, double price) {
    return repository->addProduct(id, name, price);
}

bool RecommendationService::recordPurchaseTogether(const std::string& product1Id, const std::string& product2Id) {
    return repository->recordPurchaseTogether(product1Id, product2Id);
}

std::vector<std::string> RecommendationService::getRecommendations(const std::string& productId, int depth) {
    std::vector<std::string> recommendations;
    std::vector<Product*> recommendedProducts = repository->getRecommendations(productId, depth);
    
    Product* sourceProduct = repository->getProductById(productId);
    if (sourceProduct == nullptr) {
        recommendations.push_back("Producto no encontrado: " + productId);
        return recommendations;
    }
    
    recommendations.push_back("Recomendaciones para: " + sourceProduct->getName());
    
    if (recommendedProducts.empty()) {
        recommendations.push_back("No hay recomendaciones disponibles");
        recommendations.push_back("Agregue mas compras conjuntas para generar recomendaciones");
    } else {
        for (size_t i = 0; i < recommendedProducts.size(); i++) {
            std::stringstream ss;
            ss << i + 1 << ". " << recommendedProducts[i]->toString();
            recommendations.push_back(ss.str());
        }
    }
    
    return recommendations;
}

std::vector<std::string> RecommendationService::getPopularProducts(int limit) {
    std::vector<std::string> popularList;
    std::vector<Product*> popularProducts = repository->getPopularProducts(limit);
    
    popularList.push_back("Productos mas populares:");
    
    if (popularProducts.empty()) {
        popularList.push_back("No hay productos en el sistema");
    } else {
        for (size_t i = 0; i < popularProducts.size(); i++) {
            std::stringstream ss;
            ss << i + 1 << ". " << popularProducts[i]->getName() 
               << " - Compras: " << popularProducts[i]->getPurchaseCount();
            popularList.push_back(ss.str());
        }
    }
    
    return popularList;
}

std::vector<std::string> RecommendationService::getAllProductsInfo() {
    std::vector<std::string> productsInfo;
    std::vector<std::string> productNames = repository->getAllProductNames();
    
    productsInfo.push_back("Productos en el sistema (" + std::to_string(productNames.size()) + "):");
    
    for (const std::string& name : productNames) {
        productsInfo.push_back("- " + name);
    }
    
    return productsInfo;
}

std::vector<std::string> RecommendationService::getProductRelationships() {
    return repository->getProductRelationships();
}

std::vector<std::string> RecommendationService::getStatistics() {
    return repository->getStatistics();
}

std::string RecommendationService::getProductInfo(const std::string& productId) {
    Product* product = repository->getProductById(productId);
    if (product == nullptr) {
        return "Producto no encontrado: " + productId;
    }
    
    std::stringstream ss;
    ss << product->getDetailedInfo() << "\n\n";
    
    std::vector<Product*> recommendations = repository->getRecommendations(productId, 2);
    if (!recommendations.empty()) {
        ss << "Recomendaciones basadas en este producto:\n";
        for (size_t i = 0; i < recommendations.size(); i++) {
            ss << i + 1 << ". " << recommendations[i]->toString() << "\n";
        }
    } else {
        ss << "No hay recomendaciones disponibles para este producto";
    }
    
    return ss.str();
}

int RecommendationService::getProductCount() const {
    return repository->getProductCount();
}

void RecommendationService::clearData() {
    repository->clearGraph();
}
