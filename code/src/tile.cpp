#include "tile.h"

Tile::Tile(std::unique_ptr<ITileState> initialState) : state(std::move(initialState)) {}

void Tile::updateTile() { state->updateTile(*this); }

void Tile::setState(std::unique_ptr<ITileState> newState) {
    state->exit();
    state = std::move(newState);
    state->enter();
}

char Tile::getColor() const { return state->getColor(); }