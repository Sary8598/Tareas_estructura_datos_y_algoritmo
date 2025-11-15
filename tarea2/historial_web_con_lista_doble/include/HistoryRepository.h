#ifndef HISTORY_REPOSITORY_H
#define HISTORY_REPOSITORY_H

#include "IHistoryRepository.h"
#include <chrono>

class HistoryRepository : public IHistoryRepository {
private:
    WebPage* head;
    WebPage* tail;
    WebPage* current;
    
public:
    HistoryRepository();
    ~HistoryRepository();
    
    void insertPage(const std::string& url, const std::string& datetime) override;
    bool removePage(const std::string& url) override;
    PageArray getHistoryReverse() override;
    WebPage* getCurrentPage() override;
    WebPage* navigateForward() override;
    WebPage* navigateBackward() override;
    void clear() override;
    
    std::chrono::nanoseconds insertTime;
    std::chrono::nanoseconds removeTime;
    std::chrono::nanoseconds getHistoryTime;
    std::chrono::nanoseconds navigateTime;
    std::chrono::nanoseconds getCurrentTime;
    
    struct RepoTimes {
        long long insertTime;
        long long removeTime;
        long long getHistoryTime;
        long long navigateTime;
        long long getCurrentTime;
    };
    
    RepoTimes getExecutionTimes() const;
};

#endif