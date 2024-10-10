#pragma once

#include "artist.h"
#include "model.h"

class CollisionHandler {

public:
    CollisionHandler(model* aModel) : mModel(aModel) {}
    ~CollisionHandler() {}

    void handleCollisions() {
        if (mNaiveEnabled)
            naiveCollisionCheck();
        else
            quadTreeCollisionCheck();
    }

    bool isColliding(const std::unique_ptr<artist>& person1, const std::unique_ptr<artist>& person2) {
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

    bool isColliding(const std::unique_ptr<artist>& person1, const std::unique_ptr<tileNode>& tileNode) {
        const float artistWidth = 0.5f;
        const float artistHeight = 0.5f;

        const auto& loc1 = person1->getLocation();
        // const auto& loc2 = tileNode->getLocation();
        //
        // if (loc1.mX + artistWidth >= loc2.mX && loc1.mX <= loc2.mX + artistWidth && loc1.mY + artistHeight >= loc2.mY
        // &&
        //     loc1.mY <= loc2.mY + artistHeight) {
        //     return true;
        // }
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

        for (const auto& person : mModel->getLevelData().getPeople()) {
            for (const auto& tileNode : mModel->getLevelData().getGrid()) {
                if (isColliding(person, tileNode)) {
                }
            }
        }

        // for (const auto& otherPerson : mPeople) {
        //     if (aPerson == otherPerson)
        //         continue;
        //
        //     if (isColliding(aPerson, otherPerson)) {
        //         return true;
        //     }
        // }
        return;
    }

    void quadTreeCollisionCheck() {}

    void setNaive(bool aNaiveState) { mNaiveEnabled = aNaiveState; }

private:
    bool mNaiveEnabled = true;

    model* mModel;
};