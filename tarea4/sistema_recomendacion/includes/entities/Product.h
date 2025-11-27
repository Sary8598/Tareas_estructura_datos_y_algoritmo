#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <vector>

class Product {
private:
    std::string id;
    std::string name;
    double price;
    std::vector<Product*> relatedProducts;
    int purchaseCount;

public:
    Product(const std::string& productId, const std::string& productName, double productPrice = 0.0);
    
    std::string getId() const;
    std::string getName() const;
    double getPrice() const;
    int getPurchaseCount() const;
    
    void setPrice(double newPrice);
    void incrementPurchaseCount();
    void addRelatedProduct(Product* product);
    
    const std::vector<Product*>& getRelatedProducts() const;
    int getRelatedProductCount() const;
    bool hasRelatedProducts() const;
    
    std::string toString() const;
    std::string getDetailedInfo() const;
};

#endif
