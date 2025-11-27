#include "controllers/RecommendationController.h"
#include <iostream>
#include <limits>

RecommendationController::RecommendationController(RecommendationService* recService) 
    : service(recService) {}

RecommendationController::~RecommendationController() {
    delete service;
}

void RecommendationController::displayMenu() const {
    std::cout << "\n=== SISTEMA DE RECOMENDACIONES ===\n";
    std::cout << "1. Agregar producto\n";
    std::cout << "2. Registrar compra conjunta\n";
    std::cout << "3. Obtener recomendaciones\n";
    std::cout << "4. Mostrar productos populares\n";
    std::cout << "5. Mostrar todos los productos\n";
    std::cout << "6. Mostrar relaciones entre productos\n";
    std::cout << "7. Mostrar estadisticas\n";
    std::cout << "8. Mostrar informacion de producto\n";
    std::cout << "9. Mostrar ayuda\n";
    std::cout << "10. Mostrar ejemplo\n";
    std::cout << "11. Salir\n";
    std::cout << "Seleccione una opcion (1-11): ";
}

void RecommendationController::processChoice(int choice) {
    switch (choice) {
        case 1:
            addProduct();
            break;
        case 2:
            recordPurchase();
            break;
        case 3:
            getRecommendations();
            break;
        case 4:
            showPopularProducts();
            break;
        case 5:
            showAllProducts();
            break;
        case 6:
            showProductRelationships();
            break;
        case 7:
            showStatistics();
            break;
        case 8:
            showProductInfo();
            break;
        case 9:
            showHelp();
            break;
        case 10:
            showExample();
            break;
        case 11:
            std::cout << "Saliendo del sistema de recomendaciones...\n";
            break;
        default:
            std::cout << "Opcion invalida. Por favor seleccione 1-11.\n";
    }
}

void RecommendationController::addProduct() {
    std::string id, name;
    double price;
    
    std::cout << "Ingrese el ID del producto: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, id);
    
    std::cout << "Ingrese el nombre del producto: ";
    std::getline(std::cin, name);
    
    std::cout << "Ingrese el precio (0 si no aplica): $";
    price = getValidatedPrice();
    
    if (id.empty() || name.empty()) {
        std::cout << "Error: ID y nombre no pueden estar vacios\n";
        return;
    }
    
    if (service->addProduct(id, name, price)) {
        std::cout << "Producto agregado exitosamente: " << name << " (" << id << ")\n";
    } else {
        std::cout << "Error: No se pudo agregar el producto (ID duplicado o limite alcanzado)\n";
    }
}

void RecommendationController::recordPurchase() {
    std::string product1Id, product2Id;
    
    std::cout << "Ingrese el ID del primer producto: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, product1Id);
    
    std::cout << "Ingrese el ID del segundo producto: ";
    std::getline(std::cin, product2Id);
    
    if (product1Id.empty() || product2Id.empty()) {
        std::cout << "Error: Los IDs no pueden estar vacios\n";
        return;
    }
    
    if (service->recordPurchaseTogether(product1Id, product2Id)) {
        std::cout << "Compra conjunta registrada: " << product1Id << " + " << product2Id << "\n";
    } else {
        std::cout << "Error: No se pudo registrar la compra conjunta\n";
        std::cout << "(Productos no existen o IDs iguales)\n";
    }
}

void RecommendationController::getRecommendations() {
    std::string productId;
    
    std::cout << "Ingrese el ID del producto para recomendaciones: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, productId);
    
    if (productId.empty()) {
        std::cout << "Error: El ID no puede estar vacio\n";
        return;
    }
    
    std::vector<std::string> recommendations = service->getRecommendations(productId);
    
    std::cout << "\n=== RECOMENDACIONES ===\n";
    for (const std::string& rec : recommendations) {
        std::cout << rec << "\n";
    }
}

void RecommendationController::showPopularProducts() {
    std::vector<std::string> popularProducts = service->getPopularProducts();
    
    std::cout << "\n=== PRODUCTOS POPULARES ===\n";
    for (const std::string& product : popularProducts) {
        std::cout << product << "\n";
    }
}

void RecommendationController::showAllProducts() {
    std::vector<std::string> allProducts = service->getAllProductsInfo();
    
    std::cout << "\n=== TODOS LOS PRODUCTOS ===\n";
    for (const std::string& product : allProducts) {
        std::cout << product << "\n";
    }
}

void RecommendationController::showProductRelationships() {
    std::vector<std::string> relationships = service->getProductRelationships();
    
    std::cout << "\n=== RELACIONES ENTRE PRODUCTOS ===\n";
    for (const std::string& relation : relationships) {
        std::cout << relation << "\n";
    }
}

void RecommendationController::showStatistics() {
    std::vector<std::string> stats = service->getStatistics();
    
    std::cout << "\n=== ESTADISTICAS DEL SISTEMA ===\n";
    for (const std::string& stat : stats) {
        std::cout << stat << "\n";
    }
}

void RecommendationController::showProductInfo() {
    std::string productId;
    
    std::cout << "Ingrese el ID del producto: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, productId);
    
    if (productId.empty()) {
        std::cout << "Error: El ID no puede estar vacio\n";
        return;
    }
    
    std::string info = service->getProductInfo(productId);
    std::cout << "\n=== INFORMACION DEL PRODUCTO ===\n";
    std::cout << info << "\n";
}

void RecommendationController::showHelp() const {
    std::cout << "\n=== AYUDA - SISTEMA DE RECOMENDACIONES ===\n";
    std::cout << "Este sistema genera recomendaciones usando un grafo de productos.\n\n";
    std::cout << "CONCEPTOS:\n";
    std::cout << "- Producto: Elemento con ID, nombre y precio\n";
    std::cout << "- Compra conjunta: Cuando dos productos se compran juntos\n";
    std::cout << "- Grafo: Los productos son vertices, las compras conjuntas son aristas\n";
    std::cout << "- BFS: Busqueda en amplitud para encontrar productos relacionados\n\n";
    std::cout << "FUNCIONALIDADES:\n";
    std::cout << "1. Agregar producto: Anade un nuevo producto al sistema\n";
    std::cout << "2. Registrar compra conjunta: Establece que dos productos se compraron juntos\n";
    std::cout << "3. Recomendaciones: Sugiere productos relacionados usando BFS (profundidad 2)\n";
    std::cout << "4. Productos populares: Muestra los productos mas comprados\n";
    std::cout << "5. Todos los productos: Lista todos los productos en el sistema\n";
    std::cout << "6. Relaciones: Muestra que productos se compran juntos\n";
    std::cout << "7. Estadisticas: Muestra metricas del sistema\n";
    std::cout << "8. Info producto: Informacion detallada de un producto\n";
}

void RecommendationController::showExample() const {
    std::cout << "\n=== EJEMPLO DE USO ===\n";
    std::cout << "Productos:\n";
    std::cout << "  P001 - Laptop\n";
    std::cout << "  P002 - Mouse\n";
    std::cout << "  P003 - Teclado\n";
    std::cout << "  P004 - Monitor\n";
    std::cout << "  P005 - Audifonos\n\n";
    std::cout << "Compras conjuntas:\n";
    std::cout << "  Laptop + Mouse\n";
    std::cout << "  Laptop + Teclado\n";
    std::cout << "  Mouse + Teclado\n";
    std::cout << "  Monitor + Audifonos\n\n";
    std::cout << "Recomendaciones para Laptop:\n";
    std::cout << "  Mouse, Teclado, Monitor, Audifonos\n";
    std::cout << "(BFS encuentra productos a profundidad 1 y 2)\n";
}

int RecommendationController::getValidatedInput() const {
    int choice;
    std::cin >> choice;
    
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }
    
    return choice;
}

double RecommendationController::getValidatedPrice() const {
    double price;
    if (!(std::cin >> price) || price < 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return 0.0;
    }
    return price;
}

void RecommendationController::run() {
    int choice = 0;
    
    std::cout << "Sistema de Recomendaciones Iniciado\n";
    
    do {
        displayMenu();
        choice = getValidatedInput();
        
        if (choice == -1) {
            std::cout << "Entrada invalida. Por favor ingrese un numero.\n";
            continue;
        }
        
        processChoice(choice);
        
    } while (choice != 11);
}
