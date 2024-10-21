#ifndef MEMENTO_H
#define MEMENTO_H

#include "levelData.h"

#include <memory>

class Memento {
public:
    Memento() = default;
    Memento(LevelData& aLevelData);
    ParsedGrid getGrid();
    std::vector<Artist>& getPeople();

private:
    ParsedGrid mGrid;
    std::vector<Artist> mPeople;
};

#endif // MEMENTO_H