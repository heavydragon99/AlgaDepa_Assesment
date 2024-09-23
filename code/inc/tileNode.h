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

    void addEdge(std::unique_ptr<tileEdge> aEdge);
    const std::vector<std::unique_ptr<tileEdge>> &getEdges() const;
    tile *getTile() const;

private:
    std::unique_ptr<tile> mTile;
    std::vector<std::unique_ptr<tileEdge>> mEdges;
};

#endif // TILENODE_H