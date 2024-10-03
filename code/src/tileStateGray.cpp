#include "tileStateGray.h"
#include "tile.h"
#include "tileStateBlue.h"
#include "tileStateRed.h"

tileStateGray::tileStateGray() { mCounter = 0; }

void tileStateGray::updateTile(tile& t) {
    // Transition to the next state
    mCounter++;
    if (mCounter == 3) {
        t.setState(std::make_unique<tileStateRed>());
    }
}

char tileStateGray::getColor() const { return 'G'; }

void tileStateGray::enter() {
    // Code to execute when entering the gray state
}

void tileStateGray::exit() {
    // Code to execute when exiting the gray state
}

void tileStateGray::forceBlue(tile& t) { t.setState(std::make_unique<tileStateBlue>()); }