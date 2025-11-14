#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <string>

const int MAX_PAGES = 100;

struct WebPage {
    std::string url;
    std::string datetime;
    WebPage* next;
    WebPage* prev;
    
    WebPage(const std::string& u, const std::string& dt) 
        : url(u), datetime(dt), next(nullptr), prev(nullptr) {}
};

struct PageArray {
    WebPage* pages[MAX_PAGES];
    int count;
    
    PageArray() : count(0) {
        for (int i = 0; i < MAX_PAGES; i++) {
            pages[i] = nullptr;
        }
    }
};

#endif