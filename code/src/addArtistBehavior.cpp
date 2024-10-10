#include "addArtistBehavior.h"

#include <iostream>

AddArtistBehavior::AddArtistBehavior(LevelData* aLevelData) : mLevelData(aLevelData) {}

void AddArtistBehavior::doBehavior(Tile& aTile) {
    // Code to infect tiles
    mLevelData->addArtist(aTile);
}