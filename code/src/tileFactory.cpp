#include "tileFactory.h"

std::unique_ptr<tile> tileFactory::createTile(tileColor color) {
    switch (color) {
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