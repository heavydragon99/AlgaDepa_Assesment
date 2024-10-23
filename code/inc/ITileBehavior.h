#ifndef ITILEBEHAVIOR_H
#define ITILEBEHAVIOR_H

#include "LevelData.h"
#include "Tile.h"
#include <memory>

class Tile;

/**
 * @brief Interface for tile behaviors.
 */
class ITileBehavior {
public:
    /**
     * @brief Virtual destructor for ITileBehavior.
     */
    virtual ~ITileBehavior() = default;

    /**
     * @brief Clone the behavior.
     * @return A unique pointer to the cloned behavior.
     */
    virtual std::unique_ptr<ITileBehavior> clone() const = 0;

    /**
     * @brief Execute the behavior on a tile.
     * @param aTile The tile on which to execute the behavior.
     */
    virtual void doBehavior(Tile& aTile) = 0;
};

/**
 * @brief Behavior to delete an artist from a tile.
 */
class KillArtistBehavior : public ITileBehavior {
public:
    /**
     * @brief Constructor for KillArtistBehavior.
     * @param aLevelData Pointer to the level data.
     */
    KillArtistBehavior(LevelData* aLevelData) : mLevelData(aLevelData) {}

    /**
     * @brief Clone the behavior.
     * @return A unique pointer to the cloned behavior.
     */
    std::unique_ptr<ITileBehavior> clone() const override { return std::make_unique<KillArtistBehavior>(*this); }

    /**
     * @brief Execute the behavior on a tile.
     * @param aTile The tile on which to execute the behavior.
     */
    void doBehavior(Tile& aTile) override { mLevelData->deleteArtist(aTile); }

private:
    LevelData* mLevelData; ///< Pointer to the level data.
};

/**
 * @brief Behavior to infect tiles.
 */
class InfectTilesBehavior : public ITileBehavior {
public:
    /**
     * @brief Constructor for InfectTilesBehavior.
     * @param aLevelData Pointer to the level data.
     */
    InfectTilesBehavior(LevelData* aLevelData) : mLevelData(aLevelData) {}

    /**
     * @brief Clone the behavior.
     * @return A unique pointer to the cloned behavior.
     */
    std::unique_ptr<ITileBehavior> clone() const override { return std::make_unique<InfectTilesBehavior>(*this); }

    /**
     * @brief Execute the behavior on a tile.
     * @param aTile The tile on which to execute the behavior.
     */
    void doBehavior(Tile& aTile) override { mLevelData->infectTiles(aTile); }

private:
    LevelData* mLevelData; ///< Pointer to the level data.
};

/**
 * @brief Behavior to add an artist to a tile.
 */
class AddArtistBehavior : public ITileBehavior {
public:
    /**
     * @brief Constructor for AddArtistBehavior.
     * @param aLevelData Pointer to the level data.
     */
    AddArtistBehavior(LevelData* aLevelData) : mLevelData(aLevelData) {}

    /**
     * @brief Clone the behavior.
     * @return A unique pointer to the cloned behavior.
     */
    std::unique_ptr<ITileBehavior> clone() const override { return std::make_unique<AddArtistBehavior>(*this); }

    /**
     * @brief Execute the behavior on a tile.
     * @param aTile The tile on which to execute the behavior.
     */
    void doBehavior(Tile& aTile) override { mLevelData->addArtist(aTile); }

private:
    LevelData* mLevelData; ///< Pointer to the level data.
};

/**
 * @brief No operation behavior.
 */
class NoOpBehavior : public ITileBehavior {
public:
    /**
     * @brief Default constructor for NoOpBehavior.
     */
    NoOpBehavior() = default;

    /**
     * @brief Clone the behavior.
     * @return A unique pointer to the cloned behavior.
     */
    std::unique_ptr<ITileBehavior> clone() const override { return std::make_unique<NoOpBehavior>(*this); }

    /**
     * @brief Execute the behavior on a tile.
     * @param aTile The tile on which to execute the behavior.
     */
    void doBehavior(Tile& aTile) override {
        // Do nothing
    }
};

#endif // ITILEBEHAVIOR_H