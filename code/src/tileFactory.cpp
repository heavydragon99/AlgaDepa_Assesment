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
            return std::make_unique<tile>(new tileStateRed());
        case tileColor::Blue:
            return std::make_unique<tile>(new tileStateBlue());
        case tileColor::Yellow:
            return std::make_unique<tile>(new tileStateYellow());
        case tileColor::Gray:
            return std::make_unique<tile>(new tileStateGray());
        case tileColor::White:
            return std::make_unique<tile>(new tileStateWhite());
        default:
            return nullptr;
    }
}