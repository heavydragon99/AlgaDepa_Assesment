#ifndef TILEFACTORY_H
#define TILEFACTORY_H

#include "tile.h"
#include "tileStateRed.h"
#include "tileStateBlue.h"
#include "tileStateYellow.h"
#include "tileStateGray.h"
#include "tileStateWhite.h"

#include <memory>

enum class tileColor {
    Red,
    Blue,
    Yellow,
    Gray,
    White
};

class tileFactory {
public:
    static std::unique_ptr<tile> createTile(tileColor color);
};

#endif // TILEFACTORY_H