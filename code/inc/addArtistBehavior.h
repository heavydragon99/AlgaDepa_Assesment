// KillPlayerBehavior.h
#ifndef ADDARTISTBEHAVIOR_H
#define ADDARTISTBEHAVIOR_H

#include "iTileBehavior.h"
#include "levelData.h"

class AddArtistBehavior : public ITileBehavior{
public:
    AddArtistBehavior(LevelData* aLevelData);
    void doBehavior(Tile& aTile) override;

    private:
    LevelData* mLevelData;
};;

#endif // ADDARTISTBEHAVIOR_H