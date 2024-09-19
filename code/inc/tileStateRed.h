#ifndef TILESTATERED_H
#define TILESTATERED_H

#include "iTileState.h"

class tileStateRed : public iTileState {
public:
    void updateTile(tile* t) override;
};

#endif // TILESTATRED_H