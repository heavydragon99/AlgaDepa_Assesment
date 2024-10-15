#ifndef TILESTATEBLUE_H
#define TILESTATEBLUE_H

#include "iTileBehavior.h"
#include "iTileState.h"

#include <memory>

class TileStateBlue : public ITileState {
public:
    TileStateBlue(std::unique_ptr<ITileBehavior> aBehavior);
    std::unique_ptr<ITileState> clone() const override;
    void updateTile(Tile& t) override;
    char getColor() const override;
    void enter() override;
    void exit() override;
    void forceBlue(Tile& t) override;

private:
    std::unique_ptr<ITileBehavior> mBehavior;
    int mCounter;
    static const int requiredActions = 3;
};

#endif // TILESTATEBLUE_H