#include "addArtistBehavior.h"

#include <iostream>

AddArtistBehavior::AddArtistBehavior(LevelData* aLevelData) : mLevelData(aLevelData) {}

std::unique_ptr<ITileBehavior> AddArtistBehavior::clone() const {
    return std::make_unique<AddArtistBehavior>(*this);
}

void AddArtistBehavior::doBehavior(Tile& aTile) {
    // Code to infect tiles
    mLevelData->addArtist(aTile);
}