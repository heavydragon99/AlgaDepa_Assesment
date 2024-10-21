#ifndef MODEL_H
#define MODEL_H

#include "Memento.h"
#include "MementoManager.h"
#include "PathFinder.h"
#include "levelData.h"
#include "structs.h"

#include <chrono>
#include <memory>

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
    std::unique_ptr<LevelData> mLevel;
    std::unique_ptr<MementoManager> mMementoManager;
    std::unique_ptr<PathFinder> mPathFinder;
    std::chrono::time_point<std::chrono::steady_clock> mLastUpdateTime;
    static constexpr std::chrono::milliseconds MEMENTO_UPDATE_INTERVAL{600}; // Define the interval here
};

#endif // MODEL_H
