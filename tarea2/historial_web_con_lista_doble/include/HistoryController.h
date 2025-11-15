#ifndef HISTORY_CONTROLLER_H
#define HISTORY_CONTROLLER_H

#include "HistoryService.h"
#include <memory>

struct ExecutionTimes {
    long long insertTime = 0;
    long long removeTime = 0;
    long long getHistoryTime = 0;
    long long navigateTime = 0;
    long long getCurrentTime = 0;
};

class HistoryController {
private:
    std::unique_ptr<HistoryService> service;
    
public:
    explicit HistoryController(std::unique_ptr<HistoryService> historyService);
    
    void visitPage(const std::string& url);
    bool removePage(const std::string& url);
    PageArray getHistoryReverse();
    WebPage* getCurrentPage();
    WebPage* navigateForward();
    WebPage* navigateBackward();
    ExecutionTimes getExecutionTimes() const;
};

#endif