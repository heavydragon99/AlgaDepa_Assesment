#ifndef MEMENTO_H
#define MEMENTO_H

#include "levelData.h"

#include <memory>

class Memento {
public:
    Memento() = default;
    Memento(LevelData& aLevelData);
    ParsedGrid getState();

private:
    ParsedGrid mGrid;
};

#endif // MEMENTO_H