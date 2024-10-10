#ifndef TILESTATEWHITE_H
#define TILESTATEWHITE_H

#include "iTileState.h"
#include "iTileBehavior.h"

#include <memory>

class TileStateWhite : public ITileState {
public:
    TileStateWhite(std::unique_ptr<ITileBehavior> aBehavior);
    void updateTile(Tile& t) override;
    char getColor() const override;
    void enter() override;
    void exit() override;
    void forceBlue(Tile& t) override;

private:
    std::unique_ptr<ITileBehavior> mBehavior;
};

#endif // TILESTATEWHITE_H