#include "model.h"

model::model() {}

void model::createLevel(std::vector<ParsedPerson> aPersons, ParsedGrid aGrid) {
    mLevel.buildLevelData(aPersons, aGrid);
}

const levelData& model::getLevelData() const { return mLevel; }

void model::updateModel() { mLevel.updateLevelData(); }
