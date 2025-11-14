#include "../include/HistoryService.h"
#include "../include/HistoryRepository.h"
#include "../include/HistoryView.h"
#include <memory>
#include <chrono>
#include <iostream>
#include <thread>

void demoProgram() {
    auto startTotal = std::chrono::high_resolution_clock::now();
    
    std::cout << "=== DEMOSTRACIÓN DEL HISTORIAL WEB ===\n\n";
    
    auto repository = std::make_unique<HistoryRepository>();
    auto service = std::make_unique<HistoryService>(std::move(repository));
    
    std::cout << "1. Visitando páginas web (inserción al final):\n";
    service->visitPage("https://www.google.com");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    service->visitPage("https://www.github.com");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    service->visitPage("https://www.stackoverflow.com");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    service->visitPage("https://www.youtube.com");
    
    std::cout << "   - Google\n";
    std::cout << "   - GitHub\n";
    std::cout << "   - Stack Overflow\n";
    std::cout << "   - YouTube\n\n";
    
    std::cout << "2. Historial completo (orden cronológico inverso):\n";
    auto history = service->getHistoryReverse();
    HistoryView::showHistory(history);
    
    std::cout << "\n3. Página actual:\n";
    auto current = service->getCurrentPage();
    HistoryView::showCurrentPage(current);
    
    std::cout << "\n4. Navegando hacia atrás:\n";
    auto prev = service->navigateBackward();
    HistoryView::showCurrentPage(prev);
    
    std::cout << "\n5. Navegando hacia adelante:\n";
    auto next = service->navigateForward();
    HistoryView::showCurrentPage(next);
    
    std::cout << "\n6. Eliminando 'GitHub' del historial:\n";
    if (service->removePage("https://www.github.com")) {
        HistoryView::showSuccess("Página eliminada");
    }
    
    std::cout << "\n7. Historial después de eliminación:\n";
    history = service->getHistoryReverse();
    HistoryView::showHistory(history);
    
    auto endTotal = std::chrono::high_resolution_clock::now();
    auto totalTime = std::chrono::duration_cast<std::chrono::microseconds>(endTotal - startTotal);
    
    std::cout << "\n8. Análisis de rendimiento:\n";
    auto times = service->getExecutionTimes();
    HistoryView::showExecutionTimes(
        times.insertTime,
        times.removeTime,
        times.getHistoryTime,
        times.navigateTime,
        totalTime.count()
    );
    
    std::cout << "\n=== DEMOSTRACIÓN COMPLETADA ===\n";
}

int main() {
    demoProgram();
    return 0;
}