#include "tileStateBlue.h"

#include "tile.h"
#include "tileFactory.h"

TileStateBlue::TileStateBlue(std::unique_ptr<ITileBehavior> aBehavior) : mBehavior(std::move(aBehavior)) {}

void TileStateBlue::updateTile(Tile& t) {
    mBehavior->doBehavior(t);

    // Transition to the next state after 3 actions
    TileFactory factory;

    t.setState(factory.createNextState(getColor()));
}

char TileStateBlue::getColor() const { return 'B'; }

void TileStateBlue::enter() {
    // Code to execute when entering the blue state
}

void TileStateBlue::exit() {
    // Code to execute when exiting the blue state
}

void TileStateBlue::forceBlue(Tile& t) {
    // Do nothing
}