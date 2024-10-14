#include "tile.h"

Tile::Tile(std::unique_ptr<ITileState> initialState) : mState(std::move(initialState)) {}

void Tile::updateTile() { mState->updateTile(*this); }

void Tile::forceBlue() { mState->forceBlue(*this); }

void Tile::setState(std::unique_ptr<ITileState> newState) {
    mState->exit();
    mState = std::move(newState);
    mState->enter();
}

char Tile::getColor() const { return mState->getColor(); }
