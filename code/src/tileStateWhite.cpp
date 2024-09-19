#include "tileStateWhite.h"
#include "tile.h"
#include "tileStateYellow.h"

tileStateWhite::tileStateWhite() {
    // Constructor implementation (if needed)
}

void tileStateWhite::updateTile(tile* t) {
    // Transition to the next state
    t->setState(new tileStateYellow());
}

char tileStateWhite::getColor() const {
    return 'W';
}