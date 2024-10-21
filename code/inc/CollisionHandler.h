#pragma once

#include <set>
#include <tuple>

#include "Quadtree.h"
#include "artist.h"
#include "configuration.h"
#include "model.h"

class CollisionHandler {

public:
    CollisionHandler(Model* aModel) : mModel(aModel) {}
    ~CollisionHandler() {}

    void handleCollisions() {
        naiveCollisionCheck();
        // quadTreeCollisionCheck();
        // if (mNaiveEnabled)
        //     naiveCollisionCheck();
        // else
        //     quadTreeCollisionCheck();
    }

    bool isColliding(Artist& person1, Artist& person2) {
        const float artistWidth = 0.5f;
        const float artistHeight = 0.5f;

        const auto& loc1 = person1.getLocation();
        const auto& loc2 = person2.getLocation();

        if (loc1.mX + artistWidth >= loc2.mX && loc1.mX <= loc2.mX + artistWidth && loc1.mY + artistHeight >= loc2.mY &&
            loc1.mY <= loc2.mY + artistHeight) {
            return true;
        }
        return false;
    }

    bool isColliding(Artist& person1, TileNode& tileNode) {
        const float tileWidth = 1.0f;
        const float tileHeight = 1.0f;

        const Artist::Location& loc1 = person1.getLocation();

        if (loc1.mX >= tileNode.getX() && loc1.mX < tileNode.getX() + tileWidth && loc1.mY >= tileNode.getY() &&
            loc1.mY <= tileNode.getY() + tileHeight) {
            return true;
        }
        return false;
    }

    void naiveCollisionCheck() {
        const float artistWidth = 0.5f;
        const float artistHeight = 0.5f;

        int cols = mModel->getLevelData().getCols();
        int rows = mModel->getLevelData().getRows();

        // Insert all artists into the quadtree
        for (Artist& artist : mModel->getLevelData().getPeople()) {
            artist.resetRed();
        }

        // Insert all tiles into the quadtree
        for (TileNode& tile : mModel->getLevelData().getGrid()) {
            tile.getTile().resetUpdate();
        }

        for (Artist& firstPerson : mModel->getLevelData().getPeople()) {

            Artist::Location& loc = firstPerson.getLocation();
            if (loc.mX < 0 || loc.mY < 0) {
                firstPerson.collidedWall(false);
            }

            if (loc.mX + artistWidth > cols || loc.mY + artistHeight > rows) {
                firstPerson.collidedWall(true);
            }

            for (Artist& secondPerson : mModel->getLevelData().getPeople()) {
                if (&firstPerson == &secondPerson)
                    continue;

                if (isColliding(firstPerson, secondPerson)) {
                    firstPerson.collidedOtherArtist();
                }
            }
        }
        static std::set<std::tuple<Artist*, TileNode*>> previousCollisions;
        std::set<std::tuple<Artist*, TileNode*>> currentCollision;

        int amountOfArists = mModel->getLevelData().getPeople().size();

        for (int iArtist = 0; iArtist < amountOfArists; iArtist++) {
            Artist* person = &mModel->getLevelData().getPeople()[iArtist];
            Artist& personRef = mModel->getLevelData().getPeople()[iArtist];
            ; // Get the raw pointer to the artist

            for (TileNode& tileItr : mModel->getLevelData().getGrid()) {
                TileNode* tile = &tileItr; // Get the raw pointer to the tileNode

                if (isColliding(personRef, tileItr)) { // Your collision detection logic
                    std::tuple<Artist*, TileNode*> collisionKey = std::make_tuple(person, tile);

                    // Check if this collision is new
                    if (previousCollisions.find(collisionKey) == previousCollisions.end()) {
                        // This is a new collision
                        if (!Configuration::getInstance().getConfig("PauseTiles")) { // Check if the tiles are paused
                            tileItr.getTile().updateTile();
                        }
                    }

                    // Add to current collision set
                    currentCollision.insert(collisionKey);
                }
            }
            amountOfArists = mModel->getLevelData().getPeople().size();
        }

        // Update the previous collisions with the current ones
        previousCollisions = std::move(currentCollision);
        return;
    }

    void quadTreeCollisionCheck() {
        const float artistWidth = 0.5f;
        const float artistHeight = 0.5f;
        const float tileWidth = 1.0f;
        const float tileHeight = 1.0f;
        int cols = mModel->getLevelData().getCols();
        int rows = mModel->getLevelData().getRows();

        // Define the bounds of the entire grid
        Quadtree::Boundary boundary{0, 0, static_cast<float>(mModel->getLevelData().getCols()),
                                    static_cast<float>(mModel->getLevelData().getRows())};

        // Create the Quadtree with a capacity of 4 objects per node
        Quadtree quadtree(boundary, 52);

        // Insert all artists into the quadtree
        for (Artist& artist : mModel->getLevelData().getPeople()) {
            artist.resetRed();
            quadtree.insert(&artist);
        }

        // Insert all tiles into the quadtree
        for (TileNode& tile : mModel->getLevelData().getGrid()) {
            tile.getTile().resetUpdate();
            quadtree.insert(&tile);
        }

        // Current collisions set for tiles
        std::set<std::tuple<Artist*, TileNode*>> currentTileCollisions;

        // Check collisions between artists
        for (Artist& artist : mModel->getLevelData().getPeople()) {
            Artist::Location& loc = artist.getLocation();
            if (loc.mX < 0 || loc.mY < 0) {
                artist.collidedWall(false);
            }

            if (loc.mX + artistWidth > cols || loc.mY + artistHeight > rows) {
                artist.collidedWall(true);
            }
            Quadtree::Boundary artistBoundary{artist.getLocation().mX - artistWidth,
                                              artist.getLocation().mY - artistHeight, artistWidth * 2,
                                              artistHeight * 2};

            // Query possible artist collisions
            std::vector<Artist*> possibleArtistCollisions;
            quadtree.queryArtists(artistBoundary, possibleArtistCollisions);

            for (Artist* other : possibleArtistCollisions) {
                if (&artist != other && isColliding(artist, *other)) {
                    // Call collided function for artist-artist collision
                    artist.collidedOtherArtist();
                }
            }

            // Query possible tile collisions
            std::vector<TileNode*> possibleTileCollisions;
            quadtree.queryTiles(artistBoundary, possibleTileCollisions);

            for (TileNode* tile : possibleTileCollisions) {
                if (isColliding(artist, *tile)) {
                    // Create a tuple for the current artist-tile collision
                    std::tuple<Artist*, TileNode*> collisionKey = std::make_tuple(&artist, tile);

                    // If this collision did not occur in the previous check, act on it
                    if (mPreviousTileCollisions.find(collisionKey) == mPreviousTileCollisions.end()) {
                        if (!Configuration::getInstance().getConfig("PauseTiles")) { // Check if the tiles are paused
                            tile->getTile().updateTile();                            // Act on new collision
                        }
                    }

                    // Add to current tile collision set
                    currentTileCollisions.insert(collisionKey);
                }
            }
        }

        // Update previous collisions with the current tile collisions
        mPreviousTileCollisions = std::move(currentTileCollisions);
    }

    void setNaive(bool aNaiveState) { mNaiveEnabled = aNaiveState; }

private:
    // Store previous collisions between artists and tiles
    std::set<std::tuple<Artist*, TileNode*>> mPreviousTileCollisions;

    bool mNaiveEnabled = true;

    Model* mModel;
};
