// InfectTilesBehavior.h
#ifndef INFECTTILESBEHAVIOR_H
#define INFECTTILESBEHAVIOR_H

#include "TileBehavior.h"

class infectTilesBehavior : public iTileBehavior {
public:
    void doBehavior(tile& t) override {
        // Logic to infect tiles around this tile
    }
};

#endif // INFECTTILESBEHAVIOR_H