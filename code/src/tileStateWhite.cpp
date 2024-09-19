#include "tileStateWhite.h"
#include "tile.h"
#include "tileStateRed.h"

void tileStateWhite::updateTile(tile* t) {
    // Transition to the next state
    t->setState(new tileStateRed());
}