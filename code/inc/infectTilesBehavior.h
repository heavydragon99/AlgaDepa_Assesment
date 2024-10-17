// InfectTilesBehavior.h
#ifndef INFECTTILESBEHAVIOR_H
#define INFECTTILESBEHAVIOR_H

#include "iTileBehavior.h"
#include "levelData.h"

class InfectTilesBehavior : public ITileBehavior{
public:
    InfectTilesBehavior(LevelData* aLevelData);
    std::unique_ptr<ITileBehavior> clone() const override;
    void doBehavior(Tile& aTile) override;

    private:
    LevelData* mLevelData;
};

#endif // INFECTTILESBEHAVIOR_H