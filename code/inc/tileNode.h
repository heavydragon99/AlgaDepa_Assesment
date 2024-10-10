#ifndef TILENODE_H
#define TILENODE_H

#include "tile.h"

#include <memory>
#include <vector>

class tileNode
{
public:
    tileNode(std::unique_ptr<tile> aTile, int aX, int aY);

    void addNeighbor(tileNode &aNeighbor);
    const std::vector<std::reference_wrapper<tileNode>> &getNeighbors() const;
    
    tile &getTile() const;

    void setWeight(int aWeight);
    int getWeight() const;

    int getX() const;
    int getY() const;

private:
    std::unique_ptr<tile> mTile;
    std::vector<std::reference_wrapper<tileNode>> mNeighbors;

    int mWeight;

    int mX;
    int mY;
};

#endif // TILENODE_H