#include "tileStateYellow.h"

#include "tile.h"
#include "tileFactory.h"

TileStateYellow::TileStateYellow(std::unique_ptr<ITileBehavior> aBehavior)
    : mBehavior(std::move(aBehavior)), mCounter(0) {}

std::unique_ptr<ITileState> TileStateYellow::clone() const {
    return std::make_unique<TileStateYellow>(mBehavior->clone());
}

void TileStateYellow::updateTile(Tile& t) {
        if (mBehavior != nullptr) {
        mBehavior->doBehavior(t);
    }

    mCounter++; // Increment the action counter
    if (mCounter >= requiredActions) {
        // Transition to the next state after required amount of actions
        t.setState(TileFactory::createNextState(getColor()));
    }
}

char TileStateYellow::getColor() const { return 'Y'; }

void TileStateYellow::enter() {
    // Code to execute when entering the yellow state
}

void TileStateYellow::exit() {
    // Code to execute when exiting the yellow state
}

void TileStateYellow::forceBlue(Tile& t) { t.setState(TileFactory::createBlueState()); }