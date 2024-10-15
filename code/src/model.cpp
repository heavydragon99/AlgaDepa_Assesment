#include "model.h"

Model::Model() {}

void Model::createLevel(std::vector<ParsedPerson> aPersons, ParsedGrid aGrid) {
    mLevel.buildLevelData(aPersons, aGrid);
}

LevelData& Model::getLevelData() { return mLevel; }

void Model::updateModel() { mLevel.updateLevelData(); }
