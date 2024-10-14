#ifndef TILESTATEGRAY_H
#define TILESTATEGRAY_H

#include "iTileState.h"
#include "iTileBehavior.h"

#include <memory>

class TileStateGray : public ITileState
{
public:
    TileStateGray(std::unique_ptr<ITileBehavior> aBehavior);
    void updateTile(Tile &t) override;
    char getColor() const override;
    void enter() override;
    void exit() override;
    void forceBlue(Tile &t) override;

private:
    std::unique_ptr<ITileBehavior> mBehavior;
    int mCounter;
    static const int requiredActions = 2;
};

#endif // TILESTATEGRAY_H