#include "tileStateYellow.h"

#include "tile.h"
#include "tileFactory.h"

tileStateYellow::tileStateYellow(std::unique_ptr<iTileBehavior> aBehavior) : mBehavior(std::move(aBehavior)), mCounter(0) {}

void tileStateYellow::updateTile(tile& t) {
    mBehavior->doBehavior();

    mCounter++; // Increment the action counter
    if (mCounter >= requiredActions) {
        // Transition to the next state after 3 actions
        tileFactory factory;

        t.setState(factory.createNextState(getColor()));
    }
}

char tileStateYellow::getColor() const { return 'Y'; }

void tileStateYellow::enter() {
    // Code to execute when entering the yellow state
}

void tileStateYellow::exit() {
    // Code to execute when exiting the yellow state
}

void tileStateYellow::forceBlue(tile& t) { }