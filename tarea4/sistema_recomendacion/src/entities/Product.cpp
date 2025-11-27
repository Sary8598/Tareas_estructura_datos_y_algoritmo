#include "entities/Product.h"
#include <sstream>
#include <iomanip> 

Product::Product(const std::string& productId, const std::string& productName, double productPrice) 
    : id(productId), name(productName), price(productPrice), purchaseCount(0) {}

std::string Product::getId() const {
    return id;
}

std::string Product::getName() const {
    return name;
}

double Product::getPrice() const {
    return price;
}

int Product::getPurchaseCount() const {
    return purchaseCount;
}

void Product::setPrice(double newPrice) {
    if (newPrice >= 0) {
        price = newPrice;
    }
}

void Product::incrementPurchaseCount() {
    purchaseCount++;
}

void Product::addRelatedProduct(Product* product) {
    if (product != nullptr && product != this) {
        for (Product* existing : relatedProducts) {
            if (existing == product) {
                return;
            }
        }
        relatedProducts.push_back(product);
    }
}

const std::vector<Product*>& Product::getRelatedProducts() const {
    return relatedProducts;
}

int Product::getRelatedProductCount() const {
    return relatedProducts.size();
}

bool Product::hasRelatedProducts() const {
    return !relatedProducts.empty();
}

std::string Product::toString() const {
    std::ostringstream oss;
    oss << name << " (" << id << ")";
    if (price > 0) {
        oss << " - $" << std::fixed << std::setprecision(2) << price;
    }
    return oss.str();
}

std::string Product::getDetailedInfo() const {
    std::ostringstream oss;
    oss << "Producto: " << name << "\n";
    oss << "ID: " << id << "\n";
    oss << "Precio: $" << std::fixed << std::setprecision(2) << price << "\n";
    oss << "Veces comprado: " << purchaseCount << "\n";
    oss << "Productos relacionados: " << relatedProducts.size();
    return oss.str();
}
