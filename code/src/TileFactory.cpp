#include "TileFactory.h"

#include "ITileState.h"
#include "ITileBehavior.h"

LevelData* TileFactory::mLevelData = nullptr;

/**
 * @brief Creates a tile based on the given color.
 * @param color Character representing the color of the tile.
 * @return A unique pointer to the created Tile.
 */
std::unique_ptr<Tile> TileFactory::createTile(char color) {
    TileColor tColor = charToTileColor(color);
    std::unique_ptr<ITileBehavior> behavior = createBehavior(tColor);
    switch (tColor) {
    case TileColor::Red:
        return std::make_unique<Tile>(std::make_unique<TileStateRed>(std::move(behavior)));
    case TileColor::Blue:
        return std::make_unique<Tile>(std::make_unique<TileStateBlue>(std::move(behavior)));
    case TileColor::Yellow:
        return std::make_unique<Tile>(std::make_unique<TileStateYellow>(std::move(behavior)));
    case TileColor::Gray:
        return std::make_unique<Tile>(std::make_unique<TileStateGray>(std::move(behavior)));
    case TileColor::White:
        return std::make_unique<Tile>(std::make_unique<TileStateWhite>(std::move(behavior)));
    default:
        return nullptr;
    }
}

/**
 * @brief Creates the next state of a tile based on the current color.
 * @param currentColor Character representing the current color of the tile.
 * @return A unique pointer to the created ITileState.
 */
std::unique_ptr<ITileState> TileFactory::createNextState(char currentColor) {
    TileColor tColor = charToTileColor(currentColor);
    std::unique_ptr<ITileBehavior> behavior = createBehavior(tColor);
    switch (tColor) {
    case TileColor::Red:
        return std::make_unique<TileStateBlue>(std::move(behavior));
    case TileColor::Blue:
        return std::make_unique<TileStateYellow>(std::move(behavior));
    case TileColor::Yellow:
        return std::make_unique<TileStateGray>(std::move(behavior));
    case TileColor::Gray:
        return std::make_unique<TileStateRed>(std::move(behavior));
    case TileColor::White:
        return std::make_unique<TileStateWhite>(std::move(behavior));
    default:
        return nullptr;
    }
}

/**
 * @brief Creates a blue state tile.
 * @return A unique pointer to the created ITileState.
 */
std::unique_ptr<ITileState> TileFactory::createBlueState() {
    TileColor tColor = charToTileColor('B');
    std::unique_ptr<ITileBehavior> behavior = createBehavior(tColor);
    return std::make_unique<TileStateBlue>(std::move(behavior));
}

/**
 * @brief Sets the level data for the tile factory.
 * @param aLevelData Pointer to the LevelData object.
 */
void TileFactory::setLevelData(LevelData* aLevelData) {
    mLevelData = aLevelData;
}

/**
 * @brief Converts a character to a TileColor enum.
 * @param color Character representing the color.
 * @return Corresponding TileColor enum value.
 */
TileColor TileFactory::charToTileColor(char color) {
    switch (color) {
    case 'R':
        return TileColor::Red;
    case 'B':
        return TileColor::Blue;
    case 'Y':
        return TileColor::Yellow;
    case 'G':
        return TileColor::Gray;
    case '_':
        return TileColor::White;
    default:
        return TileColor::White; // Default to white if unknown
    }
}

/**
 * @brief Creates a behavior based on the tile color.
 * @param aColor TileColor enum value.
 * @return A unique pointer to the created ITileBehavior.
 */
std::unique_ptr<ITileBehavior> TileFactory::createBehavior(TileColor aColor) {
    switch (aColor) {
    case TileColor::Red:
        return std::make_unique<KillArtistBehavior>(mLevelData);
    case TileColor::Blue:
        return std::make_unique<InfectTilesBehavior>(mLevelData);
    case TileColor::Yellow:
        return std::make_unique<AddArtistBehavior>(mLevelData);
    case TileColor::Gray:
        return std::make_unique<NoOpBehavior>();
    case TileColor::White:
        return std::make_unique<NoOpBehavior>();
    default:
        return nullptr;
    }
}