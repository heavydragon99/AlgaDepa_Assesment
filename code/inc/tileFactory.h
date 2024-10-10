#ifndef TILEFACTORY_H
#define TILEFACTORY_H

#include "tile.h"
#include "iTileBehavior.h"
#include "levelData.h"

#include <memory>

enum class TileColor {
    Red,
    Blue,
    Yellow,
    Gray,
    White
};

class TileFactory {
public:
    static std::unique_ptr<Tile> createTile(char color);
    static std::unique_ptr<ITileState> createNextState(char currentColor);
    static void setLevelData(LevelData* aLevelData);
private:
    static TileColor charToTileColor(char color);
    static std::unique_ptr<ITileBehavior> createBehavior(TileColor aColor);

    static LevelData* mLevelData;    
};

#endif // TILEFACTORY_H