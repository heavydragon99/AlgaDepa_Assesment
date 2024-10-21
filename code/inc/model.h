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

    void startStopSimulation();
    void setPathfindingAlgorithm();
    void findPath(const std::pair<int, int>& aStart, const std::pair<int, int>& aEnd);

private:
    Memento saveToMemento() const;
    void restoreFromMemento(Memento&& memento);

private:
    std::unique_ptr<LevelData> mLevel;
    std::unique_ptr<MementoManager> mMementoManager;
    std::unique_ptr<PathFinder> mPathFinder;
    std::chrono::time_point<std::chrono::steady_clock> mLastUpdateTime;
    static constexpr std::chrono::seconds UPDATE_INTERVAL{1}; // Define the interval here
    bool mSimulationRunning;
    PathFinder::Algorithms mPathfindingAlgorithm;
};

#endif // MODEL_H
