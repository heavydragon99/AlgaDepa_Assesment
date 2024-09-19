#include "tile.h"

tile::tile(iTileState* initialState) : state(initialState) {}

tile::~tile() {
    delete state;
}

void tile::updateTile() {
    state->updateTile(this);
}

void tile::setState(iTileState* newState) {
    delete state;
    state = newState;
}