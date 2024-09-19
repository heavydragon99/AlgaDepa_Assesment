#include "tileStateRed.h"
#include "tile.h"
#include "tileStateBlue.h"

void tileStateRed::updateTile(tile* t) {
    // Transition to the next state
    t->setState(new tileStateBlue());
}