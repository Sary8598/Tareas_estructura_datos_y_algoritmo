#ifndef HISTORY_VIEW_H
#define HISTORY_VIEW_H

#include "WebPage.h"
#include <string>

class HistoryController;

class HistoryView {
public:
    static void showMenu();
    static void showHistory(const PageArray& pages);
    static void showCurrentPage(WebPage* page);
    static void showMessage(const std::string& message);
    static void showError(const std::string& error);
    static void showSuccess(const std::string& success);
    static void showExecutionTimes(long long insertTime, long long removeTime, 
                                 long long getHistoryTime, long long navigateTime, 
                                 long long totalTime);
    static std::string getUrl();
    static int getUserChoice();
    static void waitForUser();
    static void run(HistoryController& controller);
};

#endif