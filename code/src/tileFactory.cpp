#include "tileFactory.h"

tileColor tileFactory::charToTileColor(char color) {
    switch (color) {
        case 'R':
            return tileColor::Red;
        case 'B':
            return tileColor::Blue;
        case 'Y':
            return tileColor::Yellow;
        case 'G':
            return tileColor::Gray;
        case '_':
            return tileColor::White;
        default:
            return tileColor::White; // Default to white if unknown
    }
}

std::unique_ptr<tile> tileFactory::createTile(char color) {
    tileColor tColor = charToTileColor(color);
    switch (tColor) {
        case tileColor::Red:
            return std::make_unique<tile>(std::make_unique<tileStateRed>());
        case tileColor::Blue:
            return std::make_unique<tile>(std::make_unique<tileStateBlue>());
        case tileColor::Yellow:
            return std::make_unique<tile>(std::make_unique<tileStateYellow>());
        case tileColor::Gray:
            return std::make_unique<tile>(std::make_unique<tileStateGray>());
        case tileColor::White:
            return std::make_unique<tile>(std::make_unique<tileStateWhite>());
        default:
            return nullptr;
    }
}