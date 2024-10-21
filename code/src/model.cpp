#include "model.h"

#include "configuration.h"

Model::Model()
    : mLevel(std::make_unique<LevelData>()), mMementoManager(std::make_unique<MementoManager>()),
      mPathFinder(std::make_unique<PathFinder>()), mLastUpdateTime(std::chrono::steady_clock::now()) {}

void Model::createLevel(std::vector<ParsedPerson> aPersons, ParsedGrid aGrid) {
    mLevel->buildLevelData(aPersons, aGrid);
}

LevelData& Model::getLevelData() { return *mLevel; }

void Model::updateModel() {
    if (!Configuration::getInstance().getConfig("PauseArtists")) {
        auto now = std::chrono::steady_clock::now();
        if (now - mLastUpdateTime >= UPDATE_INTERVAL) {
            mMementoManager->addMemento(saveToMemento());
            mLastUpdateTime = now;
        }
        mLevel->updateLevelData();
    }
}

void Model::updateTile(int aX, int aY) { mLevel->updateTile(aX, aY); }

Memento Model::saveToMemento() const { return Memento(std::make_unique<LevelData>(*mLevel)); }

void Model::restoreFromMemento(Memento&& memento) { mLevel = std::move(memento.getState()); }

void Model::usePreviousMemento() { restoreFromMemento(mMementoManager->getPreviousMemento()); }

void Model::useNextMemento() { restoreFromMemento(mMementoManager->getNextMemento()); }

void Model::findPath(const std::pair<int, int>& aStart, const std::pair<int, int>& aEnd) {
    mPathFinder->findPath(mLevel.get(), aStart, aEnd);
}
