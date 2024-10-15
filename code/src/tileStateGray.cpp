#include "tileStateGray.h"

#include "tile.h"
#include "tileFactory.h"

TileStateGray::TileStateGray(std::unique_ptr<ITileBehavior> aBehavior) : mBehavior(std::move(aBehavior)), mCounter(0) {}

std::unique_ptr<ITileState> TileStateGray::clone() const { return std::make_unique<TileStateGray>(mBehavior->clone()); }

void TileStateGray::updateTile(Tile& t) {
    if (mBehavior != nullptr) {
        mBehavior->doBehavior(t);
    }
    mCounter++; // Increment the action counter
    if (mCounter >= requiredActions) {
        // Transition to the next state after required amount of actions
        t.setState(TileFactory::createNextState(getColor()));
    }
}

char TileStateGray::getColor() const { return 'G'; }

void TileStateGray::enter() {
    // Code to execute when entering the gray state
}

void TileStateGray::exit() {
    // Code to execute when exiting the gray state
}

void TileStateGray::forceBlue(Tile& t) { t.setState(TileFactory::createBlueState()); }