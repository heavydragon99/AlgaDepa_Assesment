#ifndef TILE_H
#define TILE_H

#include "iTileState.h"

#include <memory>

class Tile {
public:
    Tile(std::unique_ptr<ITileState> initialState);
    ~Tile() = default;

    void updateTile();
    void forceBlue();
    void setState(std::unique_ptr<ITileState> newState);
    char getColor() const;

private:
    std::unique_ptr<ITileState> mState;
};

#endif // TILE_H