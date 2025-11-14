#ifndef IHISTORY_REPOSITORY_H
#define IHISTORY_REPOSITORY_H

#include "WebPage.h"

class IHistoryRepository {
public:
    virtual ~IHistoryRepository() = default;
    virtual void insertPage(const std::string& url, const std::string& datetime) = 0;
    virtual bool removePage(const std::string& url) = 0;
    virtual PageArray getHistoryReverse() = 0;
    virtual WebPage* getCurrentPage() = 0;
    virtual WebPage* navigateForward() = 0;
    virtual WebPage* navigateBackward() = 0;
    virtual void clear() = 0;
};

#endif