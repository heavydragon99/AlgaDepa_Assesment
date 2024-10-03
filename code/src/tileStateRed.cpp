#include "tileStateRed.h"

#include "tile.h"
#include "tileFactory.h"

tileStateRed::tileStateRed(std::unique_ptr<iTileBehavior> aBehavior) : mBehavior(std::move(aBehavior)) {}


void tileStateRed::updateTile(tile& t) {
    mBehavior->doBehavior();

    tileFactory factory;
    t.setState(factory.createNextState(getColor()));
}

char tileStateRed::getColor() const { return 'R'; }

void tileStateRed::enter() {
    // Code to execute when entering the red state
}

void tileStateRed::exit() {
    // Code to execute when exiting the red state
}

void tileStateRed::forceBlue(tile& t) { }