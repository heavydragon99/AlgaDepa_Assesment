#ifndef TILESTATERED_H
#define TILESTATERED_H

#include "iTileState.h"
#include "iTileBehavior.h"

#include <memory>

class TileStateRed : public ITileState {
public:
    TileStateRed(std::unique_ptr<ITileBehavior> aBehavior);
    std::unique_ptr<ITileState> clone() const override;
    void updateTile(Tile& t) override;
    char getColor() const override;
    void enter() override;
    void exit() override;
    void forceBlue(Tile& t) override;

private:
    std::unique_ptr<ITileBehavior> mBehavior;
};

#endif // TILESTATERED_H