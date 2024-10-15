// ITileBehavior.h
#ifndef TILEBEHAVIOR_H
#define TILEBEHAVIOR_H

#include "iTileBehavior.h"

#include <memory>

class Tile;

class ITileBehavior {
public:
    virtual ~ITileBehavior() = default;
    virtual std::unique_ptr<ITileBehavior> clone() const { return nullptr; };
    virtual void doBehavior(Tile& aTile) {/*Default no-op implementation*/};
};

#endif // TILEBEHAVIOR_H




