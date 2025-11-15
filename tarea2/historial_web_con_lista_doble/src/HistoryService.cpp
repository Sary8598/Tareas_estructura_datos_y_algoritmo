#include "../include/HistoryService.h"
#include <stdexcept>
#include <ctime>
#include <sstream>
#include <iomanip>

HistoryService::HistoryService(std::unique_ptr<IHistoryRepository> repo) 
    : repository(std::move(repo)) {}

void HistoryService::visitPage(const std::string& url) {
    if (!isValidUrl(url)) {
        throw std::invalid_argument("URL no valida");
    }
    
    std::string datetime = getCurrentDateTime();
    repository->insertPage(url, datetime);
}

bool HistoryService::removePage(const std::string& url) {
    if (!isValidUrl(url)) {
        throw std::invalid_argument("URL no valida");
    }
    
    return repository->removePage(url);
}

PageArray HistoryService::getHistoryReverse() {
    return repository->getHistoryReverse();
}

WebPage* HistoryService::getCurrentPage() {
    return repository->getCurrentPage();
}

WebPage* HistoryService::navigateForward() {
    return repository->navigateForward();
}

WebPage* HistoryService::navigateBackward() {
    return repository->navigateBackward();
}

bool HistoryService::isValidUrl(const std::string& url) const {
    return !url.empty() && url.length() > 3;
}

std::string HistoryService::getCurrentDateTime() const {
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

ServiceTimes HistoryService::getExecutionTimes() const {
    if (auto* historyRepo = dynamic_cast<HistoryRepository*>(repository.get())) {
        auto repoTimes = historyRepo->getExecutionTimes();
        return {
            repoTimes.insertTime,
            repoTimes.removeTime,
            repoTimes.getHistoryTime,
            repoTimes.navigateTime,
            repoTimes.getCurrentTime
        };
    }
    return {0, 0, 0, 0, 0};
}