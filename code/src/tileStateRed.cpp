#include "tileStateRed.h"

#include "tile.h"
#include "tileFactory.h"

TileStateRed::TileStateRed(std::unique_ptr<ITileBehavior> aBehavior) : mBehavior(std::move(aBehavior)) {}

std::unique_ptr<ITileState> TileStateRed::clone() const {
    return std::make_unique<TileStateRed>(mBehavior->clone());
}

void TileStateRed::updateTile(Tile& t) {
    mBehavior->doBehavior(t);

    t.setState(TileFactory::createNextState(getColor()));
}

char TileStateRed::getColor() const { return 'R'; }

void TileStateRed::enter() {
    // Code to execute when entering the red state
}

void TileStateRed::exit() {
    // Code to execute when exiting the red state
}

void TileStateRed::forceBlue(Tile& t) { t.setState(TileFactory::createBlueState()); }