#include "model.h"

Model::Model() {}

void Model::createLevel(std::vector<ParsedPerson> aPersons, ParsedGrid aGrid) {
    mLevel.buildLevelData(aPersons, aGrid);
}

const LevelData& Model::getLevelData() const { return mLevel; }

void Model::updateModel() { mLevel.updateLevelData(); }
