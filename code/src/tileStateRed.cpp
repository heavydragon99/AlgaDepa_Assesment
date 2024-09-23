#include "tileStateRed.h"
#include "tileStateWhite.h"
#include "tile.h"

tileStateRed::tileStateRed() {
    // Constructor implementation (if needed)
}

void tileStateRed::updateTile(tile* t) {
    // Transition to the next state
    t->setState(std::make_unique<tileStateWhite>());
}

char tileStateRed::getColor() const {
    return 'R';
}

void tileStateRed::enter(tile* t) {
    // Code to execute when entering the red state
}

void tileStateRed::exit(tile* t) {
    // Code to execute when exiting the red state
}