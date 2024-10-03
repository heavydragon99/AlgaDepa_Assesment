#ifndef TILESTATEGRAY_H
#define TILESTATEGRAY_H

#include "iTileState.h"
#include "iTileBehavior.h"

#include <memory>

class tileStateGray : public iTileState
{
public:
    tileStateGray(std::unique_ptr<iTileBehavior> aBehavior);
    void updateTile(tile &t) override;
    char getColor() const override;
    void enter() override;
    void exit() override;
    void forceBlue(tile &t) override;

private:
    std::unique_ptr<iTileBehavior> mBehavior;
    int mCounter;
    static const int requiredActions = 3;
};

#endif // TILESTATEGRAY_H