#include "model.h"



model::model() {
}

void model::createLevel(std::vector<parsedPerson> aPersons, parsedGrid aGrid) {
    mLevel.buildLevelData(aPersons, aGrid);
}

const levelData& model::getLevelData() const {
    return mLevel;
}