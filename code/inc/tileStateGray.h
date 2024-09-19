#ifndef TILESTATEGRAY_H
#define TILESTATEGRAY_H

#include "iTileState.h"

class tileStateGray : public iTileState {
public:
    tileStateGray();
    void updateTile(tile* t) override;
    char getColor() const override;
};

#endif // TILESTATEGRAY_H