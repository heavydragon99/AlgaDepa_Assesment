#include "tileStateYellow.h"
#include "tile.h"
#include "tileStateGray.h"

void tileStateYellow::updateTile(tile* t) {
    // Transition to the next state
    t->setState(new tileStateGray());
}