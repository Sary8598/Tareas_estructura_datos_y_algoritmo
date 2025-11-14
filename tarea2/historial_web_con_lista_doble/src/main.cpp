#include "../include/HistoryController.h"
#include "../include/HistoryService.h"
#include "../include/HistoryRepository.h"
#include "../include/HistoryView.h"
#include <memory>
#include <chrono>

int main() {
    auto startTotal = std::chrono::high_resolution_clock::now();
    
    try {
        auto repository = std::make_unique<HistoryRepository>();
        auto service = std::make_unique<HistoryService>(std::move(repository));
        auto controller = std::make_unique<HistoryController>(std::move(service));
        
        HistoryView::run(*controller);
        
        auto endTotal = std::chrono::high_resolution_clock::now();
        auto totalTime = std::chrono::duration_cast<std::chrono::microseconds>(endTotal - startTotal);
        
        auto times = controller->getExecutionTimes();
        HistoryView::showExecutionTimes(
            times.insertTime,
            times.removeTime,
            times.getHistoryTime,
            times.navigateTime,
            totalTime.count()
        );
        
    } catch (const std::exception& e) {
        HistoryView::showError("Error critico: " + std::string(e.what()));
        return 1;
    }
    
    return 0;
}