#ifndef TILESTATEBLUE_H
#define TILESTATEBLUE_H

#include "iTileState.h"
#include "iTileBehavior.h"

#include <memory>

class tileStateBlue : public iTileState {
public:
    tileStateBlue(std::unique_ptr<iTileBehavior> aBehavior);
    void updateTile(tile& t) override;
    char getColor() const override;
    void enter() override;
    void exit() override;
    void forceBlue(tile& t) override;

private:
    std::unique_ptr<iTileBehavior> mBehavior;
};

#endif // TILESTATEBLUE_H