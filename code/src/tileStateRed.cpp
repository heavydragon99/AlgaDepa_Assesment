#include "tileStateRed.h"

#include "tile.h"
#include "tileStateBlue.h"

tileStateRed::tileStateRed() {
    // Constructor implementation (if needed)
}

void tileStateRed::updateTile(tile& t) {
    // Transition to the next state
    t.setState(std::make_unique<tileStateBlue>());
}

char tileStateRed::getColor() const {
    return 'R';
}

void tileStateRed::enter() {
    // Code to execute when entering the red state
}

void tileStateRed::exit() {
    // Code to execute when exiting the red state
}

void tileStateRed::forceBlue(tile& t) {
    t.setState(std::make_unique<tileStateBlue>());
}