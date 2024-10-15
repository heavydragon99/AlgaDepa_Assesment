#include "model.h"

Model::Model() : mLevel(std::make_unique<LevelData>()), mMementoManager(std::make_unique<MementoManager>()) {}

void Model::createLevel(std::vector<ParsedPerson> aPersons, ParsedGrid aGrid) {
    mLevel->buildLevelData(aPersons, aGrid);
}

LevelData& Model::getLevelData() { return *mLevel; }

void Model::updateModel() {
    auto now = std::chrono::steady_clock::now();
    if (now - mLastUpdateTime >= UPDATE_INTERVAL) {
        mMementoManager->addMemento(saveToMemento());
        mLastUpdateTime = now;
    }
    mLevel->updateLevelData();
}

Memento Model::saveToMemento() const { return Memento(std::make_unique<LevelData>(*mLevel)); }

void Model::restoreFromMemento(Memento&& memento) { mLevel = std::move(memento.getState()); }

void Model::usePreviousMemento() { restoreFromMemento(mMementoManager->getPreviousMemento()); }

void Model::useNextMemento() { restoreFromMemento(mMementoManager->getNextMemento()); }