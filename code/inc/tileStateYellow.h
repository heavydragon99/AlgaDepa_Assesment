#ifndef TILESTATEYELLOW_H
#define TILESTATEYELLOW_H

#include "iTileState.h"

class tileStateYellow : public iTileState {
public:
    tileStateYellow();
    void updateTile(tile* t) override;
    char getColor() const override;
};

#endif // TILESTATEYELLOW_H