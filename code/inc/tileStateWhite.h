#ifndef TILESTATEWHITE_H
#define TILESTATEWHITE_H

#include "iTileState.h"

class tileStateWhite : public iTileState {
public:
    tileStateWhite();
    void updateTile(tile* t) override;
    char getColor() const override;
};

#endif // TILESTATEWHITE_H