#ifndef TILESTATEBLUE_H
#define TILESTATEBLUE_H

#include "iTileState.h"

class tileStateBlue : public iTileState {
public:
    tileStateBlue();
    void updateTile(tile* t) override;
    char getColor() const override;
};

#endif // TILESTATEBLUE_H