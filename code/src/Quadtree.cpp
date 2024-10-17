#include "Quadtree.h"

// Constructor
Quadtree::Quadtree(int level, float x, float y, float width, float height)
    : mLevel(level), mX(x), mY(y), mWidth(width), mHeight(height) {}

// Clear the quadtree
void Quadtree::clear() {
    mObjects.clear();
    for (int i = 0; i < 4; ++i) {
        if (mNodes[i]) {
            mNodes[i]->clear();
            mNodes[i].reset();
        }
    }
}

// Subdivide the node into 4 quadrants
void Quadtree::subdivide() {
    float subWidth = mWidth / 2;
    float subHeight = mHeight / 2;
    float x = mX;
    float y = mY;

    mNodes[0] = std::make_unique<Quadtree>(mLevel + 1, x + subWidth, y, subWidth, subHeight);
    mNodes[1] = std::make_unique<Quadtree>(mLevel + 1, x, y, subWidth, subHeight);
    mNodes[2] = std::make_unique<Quadtree>(mLevel + 1, x, y + subHeight, subWidth, subHeight);
    mNodes[3] = std::make_unique<Quadtree>(mLevel + 1, x + subWidth, y + subHeight, subWidth, subHeight);
}

// Get the index for the given artist
int Quadtree::getIndex(Artist* artist) {
    int index = -1;
    float verticalMidpoint = mX + (mWidth / 2);
    float horizontalMidpoint = mY + (mHeight / 2);

    bool topQuadrant = (artist->getLocation().mY < horizontalMidpoint);
    bool bottomQuadrant = (artist->getLocation().mY >= horizontalMidpoint);

    if (artist->getLocation().mX < verticalMidpoint) {
        if (topQuadrant) {
            index = 1;
        } else if (bottomQuadrant) {
            index = 2;
        }
    } else if (artist->getLocation().mX >= verticalMidpoint) {
        if (topQuadrant) {
            index = 0;
        } else if (bottomQuadrant) {
            index = 3;
        }
    }

    return index;
}

// Insert the artist into the quadtree
void Quadtree::insert(Artist* artist) {
    if (mNodes[0]) {
        int index = getIndex(artist);
        if (index != -1) {
            mNodes[index]->insert(artist);
            return;
        }
    }

    mObjects.push_back(artist);

    if (mObjects.size() > MAX_OBJECTS && mLevel < MAX_LEVELS) {
        if (!mNodes[0]) {
            subdivide();
        }

        int i = 0;
        while (i < mObjects.size()) {
            int index = getIndex(mObjects[i]);
            if (index != -1) {
                mNodes[index]->insert(mObjects[i]);
                mObjects.erase(mObjects.begin() + i);
            } else {
                i++;
            }
        }
    }
}

// Retrieve all artists that could collide with the given artist
std::vector<Artist*> Quadtree::retrieve(std::vector<Artist*>& returnObjects, Artist* artist) {
    int index = getIndex(artist);
    if (index != -1 && mNodes[0]) {
        mNodes[index]->retrieve(returnObjects, artist);
    }

    returnObjects.insert(returnObjects.end(), mObjects.begin(), mObjects.end());
    return returnObjects;
}
