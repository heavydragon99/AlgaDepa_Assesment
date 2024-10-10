#ifndef TILENODE_H
#define TILENODE_H

#include "tile.h"

#include <memory>
#include <vector>

class TileNode
{
public:
    TileNode(std::unique_ptr<Tile> aTile, int aX, int aY);

    void addNeighbor(TileNode &aNeighbor);
    const std::vector<std::reference_wrapper<TileNode>> &getNeighbors() const;
    
    Tile &getTile() const;

    void setWeight(int aWeight);
    int getWeight() const;

    int getX() const;
    int getY() const;

private:
    std::unique_ptr<Tile> mTile;
    std::vector<std::reference_wrapper<TileNode>> mNeighbors;

    int mWeight;

    int mX;
    int mY;
};

#endif // TILENODE_H