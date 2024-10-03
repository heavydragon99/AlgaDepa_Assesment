#ifndef TILESTATEWHITE_H
#define TILESTATEWHITE_H

#include "iTileState.h"
#include "iTileBehavior.h"

#include <memory>

class tileStateWhite : public iTileState {
public:
    tileStateWhite(std::unique_ptr<iTileBehavior> aBehavior);
    void updateTile(tile& t) override;
    char getColor() const override;
    void enter() override;
    void exit() override;
    void forceBlue(tile& t) override;

private:
    std::unique_ptr<iTileBehavior> mBehavior;
};

#endif // TILESTATEWHITE_H