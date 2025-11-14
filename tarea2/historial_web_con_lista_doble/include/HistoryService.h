#ifndef HISTORY_SERVICE_H
#define HISTORY_SERVICE_H

#include "IHistoryRepository.h"
#include "HistoryRepository.h"
#include <memory>

struct ServiceTimes {
    long long insertTime = 0;
    long long removeTime = 0;
    long long getHistoryTime = 0;
    long long navigateTime = 0;
};

class HistoryService {
private:
    std::unique_ptr<IHistoryRepository> repository;
    
public:
    explicit HistoryService(std::unique_ptr<IHistoryRepository> repo);
    
    void visitPage(const std::string& url);
    bool removePage(const std::string& url);
    PageArray getHistoryReverse();
    WebPage* getCurrentPage();
    WebPage* navigateForward();
    WebPage* navigateBackward();
    bool isValidUrl(const std::string& url) const;
    ServiceTimes getExecutionTimes() const;
    
private:
    std::string getCurrentDateTime() const;
};

#endif