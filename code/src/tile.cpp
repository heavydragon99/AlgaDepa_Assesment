#include "tile.h"

tile::tile(std::unique_ptr<iTileState> initialState) : state(std::move(initialState)) {
    state->enter(*this);
}

void tile::updateTile() {
    state->updateTile(*this);
}

void tile::setState(std::unique_ptr<iTileState> newState) {
    state->exit(*this);
    state = std::move(newState);
    state->enter(*this);
}

char tile::getColor() const {
    return state->getColor();
}