#include "TileNode.h"

/**
 * @brief Constructs a TileNode with a given tile and coordinates.
 * @param aTile Unique pointer to a Tile object.
 * @param aX X-coordinate of the node.
 * @param aY Y-coordinate of the node.
 */
TileNode::TileNode(std::unique_ptr<Tile> aTile, int aX, int aY)
    : mTile(std::move(aTile)), mX(aX), mY(aY), mIsPath(false), mIsVisited(false) {}

/**
 * @brief Copy constructor for TileNode.
 * @param other The TileNode to copy from.
 */
TileNode::TileNode(const TileNode& other)
    : mTile(std::make_unique<Tile>(*other.mTile)), mX(other.mX), mY(other.mY), mWeight(other.mWeight),
      mIsPath(other.mIsPath), mIsVisited(other.mIsVisited), mNeighbors(other.mNeighbors) {}

/**
 * @brief Copy assignment operator for TileNode.
 * @param other The TileNode to copy from.
 * @return Reference to the assigned TileNode.
 */
TileNode& TileNode::operator=(const TileNode& other) {
    if (this == &other) {
        return *this;
    }
    mTile = std::make_unique<Tile>(*other.mTile);
    mX = other.mX;
    mY = other.mY;
    mWeight = other.mWeight;
    mIsPath = other.mIsPath;
    mIsVisited = other.mIsVisited;
    mNeighbors = other.mNeighbors;
    return *this;
}

/**
 * @brief Adds a neighboring TileNode.
 * @param aNeighbor Reference to the neighboring TileNode.
 */
void TileNode::addNeighbor(TileNode& aNeighbor) { mNeighbors.push_back(aNeighbor); }

/**
 * @brief Gets the list of neighboring TileNodes.
 * @return Vector of references to neighboring TileNodes.
 */
const std::vector<std::reference_wrapper<TileNode>>& TileNode::getNeighbors() const { return mNeighbors; }

/**
 * @brief Gets the Tile object associated with this node.
 * @return Reference to the Tile object.
 */
Tile& TileNode::getTile() const { return *mTile.get(); }

/**
 * @brief Sets the weight of the node.
 * @param aWeight The weight to set.
 */
void TileNode::setWeight(int aWeight) { mWeight = aWeight; }

/**
 * @brief Gets the weight of the node.
 * @return The weight of the node.
 */
int TileNode::getWeight() const { return mWeight; }

/**
 * @brief Gets the X-coordinate of the node.
 * @return The X-coordinate of the node.
 */
int TileNode::getX() const { return mX; }

/**
 * @brief Gets the Y-coordinate of the node.
 * @return The Y-coordinate of the node.
 */
int TileNode::getY() const { return mY; }

/**
 * @brief Sets the path flag of the node.
 * @param aIsPath The path flag to set.
 */
void TileNode::setIsPath(bool aIsPath) { mIsPath = aIsPath; }

/**
 * @brief Checks if the node is part of a path.
 * @return True if the node is part of a path, false otherwise.
 */
bool TileNode::isPath() const { return mIsPath; }

/**
 * @brief Sets the visited flag of the node.
 * @param aIsVisited The visited flag to set.
 */
void TileNode::setIsVisited(bool aIsVisited) { mIsVisited = aIsVisited; }

/**
 * @brief Checks if the node has been visited.
 * @return True if the node has been visited, false otherwise.
 */
bool TileNode::isVisited() const { return mIsVisited; }