#include "../include/HistoryController.h"

HistoryController::HistoryController(std::unique_ptr<HistoryService> historyService) 
    : service(std::move(historyService)) {}

void HistoryController::visitPage(const std::string& url) {
    service->visitPage(url);
}

bool HistoryController::removePage(const std::string& url) {
    return service->removePage(url);
}

PageArray HistoryController::getHistoryReverse() {
    return service->getHistoryReverse();
}

WebPage* HistoryController::getCurrentPage() {
    return service->getCurrentPage();
}

WebPage* HistoryController::navigateForward() {
    return service->navigateForward();
}

WebPage* HistoryController::navigateBackward() {
    return service->navigateBackward();
}

ExecutionTimes HistoryController::getExecutionTimes() const {
    auto serviceTimes = service->getExecutionTimes();
    return {
        serviceTimes.insertTime,
        serviceTimes.removeTime,
        serviceTimes.getHistoryTime,
        serviceTimes.navigateTime
    };
}