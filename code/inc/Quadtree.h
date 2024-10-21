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

    Quadtree(const Boundary& boundary, int capacity);

    // Insert an Artist into the quadtree
    bool insert(Artist* artist);
    // Insert a TileNode into the quadtree
    bool insert(TileNode* tile);

    // Retrieve possible colliding artists within the range
    void queryArtists(const Boundary& range, std::vector<Artist*>& found) const;
    // Retrieve possible colliding tiles within the range
    void queryTiles(const Boundary& range, std::vector<TileNode*>& found) const;

    std::vector<Boundary> getBoundaries();

private:
    void subdivide();

    Boundary mBoundary;
    int mCapacity;
    bool mDivided;
    std::vector<Artist*> mArtists;
    std::vector<TileNode*> mTiles; // Added to store TileNode objects

    std::unique_ptr<Quadtree> mTopLeft;
    std::unique_ptr<Quadtree> mTopRight;
    std::unique_ptr<Quadtree> mBottomLeft;
    std::unique_ptr<Quadtree> mBottomRight;
};
