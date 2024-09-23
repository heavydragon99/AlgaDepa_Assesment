#ifndef TILE_H
#define TILE_H

#include "iTileState.h"

#include <memory>

class tile {
public:
    tile(std::unique_ptr<iTileState> initialState);
    ~tile() = default;

    void updateTile();
    void setState(std::unique_ptr<iTileState> newState);
    char getColor() const;

private:
    std::unique_ptr<iTileState> state;
};

#endif // TILE_H