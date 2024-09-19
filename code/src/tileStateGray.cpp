#include "tileStateGray.h"
#include "tile.h"
#include "tileStateWhite.h"

void tileStateGray::updateTile(tile* t) {
    // Transition to the next state
    t->setState(new tileStateWhite());
}