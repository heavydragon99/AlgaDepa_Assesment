#ifndef QUADTREE_H
#define QUADTREE_H

#include "Artist.h"
#include "TileNode.h"

#include <memory>
#include <vector>

/**
 * @brief A class representing a Quadtree data structure.
 */
class Quadtree {
public:
    /**
     * @brief A struct representing the boundary of a Quadtree node.
     */
    struct Boundary {
        float x;      ///< The x-coordinate of the boundary.
        float y;      ///< The y-coordinate of the boundary.
        float width;  ///< The width of the boundary.
        float height; ///< The height of the boundary.

        bool contains(const Artist::Location& loc) const;
        bool contains(float tileX, float tileY, float tileWidth, float tileHeight) const;
        bool intersects(const Boundary& other) const;
    };

    /**
     * @brief Constructs a Quadtree with a given boundary and capacity.
     * @param boundary The boundary of the Quadtree.
     * @param capacity The maximum number of elements a node can hold before subdividing.
     */
    Quadtree(const Boundary& boundary, int capacity, int depth = 0, int maxDepth = 2);

    bool insert(Artist* artist);
    bool insert(TileNode* tile);

    void queryArtists(const Boundary& range, std::vector<Artist*>& found) const;
    void queryTiles(const Boundary& range, std::vector<TileNode*>& found) const;

    /**
     * @brief Retrieves the boundaries of all nodes in the Quadtree.
     * @return A vector of boundaries.
     */
    std::vector<Boundary> getBoundaries();

private:
    /**
     * @brief Subdivides the Quadtree node into four children.
     */
    void subdivide();

    Boundary mBoundary;            ///< The boundary of the Quadtree node.
    int mCapacity;                 ///< The maximum number of elements a node can hold before subdividing.
    bool mDivided;                 ///< Indicates whether the node has been subdivided.
                                   ///
    int mDepth;                    ///< Current depth of the node.
    int mMaxDepth;                 ///< Maximum allowed depth.
                                   ///
    std::vector<Artist*> mArtists; ///< The artists contained in this node.
    std::vector<TileNode*> mTiles; ///< The tiles contained in this node.

    std::unique_ptr<Quadtree> mTopLeft;     ///< The top-left child node.
    std::unique_ptr<Quadtree> mTopRight;    ///< The top-right child node.
    std::unique_ptr<Quadtree> mBottomLeft;  ///< The bottom-left child node.
    std::unique_ptr<Quadtree> mBottomRight; ///< The bottom-right child node.
};

#endif // QUADTREE_H
