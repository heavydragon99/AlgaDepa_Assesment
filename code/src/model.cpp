#include "model.h"

#include "configuration.h"

#include <stdexcept>
#include <iostream>

Model::Model()
    : mLevel(std::make_unique<LevelData>()), mMementoManager(std::make_unique<MementoManager>()),
      mPathFinder(std::make_unique<PathFinder>()), mLastUpdateTime(std::chrono::steady_clock::now() - MEMENTO_UPDATE_INTERVAL) {}

void Model::createLevel(std::vector<ParsedPerson> aPersons, ParsedGrid aGrid) {
    mLevel->buildGridData(aGrid);
    mLevel->buildPersonData(aPersons);
}
void Model::setPersonData(std::vector<ParsedPerson> aPersons) { mLevel->buildPersonData(aPersons); }

void Model::setGridData(ParsedGrid aGrid) { mLevel->buildGridData(aGrid); }

LevelData& Model::getLevelData() { return *mLevel; }

void Model::updateModel() {
    if (!Configuration::getInstance().getConfig("PauseArtists")) {
        auto now = std::chrono::steady_clock::now();
        if (now - mLastUpdateTime >= MEMENTO_UPDATE_INTERVAL) {
            mMementoManager->addMemento(saveToMemento());
            mLastUpdateTime = now;
        }
        mLevel->updateLevelData();
    }
}

void Model::updateTile(int aX, int aY) { mLevel->updateTile(aX, aY); }

Memento Model::saveToMemento() const { return Memento(*mLevel.get()); }

void Model::restoreFromMemento(Memento&& memento) {
    mLevel->buildGridData(memento.getGrid());
    mLevel->buildPersonData(memento.getPeople());
}
void Model::usePreviousMemento() {
    try {
        restoreFromMemento(mMementoManager->getPreviousMemento());
    } catch (const std::exception& e) {
        std::cerr << "Error using previous memento: " << e.what() << std::endl;
    }
}

void Model::useNextMemento() {
    try {
        restoreFromMemento(mMementoManager->getNextMemento());
    } catch (const std::exception& e) {
        std::cerr << "Error using next memento: " << e.what() << std::endl;
    }
}

void Model::findPath(const std::pair<int, int>& aStart, const std::pair<int, int>& aEnd) {
    mPathFinder->findPath(mLevel.get(), aStart, aEnd);
}
