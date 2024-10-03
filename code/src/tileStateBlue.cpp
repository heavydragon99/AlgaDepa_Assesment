#include "tileStateBlue.h"

#include "tile.h"

tileStateBlue::tileStateBlue(std::unique_ptr<iTileBehavior> aBehavior)
    : mBehavior(std::move(aBehavior)), mCounter(0) {}

void tileStateBlue::updateTile(tile& t) {
    // Transition to the next state
}

char tileStateBlue::getColor() const {
    return 'B';
}

void tileStateBlue::enter() {
    // Code to execute when entering the blue state
}

void tileStateBlue::exit() {
    // Code to execute when exiting the blue state
}

void tileStateBlue::forceBlue(tile& t) {
    // Do nothing
}