#ifndef TILESTATEGRAY_H
#define TILESTATEGRAY_H

#include "iTileState.h"

class tileStateGray : public iTileState {
public:
    void updateTile(tile* t) override;
};

#endif // TILESTATEGRAY_H