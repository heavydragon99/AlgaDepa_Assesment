#include "tileStateGray.h"
#include "tile.h"
#include "tileStateRed.h"

tileStateGray::tileStateGray() {
    // Constructor implementation (if needed)
}

void tileStateGray::updateTile(tile* t) {
    // Transition to the next state
    t->setState(new tileStateRed());
}

char tileStateGray::getColor() const {
    return 'G';
}