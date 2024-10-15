#ifndef TILENODE_H
#define TILENODE_H

#include "tile.h"

#include <memory>
#include <vector>

class TileNode {
public:
    TileNode() = default; // Added so vector can be resized
    TileNode(std::unique_ptr<Tile> aTile, int aX, int aY);

    void addNeighbor(TileNode& aNeighbor);
    const std::vector<std::reference_wrapper<TileNode>>& getNeighbors() const;

    Tile& getTile() const;

    void setWeight(int aWeight);
    int getWeight() const;

    int getX() const;
    int getY() const;

    void setIsPath(bool aIsPath);
    bool isPath() const;

    void setIsVisited(bool aIsVisited);
    bool isVisited() const;

private:
    std::unique_ptr<Tile> mTile;
    std::vector<std::reference_wrapper<TileNode>> mNeighbors;

    int mWeight;

    int mX;
    int mY;

    bool mIsPath;
    bool mIsVisited;
};

#endif // TILENODE_H