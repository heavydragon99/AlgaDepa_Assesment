// ITileBehavior.h
#ifndef TILEBEHAVIOR_H
#define TILEBEHAVIOR_H

#include "iTileBehavior.h"

class Tile;

class ITileBehavior {
public:
    virtual ~ITileBehavior() = default;
    virtual void doBehavior(Tile& aTile) {/*Default no-op implementation*/};
};

#endif // TILEBEHAVIOR_H




