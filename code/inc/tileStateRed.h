#ifndef TILESTATERED_H
#define TILESTATERED_H

#include "iTileState.h"
#include "iTileBehavior.h"

#include <memory>

class tileStateRed : public iTileState {
public:
    tileStateRed(std::unique_ptr<iTileBehavior> aBehavior);
    void updateTile(tile& t) override;
    char getColor() const override;
    void enter() override;
    void exit() override;
    void forceBlue(tile& t) override;

private:
    std::unique_ptr<iTileBehavior> mBehavior;
};

#endif // TILESTATERED_H