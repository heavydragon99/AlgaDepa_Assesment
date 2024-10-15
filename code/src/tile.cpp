#include "tile.h"

Tile::Tile(std::unique_ptr<ITileState> initialState) : mState(std::move(initialState)) {}

Tile::Tile(const Tile& other) : mState(other.mState ? other.mState->clone() : nullptr) {}

Tile& Tile::operator=(const Tile& other) {
    if (this == &other) {
        return *this;
    }
    mState = other.mState ? other.mState->clone() : nullptr;
    return *this;
}

void Tile::updateTile() { mState->updateTile(*this); }

void Tile::forceBlue() { mState->forceBlue(*this); }

void Tile::setState(std::unique_ptr<ITileState> newState) {
    mState->exit();
    mState = std::move(newState);
    mState->enter();
}

char Tile::getColor() const { return mState->getColor(); }
