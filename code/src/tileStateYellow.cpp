#include "tileStateYellow.h"
#include "tile.h"
#include "tileStateBlue.h"

tileStateYellow::tileStateYellow() {
    // Constructor implementation (if needed)
}

void tileStateYellow::updateTile(tile* t) {
    // Transition to the next state
    t->setState(new tileStateBlue());
}

char tileStateYellow::getColor() const {
    return 'Y';
}