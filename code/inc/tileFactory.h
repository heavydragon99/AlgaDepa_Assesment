#ifndef TILEFACTORY_H
#define TILEFACTORY_H

#include "tile.h"

#include "iTileBehavior.h"

#include <memory>

enum class TileColor {
    Red,
    Blue,
    Yellow,
    Gray,
    White
};

class tileFactory {
public:
    static std::unique_ptr<tile> createTile(char color);
    static std::unique_ptr<iTileState> createNextState(char currentColor);
private:
    static TileColor charToTileColor(char color);
    static std::unique_ptr<iTileBehavior> createBehavior(TileColor aColor);
    
};

#endif // TILEFACTORY_H