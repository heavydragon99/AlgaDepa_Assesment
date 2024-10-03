#ifndef TILESTATEBLUE_H
#define TILESTATEBLUE_H

#include "iTileState.h"

class tileStateBlue : public iTileState {
public:
    tileStateBlue();
    void updateTile(tile& t) override;
    char getColor() const override;
    void enter() override;
    void exit() override;
    void forceBlue(tile& t) override;
};

#endif // TILESTATEBLUE_H