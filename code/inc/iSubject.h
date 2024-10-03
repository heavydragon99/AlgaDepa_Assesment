// iSubject.h
#ifndef ISUBJECT_H
#define ISUBJECT_H

#include "iObserver.h"
#include <vector>
#include <algorithm>
#include <string>

class iSubject {
public:
    virtual ~iSubject() = default;
    
    void subscribe(iObserver* observer) {
        observers.push_back(observer);
    }

    void unsubscribe(iObserver* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

protected:
    void notify(const std::pair<int, int>& aTilePos, const std::string& aAction) {
        for (iObserver* observer : observers) {
            observer->update(aTilePos, aAction);
        }
    }

private:
    std::vector<iObserver*> observers;
};

#endif // ISUBJECT_H
