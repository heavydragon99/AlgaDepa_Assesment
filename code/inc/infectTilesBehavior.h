// InfectTilesBehavior.h
#ifndef INFECTTILESBEHAVIOR_H
#define INFECTTILESBEHAVIOR_H

#include "iTileBehavior.h"
#include "iSubject.h"

class infectTilesBehavior : public iTileBehavior, public iSubject {
public:
    infectTilesBehavior() = default;
    void doBehavior() override;
};

#endif // INFECTTILESBEHAVIOR_H