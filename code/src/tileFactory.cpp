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

std::unique_ptr<tile> tileFactory::createTile(char color) {
    TileColor tColor = charToTileColor(color);
    std::unique_ptr<iTileBehavior> behavior = createBehavior(tColor);
    switch (tColor) {
    case TileColor::Red:
        return std::make_unique<tile>(std::make_unique<tileStateRed>(std::move(behavior)));
    case TileColor::Blue:
        return std::make_unique<tile>(std::make_unique<tileStateBlue>(std::move(behavior)));
    case TileColor::Yellow:
        return std::make_unique<tile>(std::make_unique<tileStateYellow>(std::move(behavior)));
    case TileColor::Gray:
        return std::make_unique<tile>(std::make_unique<tileStateGray>(std::move(behavior)));
    case TileColor::White:
        return std::make_unique<tile>(std::make_unique<tileStateWhite>(std::move(behavior)));
    default:
        return nullptr;
    }
}

std::unique_ptr<iTileState> tileFactory::createNextState(char currentColor) {
    TileColor tColor = charToTileColor(currentColor);
    std::unique_ptr<iTileBehavior> behavior = createBehavior(tColor);
    switch (tColor) {
    case TileColor::Red:
        return std::make_unique<tileStateBlue>(std::move(behavior));
    case TileColor::Blue:
        return std::make_unique<tileStateYellow>(std::move(behavior));
    case TileColor::Yellow:
        return std::make_unique<tileStateGray>(std::move(behavior));
    case TileColor::Gray:
        return std::make_unique<tileStateRed>(std::move(behavior));
    case TileColor::White:
        return std::make_unique<tileStateWhite>(std::move(behavior));
    default:
        return nullptr;
    }
}

TileColor tileFactory::charToTileColor(char color) {
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

std::unique_ptr<iTileBehavior> tileFactory::createBehavior(TileColor aColor) {
    switch (aColor) {
    case TileColor::Red:
        return std::make_unique<killArtistBehavior>();
    case TileColor::Blue:
        return std::make_unique<infectTilesBehavior>();
    case TileColor::Yellow:
        return std::make_unique<addArtistBehavior>();
    case TileColor::Gray:
        return std::make_unique<iTileBehavior>();
    case TileColor::White:
        return std::make_unique<iTileBehavior>();
    default:
        return nullptr;
    }
}