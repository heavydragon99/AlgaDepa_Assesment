#ifndef ITILEBEHAVIOR_H
#define ITILEBEHAVIOR_H

#include "levelData.h"
#include "tile.h"
#include <memory>

class Tile;

class ITileBehavior {
public:
    virtual ~ITileBehavior() = default;
    virtual std::unique_ptr<ITileBehavior> clone() const = 0;
    virtual void doBehavior(Tile& aTile) = 0;
};

// KillArtistBehavior
class KillArtistBehavior : public ITileBehavior {
public:
    KillArtistBehavior(LevelData* aLevelData) : mLevelData(aLevelData) {}
    std::unique_ptr<ITileBehavior> clone() const override { return std::make_unique<KillArtistBehavior>(*this); }
    void doBehavior(Tile& aTile) override { mLevelData->deleteArtist(aTile); }

private:
    LevelData* mLevelData;
};

// InfectTilesBehavior
class InfectTilesBehavior : public ITileBehavior {
public:
    InfectTilesBehavior(LevelData* aLevelData) : mLevelData(aLevelData) {}
    std::unique_ptr<ITileBehavior> clone() const override { return std::make_unique<InfectTilesBehavior>(*this); }
    void doBehavior(Tile& aTile) override { mLevelData->infectTiles(aTile); }

private:
    LevelData* mLevelData;
};

// AddArtistBehavior
class AddArtistBehavior : public ITileBehavior {
public:
    AddArtistBehavior(LevelData* aLevelData) : mLevelData(aLevelData) {}
    std::unique_ptr<ITileBehavior> clone() const override { return std::make_unique<AddArtistBehavior>(*this); }
    void doBehavior(Tile& aTile) override { mLevelData->addArtist(aTile); }

private:
    LevelData* mLevelData;
};

// NoOpBehavior
class NoOpBehavior : public ITileBehavior {
public:
    NoOpBehavior() = default;
    std::unique_ptr<ITileBehavior> clone() const override { return std::make_unique<NoOpBehavior>(*this); }
    void doBehavior(Tile& aTile) override {
        // Do nothing
    }
};

#endif // ITILEBEHAVIOR_H