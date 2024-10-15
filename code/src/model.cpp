#include "model.h"

Model::Model() : mLevel(std::make_unique<LevelData>()) {}

void Model::createLevel(std::vector<ParsedPerson> aPersons, ParsedGrid aGrid) {
    mLevel->buildLevelData(aPersons, aGrid);
}

LevelData& Model::getLevelData() { return *mLevel; }

void Model::updateModel() { mLevel->updateLevelData(); }

Memento Model::saveToMemento() const {
    return Memento(std::make_unique<LevelData>(*mLevel));
}

void Model::restoreFromMemento(Memento&& memento) {
    mLevel = std::move(memento.getState());
}