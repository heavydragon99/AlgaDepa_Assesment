#ifndef TILESTATERED_H
#define TILESTATERED_H

#include "iTileState.h"

class tileStateRed : public iTileState {
public:
    tileStateRed();
    void updateTile(tile* t) override;
};

#endif // TILESTATERED_H