#include "tileStateBlue.h"

#include "tile.h"
#include "tileStateYellow.h"

tileStateBlue::tileStateBlue() {
    // Constructor implementation (if needed)
}

void tileStateBlue::updateTile(tile& t) {
    // Transition to the next state
    t.setState(std::make_unique<tileStateYellow>());
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