#include "../include/HistoryView.h"
#include "../include/HistoryController.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

void HistoryView::showMenu() {
    std::cout << "\n=== NAVEGADOR WEB - HISTORIAL ===\n";
    std::cout << "1. Visitar pagina\n";
    std::cout << "2. Mostrar historial (orden cronologico inverso)\n";
    std::cout << "3. Navegar hacia atras\n";
    std::cout << "4. Navegar hacia adelante\n";
    std::cout << "5. Eliminar pagina del historial\n";
    std::cout << "6. Mostrar pagina actual\n";
    std::cout << "7. Salir\n";
    std::cout << "================================\n";
}

void HistoryView::showHistory(const PageArray& pages) {
    std::cout << "\n=== HISTORIAL DE NAVEGACION (ULTIMA A PRIMERA) ===\n";
    
    if (pages.count == 0) {
        std::cout << "No hay paginas en el historial.\n";
        return;
    }
    
    std::cout << std::left << std::setw(40) << "URL" 
              << std::setw(20) << "Fecha y Hora" << "\n";
    std::cout << std::string(60, '-') << "\n";
    
    for (int i = 0; i < pages.count; i++) {
        std::cout << std::left << std::setw(40) << pages.pages[i]->url
                  << std::setw(20) << pages.pages[i]->datetime << "\n";
    }
    std::cout << "==================================================\n";
}

void HistoryView::showCurrentPage(WebPage* page) {
    std::cout << "\n=== PAGINA ACTUAL ===\n";
    if (page) {
        std::cout << "URL: " << page->url << "\n";
        std::cout << "Visitada: " << page->datetime << "\n";
    } else {
        std::cout << "No hay pagina actual.\n";
    }
    std::cout << "====================\n";
}

void HistoryView::showMessage(const std::string& message) {
    std::cout << message << std::endl;
}

void HistoryView::showError(const std::string& error) {
    std::cout << "ERROR: " << error << std::endl;
}

void HistoryView::showSuccess(const std::string& success) {
    std::cout << "ÉXITO: " << success << std::endl;
}

void HistoryView::showExecutionTimes(long long insertTime, long long removeTime, 
                                   long long getHistoryTime, long long navigateTime, 
                                   long long totalTime) {
    std::cout << "\n=== TIEMPOS DE EJECUCION ===\n";
    std::cout << "Visitar pagina: " << insertTime << " microsegundos\n";
    std::cout << "Eliminar pagina: " << removeTime << " microsegundos\n";
    std::cout << "Obtener historial: " << getHistoryTime << " microsegundos\n";
    std::cout << "Navegar: " << navigateTime << " microsegundos\n";
    std::cout << "Tiempo total: " << totalTime << " microsegundos\n";
    std::cout << "============================\n";
}

std::string HistoryView::getUrl() {
    std::string url;
    std::cout << "Ingrese la URL: ";
    std::cin.ignore();
    std::getline(std::cin, url);
    return url;
}

int HistoryView::getUserChoice() {
    int choice;
    std::cout << "Seleccione una opción: ";
    std::cin >> choice;
    return choice;
}

void HistoryView::waitForUser() {
    std::cout << "\nPresione Enter para continuar...";
    std::cin.ignore();
    std::cin.get();
}

void HistoryView::run(HistoryController& controller) {
    int choice;
    
    do {
        showMenu();
        choice = getUserChoice();
        
        try {
            switch (choice) {
                case 1: {
                    std::string url = getUrl();
                    controller.visitPage(url);
                    showSuccess("Pagina visitada y agregada al historial");
                    break;
                }
                case 2: {
                    auto history = controller.getHistoryReverse();
                    showHistory(history);
                    break;
                }
                case 3: {
                    auto page = controller.navigateBackward();
                    if (page) {
                        showSuccess("Navegando hacia atras");
                        showCurrentPage(page);
                    } else {
                        showError("No se puede navegar hacia atras");
                    }
                    break;
                }
                case 4: {
                    auto page = controller.navigateForward();
                    if (page) {
                        showSuccess("Navegando hacia adelante");
                        showCurrentPage(page);
                    } else {
                        showError("No se puede navegar hacia adelante");
                    }
                    break;
                }
                case 5: {
                    std::string url = getUrl();
                    if (controller.removePage(url)) {
                        showSuccess("Pagina eliminada del historial");
                    } else {
                        showError("Pagina no encontrada en el historial");
                    }
                    break;
                }
                case 6: {
                    auto page = controller.getCurrentPage();
                    showCurrentPage(page);
                    break;
                }
                case 7:
                    showMessage("Saliendo del navegador...");
                    break;
                default:
                    showError("Opcion invalida");
                    break;
            }
        } catch (const std::exception& e) {
            showError(e.what());
        }
        
        if (choice != 7) {
            waitForUser();
        }
        
    } while (choice != 7);
}