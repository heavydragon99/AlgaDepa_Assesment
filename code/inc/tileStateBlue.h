#ifndef TILESTATEBLUE_H
#define TILESTATEBLUE_H

#include "iTileState.h"

class tileStateBlue : public iTileState {
public:
    tileStateBlue();
    void updateTile(tile* t) override;
};

#endif // TILESTATEBLUE_H