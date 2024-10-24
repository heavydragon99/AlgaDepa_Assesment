#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include <iostream>
#include <set>
#include <tuple>
#include <vector>

#include "Artist.h"
#include "Configuration.h"
#include "Model.h"
#include "Quadtree.h"

#define QUADTREE_CAPACITY 4
#define QUADTREE_MAX_DEPTH 7

/**
 * @brief Handles collisions between artists and tiles.
 */
class CollisionHandler {
public:
    CollisionHandler(Model* aModel);
    ~CollisionHandler();

    void handleCollisions();
    bool isColliding(Artist& person1, Artist& person2);
    bool isColliding(Artist& person1, TileNode& tileNode);
    void naiveCollisionCheck();
    void quadTreeCollisionCheck();
    std::vector<Quadtree::Boundary> getBoundaries();

private:
    /**
     * @brief Stores previous collisions between artists and tiles.
     */
    std::set<std::tuple<Artist*, TileNode*>> mPreviousTileCollisions;

    /**
     * @brief Pointer to the model.
     */
    Model* mModel;
};

#endif // COLLISIONHANDLER_H
