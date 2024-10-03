#include "tileNode.h"

tileNode::tileNode(std::unique_ptr<tile> aTile)
    : mTile(std::move(aTile)) {}

void tileNode::addNeighbor(tileNode &aNeighbor)
{
    mNeighbors.push_back(aNeighbor);
}

const std::vector<std::reference_wrapper<tileNode>> &tileNode::getNeighbors() const
{
    return mNeighbors;
}

const tile &tileNode::getTile() const
{
    return *mTile.get();
}

void tileNode::setWeight(float aWeight) { mWeight = aWeight; }

float tileNode::getWeight() const { return mWeight; }