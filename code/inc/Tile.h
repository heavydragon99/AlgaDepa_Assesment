#ifndef TILE_H
#define TILE_H

#include "ITileState.h"
#include <memory>

/**
 * @class Tile
 * @brief Represents a tile that can change its state.
 */
class Tile {
public:
    Tile(std::unique_ptr<ITileState> initialState);
    ~Tile() = default;

    Tile(const Tile& other);
    Tile& operator=(const Tile& other);

    void updateTile();
    void forceBlue();
    void setState(std::unique_ptr<ITileState> newState);
    char getColor() const;
    void resetUpdate();

private:
    std::unique_ptr<ITileState> mState; ///< The current state of the tile.
    bool mUpdated = true;               ///< Indicates whether the tile has been updated.
};

#endif // TILE_H