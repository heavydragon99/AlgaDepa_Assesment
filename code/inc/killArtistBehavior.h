// KillPlayerBehavior.h
#ifndef KILLPLAYERBEHAVIOR_H
#define KILLPLAYERBEHAVIOR_H

#include "iTileBehavior.h"
#include "levelData.h"

class KillArtistBehavior : public ITileBehavior {
public:
    KillArtistBehavior(LevelData* aLevelData);
    void doBehavior(Tile& aTile) override;

    private:
    LevelData* mLevelData;
};;

#endif // KILLPLAYERBEHAVIOR_H