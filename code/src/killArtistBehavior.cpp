#include "killArtistBehavior.h"

#include <iostream>

KillArtistBehavior::KillArtistBehavior(LevelData* aLevelData) : mLevelData(aLevelData) {}

std::unique_ptr<ITileBehavior> KillArtistBehavior::clone() const {
    return std::make_unique<KillArtistBehavior>(*this);
}

void KillArtistBehavior::doBehavior(Tile& aTile) {
    mLevelData->deleteArtist(aTile);
}