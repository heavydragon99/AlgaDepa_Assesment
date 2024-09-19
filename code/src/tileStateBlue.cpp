#include "tileStateGray.h"
#include "tile.h"
#include "tileStateBlue.h"

tileStateBlue::tileStateBlue() {
    // Constructor implementation (if needed)
}

void tileStateBlue::updateTile(tile* t) {
    // Transition to the next state
    t->setState(new tileStateGray());
}

char tileStateBlue::getColor() const {
    return 'B';
}