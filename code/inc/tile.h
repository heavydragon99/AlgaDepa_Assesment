#ifndef TILE_H
#define TILE_H

#include "iTileState.h"

#include <memory>

class Tile {
public:
    Tile(std::unique_ptr<ITileState> initialState);
    ~Tile() = default;

    // Copy constructor
    Tile(const Tile& other);

    // Copy assignment operator
    Tile& operator=(const Tile& other);

    void updateTile();
    void forceBlue();
    void setState(std::unique_ptr<ITileState> newState);
    char getColor() const;

    void resetUpdate();

private:
    std::unique_ptr<ITileState> mState;

    bool mUpdated = false;
};

#endif // TILE_H
