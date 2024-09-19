#include "tileStateRed.h"
#include "tileStateWhite.h"
#include "tile.h"

tileStateRed::tileStateRed() {
    // Constructor implementation (if needed)
}

void tileStateRed::updateTile(tile* t) {
    // Transition to the next state
    t->setState(new tileStateWhite());
}

char tileStateRed::getColor() const {
    return 'R';
}