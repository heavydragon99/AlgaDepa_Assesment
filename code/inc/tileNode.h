#ifndef TILENODE_H
#define TILENODE_H

#include "tile.h"


#include <memory>
#include <vector>

class tileNode
{
public:
    tileNode(std::unique_ptr<tile> aTile);

    void addNeighbor(tileNode &aNeighbor);
    const std::vector<std::reference_wrapper<tileNode>> &getNeighbors() const;
    
    const tile &getTile() const;

    void setWeight(float aWeight);
    float getWeight() const;

private:
    std::unique_ptr<tile> mTile;
    std::vector<std::reference_wrapper<tileNode>> mNeighbors;

    float mWeight;
};

#endif // TILENODE_H