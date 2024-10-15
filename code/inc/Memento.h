#ifndef MEMENTO_H
#define MEMENTO_H

#include "levelData.h"

#include <memory>

class Memento {
public:
    Memento(std::unique_ptr<LevelData> state);
    std::unique_ptr<LevelData> getState();

private:
    std::unique_ptr<LevelData> mState;
};

#endif // MEMENTO_H