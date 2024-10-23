#ifndef TEST_ITILEBEHAVIOR_H
#define TEST_ITILEBEHAVIOR_H

#include "gtest/gtest.h"
#include "Tile.h"
#include "TileFactory.h"
#include "ITileBehavior.h"
#include "ITileState.h"
#include "LevelData.h"

// Stub class for LevelData
class StubLevelData : public LevelData {
public:
    void deleteArtist(const Tile&) override { deleteArtistCalled = true; }
    void infectTiles(const Tile&) override { infectTilesCalled = true; }
    void addArtist(const Tile&) override { addArtistCalled = true; }

    bool deleteArtistCalled = false;
    bool infectTilesCalled = false;
    bool addArtistCalled = false;
};

// Test fixture for ITileBehavior tests
class ITileBehaviorTest : public ::testing::Test {
protected:
    StubLevelData stubLevelData;
};

// Test KillArtistBehavior
TEST_F(ITileBehaviorTest, KillArtistBehaviorTest) {
    KillArtistBehavior behavior(&stubLevelData);
    Tile tile(std::make_unique<TileStateRed>(std::make_unique<NoOpBehavior>()));

    behavior.doBehavior(tile);
    EXPECT_TRUE(stubLevelData.deleteArtistCalled);
}

// Test InfectTilesBehavior
TEST_F(ITileBehaviorTest, InfectTilesBehaviorTest) {
    InfectTilesBehavior behavior(&stubLevelData);
    Tile tile(std::make_unique<TileStateRed>(std::make_unique<NoOpBehavior>()));

    behavior.doBehavior(tile);
    EXPECT_TRUE(stubLevelData.infectTilesCalled);
}

// Test AddArtistBehavior
TEST_F(ITileBehaviorTest, AddArtistBehaviorTest) {
    AddArtistBehavior behavior(&stubLevelData);
    Tile tile(std::make_unique<TileStateRed>(std::make_unique<NoOpBehavior>()));

    behavior.doBehavior(tile);
    EXPECT_TRUE(stubLevelData.addArtistCalled);
}

// Test NoOpBehavior
TEST_F(ITileBehaviorTest, NoOpBehaviorTest) {
    NoOpBehavior behavior;
    Tile tile(std::make_unique<TileStateRed>(std::make_unique<NoOpBehavior>()));

    // No expectations as NoOpBehavior does nothing
    behavior.doBehavior(tile);
}

// Test Tile state transitions
TEST_F(ITileBehaviorTest, TileStateTransitionTest) {
    Tile tile(std::make_unique<TileStateRed>(std::make_unique<NoOpBehavior>()));

    // Initial state should be Red
    EXPECT_EQ(tile.getColor(), 'R');

    // Transition to Yellow state
    tile.setState(std::make_unique<TileStateYellow>(std::make_unique<NoOpBehavior>()));
    EXPECT_EQ(tile.getColor(), 'Y');

    // Transition to Blue state
    tile.forceBlue();
    EXPECT_EQ(tile.getColor(), 'B');
}

// Test TileFactory createTile
TEST_F(ITileBehaviorTest, TileFactoryCreateTileTest) {
    TileFactory::setLevelData(&stubLevelData);

    auto tile = TileFactory::createTile('R');
    EXPECT_EQ(tile->getColor(), 'R');

    tile = TileFactory::createTile('Y');
    EXPECT_EQ(tile->getColor(), 'Y');

    tile = TileFactory::createTile('B');
    EXPECT_EQ(tile->getColor(), 'B');
}

#endif // TEST_ITILEBEHAVIOR_H