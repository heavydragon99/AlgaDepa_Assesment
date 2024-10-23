#ifndef MEMENTO_H
#define MEMENTO_H

#include "LevelData.h"

#include <memory>

/**
 * @class Memento
 * @brief A class to store the state of LevelData.
 */
class Memento {
public:
    Memento() = default;
    Memento(LevelData& aLevelData);
    ParsedGrid getGrid();
    std::vector<Artist>& getPeople();

private:
    ParsedGrid mGrid; ///< The stored grid.
    std::vector<Artist> mPeople; ///< The stored people.
};

#endif // MEMENTO_H