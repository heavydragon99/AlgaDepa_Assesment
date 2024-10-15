#include "infectTilesBehavior.h"

#include <iostream>

InfectTilesBehavior::InfectTilesBehavior(LevelData* aLevelData) : mLevelData(aLevelData) {}

std::unique_ptr<ITileBehavior> InfectTilesBehavior::clone() const {
    return std::make_unique<InfectTilesBehavior>(*this);
}

void InfectTilesBehavior::doBehavior(Tile& aTile) {
    mLevelData->infectTiles(aTile);
}