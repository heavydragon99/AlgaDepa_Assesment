// KillPlayerBehavior.h
#ifndef KILLPLAYERBEHAVIOR_H
#define KILLPLAYERBEHAVIOR_H

#include "TileBehavior.h"

class killPlayerBehavior : public iTileBehavior {
public:
    void doBehavior(tile& t) override {
        // Logic to kill player
    }
};

#endif // KILLPLAYERBEHAVIOR_H