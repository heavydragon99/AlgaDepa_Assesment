// TileStateFactory.h
#ifndef TILESTATEFACTORY_H
#define TILESTATEFACTORY_H

#include <memory>
#include "iTileState.h"

class TileStateFactory {
public:
    std::unique_ptr<iTileState> createNextState(char currentColor);
};

#endif // TILESTATEFACTORY_H