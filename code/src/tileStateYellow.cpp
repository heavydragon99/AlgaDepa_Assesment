#include "tileStateYellow.h"
#include "tile.h"
#include "tileStateBlue.h"

tileStateYellow::tileStateYellow() {
    // Constructor implementation (if needed)
}

void tileStateYellow::updateTile(tile* t) {
    // Transition to the next state
    t->setState(std::make_unique<tileStateBlue>());
}

char tileStateYellow::getColor() const {
    return 'Y';
}

void tileStateYellow::enter(tile* t) {
    // Code to execute when entering the yellow state
}

void tileStateYellow::exit(tile* t) {
    // Code to execute when exiting the yellow state
}