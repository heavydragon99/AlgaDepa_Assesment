#ifndef TILESTATERED_H
#define TILESTATERED_H

#include "iTileState.h"

class tileStateRed : public iTileState
{
public:
    tileStateRed();
    void updateTile(tile *t) override;
    char getColor() const override;
    void enter(tile *t) override;
    void exit(tile *t) override;
};

#endif // TILESTATERED_H