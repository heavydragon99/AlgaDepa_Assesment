#include "tileStateWhite.h"
#include "tile.h"
#include "tileStateYellow.h"

tileStateWhite::tileStateWhite() {
    // Constructor implementation (if needed)
}

void tileStateWhite::updateTile(tile& t) {
    // Transition to the next state
    t.setState(std::make_unique<tileStateYellow>());
}

char tileStateWhite::getColor() const {
    return 'W';
}

void tileStateWhite::enter(tile& t) {
    // Code to execute when entering the white state
}

void tileStateWhite::exit(tile& t) {
    // Code to execute when exiting the white state
}