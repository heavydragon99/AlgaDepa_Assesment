#include "tileNode.h"

tileNode::tileNode(std::unique_ptr<tile> aTile)
    : mTile(std::move(aTile)) {}

void tileNode::addEdge(std::shared_ptr<tileEdge> aEdge)
{
    mEdges.push_back(aEdge);
}

const std::vector<std::shared_ptr<tileEdge>> &tileNode::getEdges() const
{
    return mEdges;
}

tile &tileNode::getTile() const
{
    return *mTile.get();
}

void tileNode::setWeight(float aWeight) { mWeight = aWeight; }

float tileNode::getWeight() const { return mWeight; }