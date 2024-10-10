#include "tileStateGray.h"

#include "tile.h"
#include "tileFactory.h"

TileStateGray::TileStateGray(std::unique_ptr<ITileBehavior> aBehavior) : mBehavior(std::move(aBehavior)), mCounter(0) {}

void TileStateGray::updateTile(Tile& t) {
    mBehavior->doBehavior(t);

    mCounter++; // Increment the action counter
    if (mCounter >= requiredActions) {
        // Transition to the next state after 3 actions
        TileFactory factory;

        t.setState(factory.createNextState(getColor()));
    }
}

char TileStateGray::getColor() const { return 'G'; }

void TileStateGray::enter() {
    // Code to execute when entering the gray state
}

void TileStateGray::exit() {
    // Code to execute when exiting the gray state
}

void TileStateGray::forceBlue(Tile& t) {}