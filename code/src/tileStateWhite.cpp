#include "tileStateWhite.h"

#include "tile.h"
#include "tileFactory.h"

TileStateWhite::TileStateWhite(std::unique_ptr<ITileBehavior> aBehavior) : mBehavior(std::move(aBehavior)) {}

std::unique_ptr<ITileState> TileStateWhite::clone() const {
    auto clonedBehavior = mBehavior ? mBehavior->clone() : nullptr;
    return std::make_unique<TileStateWhite>(std::move(clonedBehavior));
}

void TileStateWhite::updateTile(Tile& t) {
    if (mBehavior != nullptr) {
        mBehavior->doBehavior(t);
    }

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