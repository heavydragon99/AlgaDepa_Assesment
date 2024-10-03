// InfectTilesBehavior.h
#ifndef INFECTTILESBEHAVIOR_H
#define INFECTTILESBEHAVIOR_H

#include "iTileBehavior.h"

class infectTilesBehavior : public iTileBehavior {
public:
    infectTilesBehavior() = default;
    void doBehavior() override;
};

#endif // INFECTTILESBEHAVIOR_H