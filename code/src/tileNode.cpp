#include "tileNode.h"

tileNode::tileNode(std::unique_ptr<tile> aTile, int aX, int aY)
    : mTile(std::move(aTile)), mX(aX), mY(aY) {}

void tileNode::addNeighbor(tileNode &aNeighbor)
{
    mNeighbors.push_back(aNeighbor);
}

const std::vector<std::reference_wrapper<tileNode>> &tileNode::getNeighbors() const
{
    return mNeighbors;
}

tile &tileNode::getTile() const
{
    return *mTile.get();
}

void tileNode::setWeight(int aWeight) { mWeight = aWeight; }

int tileNode::getWeight() const { return mWeight; }

int tileNode::getX() const { return mX; }

int tileNode::getY() const { return mY; }