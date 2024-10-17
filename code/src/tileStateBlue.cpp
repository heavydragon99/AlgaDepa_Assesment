#include "tileStateBlue.h"

#include "tile.h"
#include "tileFactory.h"

TileStateBlue::TileStateBlue(std::unique_ptr<ITileBehavior> aBehavior) : mBehavior(std::move(aBehavior)), mCounter(0) {}

std::unique_ptr<ITileState> TileStateBlue::clone() const {
    return std::make_unique<TileStateBlue>(mBehavior->clone());
}

void TileStateBlue::updateTile(Tile& t) {
    mBehavior->doBehavior(t);
    mCounter++;

    if (mCounter >= 3) {
        // Transition to the next state after 3 actions
        t.setState(TileFactory::createNextState(getColor()));
    }
}

char TileStateBlue::getColor() const { return 'B'; }

void TileStateBlue::enter() {
    // Code to execute when entering the blue state
}

void TileStateBlue::exit() {
    // Code to execute when exiting the blue state
}

void TileStateBlue::forceBlue(Tile& t) { t.setState(TileFactory::createBlueState()); }