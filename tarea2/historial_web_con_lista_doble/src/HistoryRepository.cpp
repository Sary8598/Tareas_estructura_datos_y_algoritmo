#include "../include/HistoryRepository.h"

HistoryRepository::HistoryRepository() : head(nullptr), tail(nullptr), current(nullptr) {}

HistoryRepository::~HistoryRepository() {
    clear();
}

void HistoryRepository::insertPage(const std::string& url, const std::string& datetime) {
    auto start = std::chrono::high_resolution_clock::now();
    
    WebPage* newPage = new WebPage(url, datetime);
    
    if (!head) {
        head = tail = current = newPage;
    } else {
        tail->next = newPage;
        newPage->prev = tail;
        tail = newPage;
        current = newPage;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    insertTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}

bool HistoryRepository::removePage(const std::string& url) {
    auto start = std::chrono::high_resolution_clock::now();
    
    WebPage* temp = head;
    bool found = false;
    
    while (temp) {
        if (temp->url == url) {
            if (temp == head && temp == tail) {
                head = tail = current = nullptr;
            } else if (temp == head) {
                head = temp->next;
                head->prev = nullptr;
                if (current == temp) current = head;
            } else if (temp == tail) {
                tail = temp->prev;
                tail->next = nullptr;
                if (current == temp) current = tail;
            } else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                if (current == temp) current = temp->next;
            }
            delete temp;
            found = true;
            break;
        }
        temp = temp->next;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    removeTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    return found;
}

PageArray HistoryRepository::getHistoryReverse() {
    auto start = std::chrono::high_resolution_clock::now();
    
    PageArray history;
    WebPage* temp = tail;
    
    while (temp && history.count < MAX_PAGES) {
        history.pages[history.count] = temp;
        history.count++;
        temp = temp->prev;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    getHistoryTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    return history;
}

WebPage* HistoryRepository::getCurrentPage() {
    return current;
}

WebPage* HistoryRepository::navigateForward() {
    auto start = std::chrono::high_resolution_clock::now();
    
    if (current && current->next) {
        current = current->next;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    navigateTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    return current;
}

WebPage* HistoryRepository::navigateBackward() {
    auto start = std::chrono::high_resolution_clock::now();
    
    if (current && current->prev) {
        current = current->prev;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    navigateTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    return current;
}

void HistoryRepository::clear() {
    while (head) {
        WebPage* temp = head;
        head = head->next;
        delete temp;
    }
    tail = current = nullptr;
}

HistoryRepository::RepoTimes HistoryRepository::getExecutionTimes() const {
    return {
        insertTime.count(),
        removeTime.count(),
        getHistoryTime.count(),
        navigateTime.count()
    };
}