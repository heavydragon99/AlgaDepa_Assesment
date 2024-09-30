#ifndef TILESTATEWHITE_H
#define TILESTATEWHITE_H

#include "iTileState.h"

class tileStateWhite : public iTileState
{
public:
    tileStateWhite();
    void updateTile(tile &t) override;
    char getColor() const override;
    void enter(tile &t) override;
    void exit(tile &t) override;
};

#endif // TILESTATEWHITE_H