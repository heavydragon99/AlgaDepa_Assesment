#include "Quadtree.h"

#include <iostream>

/**
 * @brief Constructs a Quadtree with a given boundary, capacity, and depth.
 * @param boundary The boundary of the Quadtree.
 * @param capacity The maximum number of elements a node can hold before subdividing.
 * @param depth The current depth of this node.
 * @param maxDepth The maximum depth allowed for the Quadtree.
 */
Quadtree::Quadtree(const Boundary& boundary, int capacity, int depth, int maxDepth)
    : mBoundary(boundary), mCapacity(capacity), mDivided(false), mDepth(depth), mMaxDepth(maxDepth) {}

/**
 * @brief Checks if a location is within the boundary.
 * @param loc The location to check.
 * @return True if the location is within the boundary, false otherwise.
 */
bool Quadtree::Boundary::contains(const Artist::Location& loc) const {
    // Include on the boundary for left/top, exclude for right/bottom
    return loc.mX >= x && loc.mX < x + width && loc.mY >= y && loc.mY < y + height;
}
//
// bool Quadtree::Boundary::contains(const Artist::Location& loc) const {
//     return loc.mX >= x && loc.mX < x + width && loc.mY >= y && loc.mY < y + height;
// }

/**
 * @brief Checks if a tile is within the boundary.
 * @param tileX The x-coordinate of the tile.
 * @param tileY The y-coordinate of the tile.
 * @param tileWidth The width of the tile.
 * @param tileHeight The height of the tile.
 * @return True if the tile is within the boundary, false otherwise.
 */
bool Quadtree::Boundary::contains(float tileX, float tileY, float tileWidth, float tileHeight) const {
    return tileX >= x && tileX < x + width && tileY >= y && tileY < y + height;
}

/**
 * @brief Checks if another boundary intersects with this boundary.
 * @param other The other boundary to check.
 * @return True if the boundaries intersect, false otherwise.
 */
bool Quadtree::Boundary::intersects(const Boundary& other) const {
    return !(other.x > x + width || other.x + other.width < x || other.y > y + height || other.y + other.height < y);
}

/**
 * @brief Inserts an Artist into the Quadtree.
 * @param artist The artist to insert.
 * @return True if the artist was successfully inserted, false otherwise.
 */
bool Quadtree::insert(Artist* artist) {
    if (!mBoundary.contains(artist->getLocation())) {
        return false; // Artist is outside this boundary
    }

    if (mDivided) {
        if (mTopLeft->insert(artist) || mTopRight->insert(artist) || mBottomLeft->insert(artist) ||
            mBottomRight->insert(artist)) {
            return true;
        }
    }

    if (mArtists.size() < mCapacity || mDepth == mMaxDepth) {
        // If there's space or we've reached max depth, store the artist
        mArtists.push_back(artist);
        return true;
    }

    if (!mDivided) {
        subdivide();
    }

    return mTopLeft->insert(artist) || mTopRight->insert(artist) || mBottomLeft->insert(artist) ||
           mBottomRight->insert(artist);
}

/**
 * @brief Inserts a TileNode into the Quadtree.
 * @param tile The tile to insert.
 * @return True if the tile was successfully inserted, false otherwise.
 */
bool Quadtree::insert(TileNode* tile) {
    if (!mBoundary.contains(tile->getX(), tile->getY(), 1.0f, 1.0f)) {
        return false; // TileNode is outside this boundary
    }

    if (mDivided) {
        if (mTopLeft->insert(tile) || mTopRight->insert(tile) || mBottomLeft->insert(tile) ||
            mBottomRight->insert(tile)) {
            return true;
        }
    }

    if (mTiles.size() < mCapacity || mDepth == mMaxDepth) {
        // If there's space or we've reached max depth, store the tile
        mTiles.push_back(tile);
        return true;
    }

    if (!mDivided) {
        subdivide();
    }

    return mTopLeft->insert(tile) || mTopRight->insert(tile) || mBottomLeft->insert(tile) || mBottomRight->insert(tile);
}

/**
 * @brief Retrieves possible colliding artists within the range.
 * @param range The boundary range to query.
 * @param found A vector to store the found artists.
 */
void Quadtree::queryArtists(const Boundary& range, std::vector<Artist*>& found) const {
    if (!mBoundary.intersects(range)) {
        return;
    }

    if (mDivided) {
        mTopLeft->queryArtists(range, found);
        mTopRight->queryArtists(range, found);
        mBottomLeft->queryArtists(range, found);
        mBottomRight->queryArtists(range, found);
    } else {
        for (Artist* artist : mArtists) {
            if (range.contains(artist->getLocation())) {
                found.push_back(artist);
            }
        }
    }
}

/**
 * @brief Retrieves possible colliding tiles within the range.
 * @param range The boundary range to query.
 * @param found A vector to store the found tiles.
 */
void Quadtree::queryTiles(const Boundary& range, std::vector<TileNode*>& found) const {
    if (!mBoundary.intersects(range)) {
        return;
    }

    if (mDivided) {
        mTopLeft->queryTiles(range, found);
        mTopRight->queryTiles(range, found);
        mBottomLeft->queryTiles(range, found);
        mBottomRight->queryTiles(range, found);
    } else {
        for (TileNode* tile : mTiles) {
            if (range.contains(tile->getX(), tile->getY(), 1.0f, 1.0f)) {
                found.push_back(tile);
            }
        }
    }
}

/**
 * @brief Retrieves the boundaries of all nodes in the Quadtree.
 * @return A vector of boundaries.
 */
std::vector<Quadtree::Boundary> Quadtree::getBoundaries() {
    // Start by adding the current node's boundary
    std::vector<Boundary> boundaries{mBoundary};

    // If the node is subdivided, add boundaries from child nodes as well
    if (mDivided) {
        std::vector<Boundary> topleft = mTopLeft->getBoundaries();
        boundaries.insert(boundaries.end(), topleft.begin(), topleft.end());

        std::vector<Boundary> topright = mTopRight->getBoundaries();
        boundaries.insert(boundaries.end(), topright.begin(), topright.end());

        std::vector<Boundary> bottomleft = mBottomLeft->getBoundaries();
        boundaries.insert(boundaries.end(), bottomleft.begin(), bottomleft.end());

        std::vector<Boundary> bottomright = mBottomRight->getBoundaries();
        boundaries.insert(boundaries.end(), bottomright.begin(), bottomright.end());
    }

    return boundaries;
}

/**
 * @brief Subdivides the Quadtree node into four children.
 */

void Quadtree::subdivide() {
    if (mDepth >= mMaxDepth) {
        return; // Do not subdivide further if the max depth is reached
    }

    float x = mBoundary.x;
    float y = mBoundary.y;
    float halfWidth = mBoundary.width / 2.0f;
    float halfHeight = mBoundary.height / 2.0f;

    mTopLeft = std::make_unique<Quadtree>(Boundary{x, y, halfWidth, halfHeight}, mCapacity, mDepth + 1, mMaxDepth);
    mTopRight =
        std::make_unique<Quadtree>(Boundary{x + halfWidth, y, halfWidth, halfHeight}, mCapacity, mDepth + 1, mMaxDepth);
    mBottomLeft = std::make_unique<Quadtree>(Boundary{x, y + halfHeight, halfWidth, halfHeight}, mCapacity, mDepth + 1,
                                             mMaxDepth);
    mBottomRight = std::make_unique<Quadtree>(Boundary{x + halfWidth, y + halfHeight, halfWidth, halfHeight}, mCapacity,
                                              mDepth + 1, mMaxDepth);

    mDivided = true;
}
