#include "killArtistBehavior.h"

#include <iostream>

KillArtistBehavior::KillArtistBehavior(LevelData* aLevelData) : mLevelData(aLevelData) {}

void KillArtistBehavior::doBehavior(Tile& aTile) {
    mLevelData->deleteArtist(aTile);
}