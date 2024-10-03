#ifndef TILESTATEYELLOW_H
#define TILESTATEYELLOW_H

#include "iTileState.h"

class tileStateYellow : public iTileState {
public:
    tileStateYellow();
    void updateTile(tile& t) override;
    char getColor() const override;
    void enter() override;
    void exit() override;
    void forceBlue(tile &t) override;

    private:
    int mCounter;
};

#endif // TILESTATEYELLOW_H