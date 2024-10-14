#include "tileStateWhite.h"

#include "tile.h"
#include "tileFactory.h"

TileStateWhite::TileStateWhite(std::unique_ptr<ITileBehavior> aBehavior) : mBehavior(std::move(aBehavior)) {}

void TileStateWhite::updateTile(Tile& t) {
    mBehavior->doBehavior(t);

    t.setState(TileFactory::createNextState(getColor()));
}

char TileStateWhite::getColor() const { return 'W'; }

void TileStateWhite::enter() {
    // Code to execute when entering the white state
}

void TileStateWhite::exit() {
    // Code to execute when exiting the white state
}

void TileStateWhite::forceBlue(Tile& t) { t.setState(TileFactory::createBlueState()); }