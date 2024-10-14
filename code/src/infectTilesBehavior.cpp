#include "infectTilesBehavior.h"

#include <iostream>

InfectTilesBehavior::InfectTilesBehavior(LevelData* aLevelData) : mLevelData(aLevelData) {}

void InfectTilesBehavior::doBehavior(Tile& aTile) {
    mLevelData->infectTiles(aTile);
}