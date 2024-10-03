#include "tileStateGray.h"

#include "tile.h"
#include "tileFactory.h"

tileStateGray::tileStateGray(std::unique_ptr<iTileBehavior> aBehavior) : mBehavior(std::move(aBehavior)), mCounter(0) {}

void tileStateGray::updateTile(tile& t) {
    mBehavior->doBehavior();

    mCounter++; // Increment the action counter
    if (mCounter >= requiredActions) {
        // Transition to the next state after 3 actions
        tileFactory factory;

        t.setState(factory.createNextState(getColor()));
    }
}

char tileStateGray::getColor() const { return 'G'; }

void tileStateGray::enter() {
    // Code to execute when entering the gray state
}

void tileStateGray::exit() {
    // Code to execute when exiting the gray state
}

void tileStateGray::forceBlue(tile& t) {}