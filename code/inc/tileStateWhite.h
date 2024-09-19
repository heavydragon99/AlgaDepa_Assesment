#ifndef TILESTATEWHITE_H
#define TILESTATEWHITE_H

#include "iTileState.h"

class tileStateWhite : public iTileState {
public:
    void updateTile(tile* t) override;
};

#endif // TILESTATEWHITE_H