#include "tileStateBlue.h"
#include "tile.h"
#include "tileStateGray.h"

tileStateBlue::tileStateBlue() {
    // Constructor implementation (if needed)
}

void tileStateBlue::updateTile(tile& t) {
    // Transition to the next state
    t.setState(std::make_unique<tileStateGray>());
}

char tileStateBlue::getColor() const {
    return 'B';
}

void tileStateBlue::enter(tile& t) {
    // Code to execute when entering the blue state
}

void tileStateBlue::exit(tile& t) {
    // Code to execute when exiting the blue state
}