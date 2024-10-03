#include "tileStateYellow.h"

#include "tile.h"
#include "tileStateGray.h"
#include "tileStateBlue.h"

tileStateYellow::tileStateYellow() { mCounter = 0; }

void tileStateYellow::updateTile(tile& t) {
    // Transition to the next state
    mCounter++;
    if (mCounter == 2) {
        t.setState(std::make_unique<tileStateGray>());
    }
}

char tileStateYellow::getColor() const { return 'Y'; }

void tileStateYellow::enter() {
    // Code to execute when entering the yellow state
}

void tileStateYellow::exit() {
    // Code to execute when exiting the yellow state
}

void tileStateYellow::forceBlue(tile& t) { t.setState(std::make_unique<tileStateBlue>()); }