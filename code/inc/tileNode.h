#ifndef TILENODE_H
#define TILENODE_H

#include "tile.h"
#include "tileEdge.h"

#include <memory>
#include <vector>

class tileNode
{
public:
    tileNode(std::unique_ptr<tile> aTile);

    void addEdge(std::shared_ptr<tileEdge> aEdge);
    const std::vector<std::shared_ptr<tileEdge>> &getEdges() const;
    tile &getTile() const;

    void setWeight(float aWeight);
    float getWeight() const;

private:
    std::unique_ptr<tile> mTile;
    std::vector<std::shared_ptr<tileEdge>> mEdges;
    float mWeight;
};

#endif // TILENODE_H