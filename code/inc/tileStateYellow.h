#ifndef TILESTATEYELLOW_H
#define TILESTATEYELLOW_H

#include "iTileState.h"
#include "iTileBehavior.h"

#include <memory>

class tileStateYellow : public iTileState {
public:
    tileStateYellow(std::unique_ptr<iTileBehavior> aBehavior);
    void updateTile(tile& t) override;
    char getColor() const override;
    void enter() override;
    void exit() override;
    void forceBlue(tile &t) override;

private:
    std::unique_ptr<iTileBehavior> mBehavior;
    int mCounter;
    static const int requiredActions = 2;
};

#endif // TILESTATEYELLOW_H