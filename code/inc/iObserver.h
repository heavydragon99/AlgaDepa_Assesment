// iObserver.h
#ifndef IOBSERVER_H
#define IOBSERVER_H

#include <utility>
#include <string>

class iObserver {
public:
    virtual ~iObserver() = default;
    virtual void update(const std::pair<int, int>& tilePos, const std::string& action) = 0;
};

#endif // IOBSERVER_H
