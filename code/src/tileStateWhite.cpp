#include "tileStateWhite.h"

#include "tile.h"
#include "tileFactory.h"

tileStateWhite::tileStateWhite(std::unique_ptr<iTileBehavior> aBehavior) : mBehavior(std::move(aBehavior)) {}

void tileStateWhite::updateTile(tile& t) {
    mBehavior->doBehavior();

    tileFactory factory;
    t.setState(factory.createNextState(getColor()));
}

char tileStateWhite::getColor() const { return 'W'; }

void tileStateWhite::enter() {
    // Code to execute when entering the white state
}

void tileStateWhite::exit() {
    // Code to execute when exiting the white state
}

void tileStateWhite::forceBlue(tile& t) {  }