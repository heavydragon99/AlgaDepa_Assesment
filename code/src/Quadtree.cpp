#include "Quadtree.h"

Quadtree::Quadtree(const Boundary& boundary, int capacity)
    : mBoundary(boundary), mCapacity(capacity), mDivided(false) {}

bool Quadtree::insert(Artist* artist) {
    if (!mBoundary.contains(artist->getLocation())) {
        return false; // Artist is outside this boundary
    }

    if (mArtists.size() < mCapacity) {
        mArtists.push_back(artist);
        return true;
    } else {
        if (!mDivided) {
            subdivide();
        }

        if (mTopLeft->insert(artist) || mTopRight->insert(artist) || mBottomLeft->insert(artist) ||
            mBottomRight->insert(artist)) {
            return true;
        }
    }

    return false;
}

bool Quadtree::insert(TileNode* tile) {
    if (!mBoundary.contains(tile->getX(), tile->getY(), 1.0f, 1.0f)) {
        return false; // TileNode is outside this boundary
    }

    if (mTiles.size() < mCapacity) {
        mTiles.push_back(tile);
        return true;
    } else {
        if (!mDivided) {
            subdivide();
        }

        if (mTopLeft->insert(tile) || mTopRight->insert(tile) || mBottomLeft->insert(tile) ||
            mBottomRight->insert(tile)) {
            return true;
        }
    }

    return false;
}

void Quadtree::queryArtists(const Boundary& range, std::vector<Artist*>& found) const {
    if (!mBoundary.intersects(range)) {
        return;
    }

    for (Artist* artist : mArtists) {
        if (range.contains(artist->getLocation())) {
            found.push_back(artist);
        }
    }

    if (mDivided) {
        mTopLeft->queryArtists(range, found);
        mTopRight->queryArtists(range, found);
        mBottomLeft->queryArtists(range, found);
        mBottomRight->queryArtists(range, found);
    }
}

void Quadtree::queryTiles(const Boundary& range, std::vector<TileNode*>& found) const {
    if (!mBoundary.intersects(range)) {
        return;
    }

    for (TileNode* tile : mTiles) {
        if (range.contains(tile->getX(), tile->getY(), 1.0f, 1.0f)) {
            found.push_back(tile);
        }
    }

    if (mDivided) {
        mTopLeft->queryTiles(range, found);
        mTopRight->queryTiles(range, found);
        mBottomLeft->queryTiles(range, found);
        mBottomRight->queryTiles(range, found);
    }
}

std::vector<Quadtree::Boundary> Quadtree::getBoundaries() {
    if (mDivided) {
        std::vector<Boundary> boundaries;

        std::vector<Boundary> topleft = mTopLeft->getBoundaries();
        boundaries.insert(boundaries.end(), topleft.begin(), topleft.end());

        std::vector<Boundary> topright = mTopRight->getBoundaries();
        boundaries.insert(boundaries.end(), topright.begin(), topright.end());

        std::vector<Boundary> bottomleft = mBottomLeft->getBoundaries();
        boundaries.insert(boundaries.end(), bottomleft.begin(), bottomleft.end());

        std::vector<Boundary> bottomright = mBottomRight->getBoundaries();
        boundaries.insert(boundaries.end(), bottomright.begin(), bottomright.end());
        // vec1.insert(vec1.end(), vec2.begin(), vec2.end());
        // mTopLeft->getBoundaries(range, found);
        // mTopRight->queryTiles(range, found);
        // mBottomLeft->queryTiles(range, found);
        // mBottomRight->queryTiles(range, found);

        return boundaries;
    } else {
        return std::vector<Boundary>{mBoundary};
    }
}

void Quadtree::subdivide() {
    float x = mBoundary.x;
    float y = mBoundary.y;
    float halfWidth = mBoundary.width / 2.0f;
    float halfHeight = mBoundary.height / 2.0f;

    mTopLeft = std::make_unique<Quadtree>(Boundary{x, y, halfWidth, halfHeight}, mCapacity);
    mTopRight = std::make_unique<Quadtree>(Boundary{x + halfWidth, y, halfWidth, halfHeight}, mCapacity);
    mBottomLeft = std::make_unique<Quadtree>(Boundary{x, y + halfHeight, halfWidth, halfHeight}, mCapacity);
    mBottomRight =
        std::make_unique<Quadtree>(Boundary{x + halfWidth, y + halfHeight, halfWidth, halfHeight}, mCapacity);

    mDivided = true;
}
