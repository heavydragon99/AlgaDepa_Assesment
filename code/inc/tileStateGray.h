#ifndef TILESTATEGRAY_H
#define TILESTATEGRAY_H

#include "iTileState.h"

class tileStateGray : public iTileState
{
public:
    tileStateGray();
    void updateTile(tile &t) override;
    char getColor() const override;
    void enter() override;
    void exit() override;
    void forceBlue(tile &t) override;

    private:
    int mCounter;
};

#endif // TILESTATEGRAY_H