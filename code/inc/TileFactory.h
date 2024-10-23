#ifndef TILEFACTORY_H
#define TILEFACTORY_H

#include "Tile.h"
#include "ITileBehavior.h"
#include "LevelData.h"

#include <memory>

/**
 * @enum TileColor
 * @brief Represents the color of a tile.
 */
enum class TileColor {
    Red,    /**< Red color */
    Blue,   /**< Blue color */
    Yellow, /**< Yellow color */
    Gray,   /**< Gray color */
    White   /**< White color */
};

/**
 * @class TileFactory
 * @brief Factory class for creating tiles and their states.
 */
class TileFactory {
public:
    static std::unique_ptr<Tile> createTile(char color);
    static std::unique_ptr<ITileState> createNextState(char currentColor);
    static std::unique_ptr<ITileState> createBlueState();
    static void setLevelData(LevelData* aLevelData);
private:
    static TileColor charToTileColor(char color);
    static std::unique_ptr<ITileBehavior> createBehavior(TileColor aColor);

    static LevelData* mLevelData;    
};

#endif // TILEFACTORY_H