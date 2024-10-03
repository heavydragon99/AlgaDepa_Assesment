#include "tileStateBlue.h"

#include "tile.h"
#include "tileFactory.h"

tileStateBlue::tileStateBlue(std::unique_ptr<iTileBehavior> aBehavior) : mBehavior(std::move(aBehavior)) {}

void tileStateBlue::updateTile(tile& t) {
    mBehavior->doBehavior();

    // Transition to the next state after 3 actions
    tileFactory factory;

    t.setState(factory.createNextState(getColor()));
}

char tileStateBlue::getColor() const { return 'B'; }

void tileStateBlue::enter() {
    // Code to execute when entering the blue state
}

void tileStateBlue::exit() {
    // Code to execute when exiting the blue state
}

void tileStateBlue::forceBlue(tile& t) {
    // Do nothing
}