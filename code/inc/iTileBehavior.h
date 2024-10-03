// iTileBehavior.h
#ifndef TILEBEHAVIOR_H
#define TILEBEHAVIOR_H

#include "iTileBehavior.h"

#include <memory>

class tile; // Forward declaration

class iTileBehavior {
public:
    virtual ~iTileBehavior() = default;
    virtual void doBehavior(tile& t) = 0;
};

#endif // TILEBEHAVIOR_H




