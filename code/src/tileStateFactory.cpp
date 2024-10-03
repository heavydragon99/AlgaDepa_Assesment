// TileStateFactory.cpp
#include "TileStateFactory.h"
#include "tileStateBlue.h"
#include "tileStateYellow.h"

std::unique_ptr<iTileState> TileStateFactory::createNextState(char currentColor) {
    if (currentColor == 'B') {
        return std::make_unique<tileStateYellow>();
    } else if (currentColor == 'Y') {
        // Define further transitions as needed
        // return std::make_unique<NextState>();
    }
    return nullptr; // Default case
}