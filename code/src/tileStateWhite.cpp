#include "tileStateWhite.h"

#include "tile.h"
#include "tileStateBlue.h"

tileStateWhite::tileStateWhite() {
    // Constructor implementation (if needed)
}

void tileStateWhite::updateTile(tile& t) {
    // Transition to the next state
}

char tileStateWhite::getColor() const {
    return 'W';
}

void tileStateWhite::enter() {
    // Code to execute when entering the white state
}

void tileStateWhite::exit() {
    // Code to execute when exiting the white state
}

void tileStateWhite::forceBlue(tile& t) {
    t.setState(std::make_unique<tileStateBlue>());
}