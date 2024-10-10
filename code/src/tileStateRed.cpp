#include "tileStateRed.h"

#include "tile.h"
#include "tileFactory.h"

TileStateRed::TileStateRed(std::unique_ptr<ITileBehavior> aBehavior) : mBehavior(std::move(aBehavior)) {}


void TileStateRed::updateTile(Tile& t) {
    mBehavior->doBehavior(t);

    TileFactory factory;
    t.setState(factory.createNextState(getColor()));
}

char TileStateRed::getColor() const { return 'R'; }

void TileStateRed::enter() {
    // Code to execute when entering the red state
}

void TileStateRed::exit() {
    // Code to execute when exiting the red state
}

void TileStateRed::forceBlue(Tile& t) { }