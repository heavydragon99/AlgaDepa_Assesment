#ifndef MODEL_H
#define MODEL_H

#include "Memento.h"
#include "MementoManager.h"
#include "PathFinder.h"
#include "LevelData.h"
#include "Structs.h"

#include <chrono>
#include <memory>

/**
 * @class Model
 * @brief Manages the level data, mementos, and pathfinding for the application.
 */
class Model {
public:
    Model();
    void createLevel(std::vector<ParsedPerson> aPersons, ParsedGrid aGrid);
    void setPersonData(std::vector<ParsedPerson> aPersons);
    void setGridData(ParsedGrid aGrid);
    LevelData& getLevelData();

    void updateModel();

    void usePreviousMemento();
    void useNextMemento();

    void findPath(const std::pair<int, int>& aStart, const std::pair<int, int>& aEnd);

    void updateTile(int aX, int aY);

    PathFinder& getPathFinder();

private:
    Memento saveToMemento() const;
    void restoreFromMemento(Memento&& memento);

private:
    std::unique_ptr<LevelData> mLevel; ///< Unique pointer to the level data.
    std::unique_ptr<MementoManager> mMementoManager; ///< Unique pointer to the memento manager.
    std::unique_ptr<PathFinder> mPathFinder; ///< Unique pointer to the pathfinder.
    std::chrono::time_point<std::chrono::steady_clock> mLastUpdateTime; ///< Last update time.
    static constexpr std::chrono::milliseconds MEMENTO_UPDATE_INTERVAL{600}; ///< Interval for memento updates.
};

#endif // MODEL_H
