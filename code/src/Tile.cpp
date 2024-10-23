#include "Tile.h"

/**
 * @brief Constructs a Tile with an initial state.
 * @param initialState The initial state of the tile.
 */
Tile::Tile(std::unique_ptr<ITileState> initialState) : mState(std::move(initialState)) {}

/**
 * @brief Copy constructor.
 * @param other The Tile to copy from.
 */
Tile::Tile(const Tile& other) : mState(other.mState ? other.mState->clone() : nullptr) {}

/**
 * @brief Copy assignment operator.
 * @param other The Tile to assign from.
 * @return A reference to this Tile.
 */
Tile& Tile::operator=(const Tile& other) {
    if (this == &other) {
        return *this;
    }
    mState = other.mState ? other.mState->clone() : nullptr;
    return *this;
}

/**
 * @brief Updates the tile.
 */
void Tile::updateTile() {
    if (!mUpdated)
        mState->updateTile(*this);

    mUpdated = true;
}

/**
 * @brief Resets the update status of the tile.
 */
void Tile::resetUpdate() { mUpdated = false; }

/**
 * @brief Forces the tile to blue state.
 */
void Tile::forceBlue() { mState->forceBlue(*this); }

/**
 * @brief Sets a new state for the tile.
 * @param newState The new state to set.
 */
void Tile::setState(std::unique_ptr<ITileState> newState) {
    mState->exit();
    mState = std::move(newState);
    mState->enter();
}

/**
 * @brief Gets the color of the tile.
 * @return The color of the tile.
 */
char Tile::getColor() const { return mState->getColor(); }