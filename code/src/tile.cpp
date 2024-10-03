#include "tile.h"
#include "TileStateFactory.h"

tile::tile(std::unique_ptr<iTileState> initialState) : state(std::move(initialState)) {}

void tile::updateTile() { state->updateTile(*this); }

void tile::setState(std::unique_ptr<iTileState> newState) {
    state->exit();
    state = std::move(newState);
    state->enter();
}

char tile::getColor() const { return state->getColor(); }