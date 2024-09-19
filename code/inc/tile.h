#ifndef TILE_H
#define TILE_H

#include "iTileState.h"

class tile {
public:
    tile(iTileState* initialState);
    ~tile();

    void updateTile();

    void setState(iTileState* newState);

private:
    iTileState* state;
};

#endif // TILE_H