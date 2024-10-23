#ifndef TILENODE_H
#define TILENODE_H

#include "Tile.h"

#include <memory>
#include <vector>

/**
 * @class TileNode
 * @brief Represents a node in a tile-based graph.
 */
class TileNode {
public:
    TileNode() = default; // Added so vector can be resized
    TileNode(std::unique_ptr<Tile> aTile, int aX, int aY);

    TileNode(const TileNode& other);
    TileNode& operator=(const TileNode& other);

    void addNeighbor(TileNode& aNeighbor);
    const std::vector<std::reference_wrapper<TileNode>>& getNeighbors() const;

    Tile& getTile() const;

    void setWeight(int aWeight);
    int getWeight() const;

    int getX() const;
    int getY() const;

    void setIsPath(bool aIsPath);
    bool isPath() const;

    void setIsVisited(bool aIsVisited);
    bool isVisited() const;

private:
    std::unique_ptr<Tile> mTile; ///< Pointer to the tile object.
    std::vector<std::reference_wrapper<TileNode>> mNeighbors; ///< List of neighboring TileNodes.

    int mWeight; ///< Weight of the node.
    int mX; ///< X-coordinate of the node.
    int mY; ///< Y-coordinate of the node.

    bool mIsPath; ///< Flag indicating if the node is part of a path.
    bool mIsVisited; ///< Flag indicating if the node has been visited.
};

#endif // TILENODE_H