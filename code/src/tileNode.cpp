#include "tileNode.h"

TileNode::TileNode(std::unique_ptr<Tile> aTile, int aX, int aY)
    : mTile(std::move(aTile)), mX(aX), mY(aY), mIsPath(false), mIsVisited(false) {}

void TileNode::addNeighbor(TileNode &aNeighbor)
{
    mNeighbors.push_back(aNeighbor);
}

const std::vector<std::reference_wrapper<TileNode>> &TileNode::getNeighbors() const
{
    return mNeighbors;
}

Tile &TileNode::getTile() const
{
    return *mTile.get();
}

void TileNode::setWeight(int aWeight) { mWeight = aWeight; }

int TileNode::getWeight() const { return mWeight; }

int TileNode::getX() const { return mX; }

int TileNode::getY() const { return mY; }

void TileNode::setIsPath(bool aIsPath) { mIsPath = aIsPath; }

bool TileNode::isPath() const { return mIsPath; }

void TileNode::setIsVisited(bool aIsVisited) { mIsVisited = aIsVisited; }

bool TileNode::isVisited() const { return mIsVisited; }
