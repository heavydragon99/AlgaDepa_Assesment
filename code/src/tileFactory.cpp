#include "tileFactory.h"

#include "tileStateBlue.h"
#include "tileStateGray.h"
#include "tileStateRed.h"
#include "tileStateWhite.h"
#include "tileStateYellow.h"

#include "addArtistBehavior.h"
#include "iTileBehavior.h"
#include "infectTilesBehavior.h"
#include "killArtistBehavior.h"

LevelData* TileFactory::mLevelData = nullptr;

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

void TileFactory::setLevelData(LevelData* aLevelData) {
    mLevelData = aLevelData;
}

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

std::unique_ptr<ITileBehavior> TileFactory::createBehavior(TileColor aColor) {
    switch (aColor) {
    case TileColor::Red:
        return std::make_unique<KillArtistBehavior>(mLevelData);
    case TileColor::Blue:
        return std::make_unique<InfectTilesBehavior>(mLevelData);
    case TileColor::Yellow:
        return std::make_unique<AddArtistBehavior>(mLevelData);
    case TileColor::Gray:
        return std::make_unique<ITileBehavior>();
    case TileColor::White:
        return std::make_unique<ITileBehavior>();
    default:
        return nullptr;
    }
}