#ifndef TILESTATEBLUE_H
#define TILESTATEBLUE_H

#include "iTileState.h"

class tileStateBlue : public iTileState {
public:
    tileStateBlue();
    void updateTile(tile& t) override;
    char getColor() const override;
    void enter(tile& t) override;
    void exit(tile& t) override;
};

#endif // TILESTATEBLUE_H