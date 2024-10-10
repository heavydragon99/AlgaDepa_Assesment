#ifndef TILESTATEBLUE_H
#define TILESTATEBLUE_H

#include "iTileState.h"
#include "iTileBehavior.h"

#include <memory>

class TileStateBlue : public ITileState {
public:
    TileStateBlue(std::unique_ptr<ITileBehavior> aBehavior);
    void updateTile(Tile& t) override;
    char getColor() const override;
    void enter() override;
    void exit() override;
    void forceBlue(Tile& t) override;

private:
    std::unique_ptr<ITileBehavior> mBehavior;
};

#endif // TILESTATEBLUE_H