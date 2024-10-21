#pragma once

#include "artist.h"
#include "tileNode.h"

#include <memory>
#include <vector>

class Quadtree {
public:
    struct Boundary {
        float x, y, width, height;
        bool contains(const Artist::Location& loc) const {
            return loc.mX >= x && loc.mX < x + width && loc.mY >= y && loc.mY < y + height;
        }
        bool contains(float tileX, float tileY, float tileWidth, float tileHeight) const {
            return tileX >= x && tileX < x + width && tileY >= y && tileY < y + height;
        }
        bool intersects(const Boundary& other) const {
            return !(
                other.x > x + width || other.x + other.width < x || other.y > y + height || other.y + other.height < y);
        }
    };

    Quadtree(const Boundary& boundary, int capacity) : mBoundary(boundary), mCapacity(capacity), mDivided(false) {}

    // Insert an Artist into the quadtree
    bool insert(Artist* artist) {
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

    // Insert a TileNode into the quadtree
    bool insert(TileNode* tile) {
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

    // Retrieve possible colliding artists within the range
    void queryArtists(const Boundary& range, std::vector<Artist*>& found) const {
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

    // Retrieve possible colliding tiles within the range
    void queryTiles(const Boundary& range, std::vector<TileNode*>& found) const {
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

    std::vector<Boundary> getBoundaries() {
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

private:
    Boundary mBoundary;
    int mCapacity;
    bool mDivided;
    std::vector<Artist*> mArtists;
    std::vector<TileNode*> mTiles; // Added to store TileNode objects

    std::unique_ptr<Quadtree> mTopLeft;
    std::unique_ptr<Quadtree> mTopRight;
    std::unique_ptr<Quadtree> mBottomLeft;
    std::unique_ptr<Quadtree> mBottomRight;

    void subdivide() {
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
};
