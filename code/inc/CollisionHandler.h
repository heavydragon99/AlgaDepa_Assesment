#pragma once

#include <set>
#include <tuple>

#include "artist.h"
#include "model.h"

class CollisionHandler {

public:
    CollisionHandler(Model* aModel) : mModel(aModel) {}
    ~CollisionHandler() {}

    void handleCollisions() {
        if (mNaiveEnabled)
            naiveCollisionCheck();
        else
            quadTreeCollisionCheck();
    }

    bool isColliding(const std::unique_ptr<Artist>& person1, const std::unique_ptr<Artist>& person2) {
        const float artistWidth = 0.5f;
        const float artistHeight = 0.5f;

        const auto& loc1 = person1->getLocation();
        const auto& loc2 = person2->getLocation();

        if (loc1.mX + artistWidth >= loc2.mX && loc1.mX <= loc2.mX + artistWidth && loc1.mY + artistHeight >= loc2.mY &&
            loc1.mY <= loc2.mY + artistHeight) {
            return true;
        }
        return false;
    }

    bool isColliding(const std::unique_ptr<Artist>& person1, const std::unique_ptr<TileNode>& tileNode) {
        const float tileWidth = 1.0f;
        const float tileHeight = 1.0f;

        const auto& loc1 = person1->getLocation();

        if (loc1.mX >= tileNode->getX() && loc1.mX < tileNode->getX() + tileWidth && loc1.mY >= tileNode->getY() &&
            loc1.mY <= tileNode->getY() + tileHeight) {
            return true;
        }
        return false;
    }

    void naiveCollisionCheck() {
        const float artistWidth = 0.5f;
        const float artistHeight = 0.5f;

        int cols = mModel->getLevelData().getCols();
        int rows = mModel->getLevelData().getRows();

        for (const auto& firstPerson : mModel->getLevelData().getPeople()) {

            const auto& loc = firstPerson.get()->getLocation();
            if (loc.mX + artistWidth > cols || loc.mX < 0 || loc.mY + artistHeight > rows || loc.mY < 0) {
                firstPerson->collidedWall();
            }

            for (const auto& secondPerson : mModel->getLevelData().getPeople()) {
                if (firstPerson == secondPerson)
                    continue;

                if (isColliding(firstPerson, secondPerson)) {
                    firstPerson->collidedOtherArtist();
                }
            }
        }
        static std::set<std::tuple<Artist*, TileNode*>> previousCollisions;
        std::set<std::tuple<Artist*, TileNode*>> currentCollisions;

        for (const auto& personPtr : mModel->getLevelData().getPeople()) {
            Artist* person = personPtr.get(); // Get the raw pointer to the artist

            for (const auto& tilePtr : mModel->getLevelData().getGrid()) {
                TileNode* tile = tilePtr.get(); // Get the raw pointer to the tileNode

                if (isColliding(personPtr, tilePtr)) { // Your collision detection logic
                    std::tuple<Artist*, TileNode*> collisionKey = std::make_tuple(person, tile);

                    // Check if this collision is new
                    if (previousCollisions.find(collisionKey) == previousCollisions.end()) {
                        // This is a new collision
                        tilePtr->getTile().updateTile();
                    }

                    // Add to current collision set
                    currentCollisions.insert(collisionKey);
                }
            }
        }

        // Update the previous collisions with the current ones
        previousCollisions = std::move(currentCollisions);
        return;
    }

    void quadTreeCollisionCheck() {}

    void setNaive(bool aNaiveState) { mNaiveEnabled = aNaiveState; }

private:
    bool mNaiveEnabled = true;

    Model* mModel;
};
