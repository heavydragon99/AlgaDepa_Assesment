#include "tileStateGray.h"
#include "tile.h"
#include "tileStateRed.h"

tileStateGray::tileStateGray() {
    // Constructor implementation (if needed)
}

void tileStateGray::updateTile(tile& t) {
    // Transition to the next state
    t.setState(std::make_unique<tileStateRed>());
}

char tileStateGray::getColor() const {
    return 'G';
}

void tileStateGray::enter(tile& t) {
    // Code to execute when entering the gray state
}

void tileStateGray::exit(tile& t) {
    // Code to execute when exiting the gray state
}