#include "tileNode.h"

tileNode::tileNode(std::unique_ptr<tile> aTile)
    : mTile(std::move(aTile)) // Correct initialization list
{
}

void tileNode::addEdge(std::unique_ptr<tileEdge> aEdge)
{
    mEdges.push_back(std::move(aEdge));
}

const std::vector<std::unique_ptr<tileEdge>> &tileNode::getEdges() const
{
    return mEdges;
}

tile *tileNode::getTile() const
{
    return mTile.get();
}