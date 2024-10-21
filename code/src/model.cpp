#include "model.h"

Model::Model()
    : mLevel(std::make_unique<LevelData>()), mMementoManager(std::make_unique<MementoManager>()),
      mPathFinder(std::make_unique<PathFinder>()), mLastUpdateTime(std::chrono::steady_clock::now()),
      mSimulationRunning(true), mPathfindingAlgorithm(PathFinder::Algorithms::Breathfirst) {}

void Model::createLevel(std::vector<ParsedPerson> aPersons, ParsedGrid aGrid) {
    mLevel->buildLevelData(aPersons, aGrid);
}
void Model::setPersonData(std::vector<ParsedPerson> aPersons) { mLevel->buildPersonData(aPersons); }

void Model::setGridData(ParsedGrid aGrid) { mLevel->buildGridData(aGrid); }

LevelData& Model::getLevelData() { return *mLevel; }

void Model::updateModel() {
    if (mSimulationRunning) {
        auto now = std::chrono::steady_clock::now();
        if (now - mLastUpdateTime >= UPDATE_INTERVAL) {
            mMementoManager->addMemento(saveToMemento());
            mLastUpdateTime = now;
        }
        mLevel->updateLevelData();
    }
}

Memento Model::saveToMemento() const { return Memento(std::make_unique<LevelData>(*mLevel)); }

void Model::restoreFromMemento(Memento&& memento) { mLevel = std::move(memento.getState()); }

void Model::usePreviousMemento() { restoreFromMemento(mMementoManager->getPreviousMemento()); }

void Model::useNextMemento() { restoreFromMemento(mMementoManager->getNextMemento()); }

void Model::startStopSimulation() { mSimulationRunning = !mSimulationRunning; }

void Model::setPathfindingAlgorithm() {
    mPathfindingAlgorithm = (mPathfindingAlgorithm == PathFinder::Algorithms::Breathfirst)
                                ? PathFinder::Algorithms::Dijkstra
                                : PathFinder::Algorithms::Breathfirst;
    mPathFinder->setAlgorithm(mPathfindingAlgorithm);
}

void Model::findPath(const std::pair<int, int>& aStart, const std::pair<int, int>& aEnd) {
    mPathFinder->findPath(mLevel.get(), aStart, aEnd);
}
