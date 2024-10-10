#ifndef TILESTATEYELLOW_H
#define TILESTATEYELLOW_H

#include "iTileState.h"
#include "iTileBehavior.h"

#include <memory>

class TileStateYellow : public ITileState {
public:
    TileStateYellow(std::unique_ptr<ITileBehavior> aBehavior);
    void updateTile(Tile& t) override;
    char getColor() const override;
    void enter() override;
    void exit() override;
    void forceBlue(Tile &t) override;

private:
    std::unique_ptr<ITileBehavior> mBehavior;
    int mCounter;
    static const int requiredActions = 2;
};

#endif // TILESTATEYELLOW_H