#include "CollisionHandler.h"

/**
 * @brief Construct a new CollisionHandler object
 *
 * @param aModel Pointer to the model object
 */
CollisionHandler::CollisionHandler(Model* aModel) : mModel(aModel) {}

/**
 * @brief Destroy the CollisionHandler object
 */
CollisionHandler::~CollisionHandler() {}

/**
 * @brief Handle collisions based on the configuration
 */
void CollisionHandler::handleCollisions() {
    if (Configuration::getInstance().getConfig("CollisionMethodQuadTree")) {
        quadTreeCollisionCheck();
    } else {
        naiveCollisionCheck();
    }
}

/**
 * @brief Check if two artists are colliding
 *
 * @param person1 Reference to the first artist
 * @param person2 Reference to the second artist
 * @return true if the artists are colliding
 * @return false if the artists are not colliding
 */
bool CollisionHandler::isColliding(Artist& person1, Artist& person2) {
    const float artistWidth = 0.5f;
    const float artistHeight = 0.5f;

    const auto& loc1 = person1.getLocation();
    const auto& loc2 = person2.getLocation();

    if (loc1.mX + artistWidth >= loc2.mX && loc1.mX <= loc2.mX + artistWidth && loc1.mY + artistHeight >= loc2.mY &&
        loc1.mY <= loc2.mY + artistHeight) {
        return true;
    }
    return false;
}

/**
 * @brief Check if an artist is colliding with a tile
 *
 * @param person1 Reference to the artist
 * @param tileNode Reference to the tile
 * @return true if the artist is colliding with the tile
 * @return false if the artist is not colliding with the tile
 */
bool CollisionHandler::isColliding(Artist& person1, TileNode& tileNode) {
    const float tileWidth = 1.0f;
    const float tileHeight = 1.0f;

    const Artist::Location& loc1 = person1.getLocation();

    if (loc1.mX >= tileNode.getX() && loc1.mX < tileNode.getX() + tileWidth && loc1.mY >= tileNode.getY() &&
        loc1.mY <= tileNode.getY() + tileHeight) {
        return true;
    }
    return false;
}

/**
 * @brief Perform a naive collision check between artists and tiles
 */
void CollisionHandler::naiveCollisionCheck() {
    const float artistWidth = 0.5f;
    const float artistHeight = 0.5f;

    int cols = mModel->getLevelData().getCols();
    int rows = mModel->getLevelData().getRows();

    // Reset collision states for all artists
    for (Artist& artist : mModel->getLevelData().getPeople()) {
        artist.resetRed();
    }

    // Reset update states for all tiles
    for (TileNode& tile : mModel->getLevelData().getGrid()) {
        tile.getTile().resetUpdate();
    }

    // Check for collisions between artists and walls
    for (Artist& firstPerson : mModel->getLevelData().getPeople()) {
        Artist::Location& loc = firstPerson.getLocation();
        if (loc.mX < 0 || loc.mY < 0) {
            firstPerson.collidedWall(false);
        }

        if (loc.mX + artistWidth > cols || loc.mY + artistHeight > rows) {
            firstPerson.collidedWall(true);
        }

        // Check for collisions between artists
        for (Artist& secondPerson : mModel->getLevelData().getPeople()) {
            if (&firstPerson == &secondPerson)
                continue;

            if (isColliding(firstPerson, secondPerson)) {
                firstPerson.collidedOtherArtist();
            }
        }
    }

    static std::set<std::tuple<Artist*, TileNode*>> previousCollisions;
    std::set<std::tuple<Artist*, TileNode*>> currentCollision;

    int amountOfArists = mModel->getLevelData().getPeople().size();

    // Check for collisions between artists and tiles
    for (int iArtist = 0; iArtist < amountOfArists; iArtist++) {
        Artist* person = &mModel->getLevelData().getPeople()[iArtist];
        Artist& personRef = mModel->getLevelData().getPeople()[iArtist];

        for (TileNode& tileItr : mModel->getLevelData().getGrid()) {
            TileNode* tile = &tileItr;

            if (isColliding(personRef, tileItr)) {
                std::tuple<Artist*, TileNode*> collisionKey = std::make_tuple(person, tile);

                if (previousCollisions.find(collisionKey) == previousCollisions.end()) {
                    if (!Configuration::getInstance().getConfig("PauseTiles")) {
                        tileItr.getTile().updateTile();
                    }
                }
                if (Configuration::getInstance().getConfig("CollisionWithPath")) {
                    if (tile->isPath()) {
                        person->triggerRed();
                    }
                }

                currentCollision.insert(collisionKey);
            }
        }
        amountOfArists = mModel->getLevelData().getPeople().size();
    }

    previousCollisions = std::move(currentCollision);
}

/**
 * @brief Perform a quadtree-based collision check between artists and tiles
 */
void CollisionHandler::quadTreeCollisionCheck() {
    const float artistWidth = 0.5f;
    const float artistHeight = 0.5f;
    const float tileWidth = 1.0f;
    const float tileHeight = 1.0f;
    int cols = mModel->getLevelData().getCols();
    int rows = mModel->getLevelData().getRows();

    Quadtree::Boundary boundary{0, 0, static_cast<float>(mModel->getLevelData().getCols()),
                                static_cast<float>(mModel->getLevelData().getRows())};

    Quadtree quadtree(boundary, QUADTREE_CAPACITY, 0, QUADTREE_MAX_DEPTH);

    // Insert all artists into the quadtree
    for (Artist& artist : mModel->getLevelData().getPeople()) {
        artist.resetRed();
        if (quadtree.insert(&artist) == false) {
            // std::cout << "Quadtree artist insertion failed" << std::endl;
        }
    }

    // Insert all tiles into the quadtree
    for (TileNode& tile : mModel->getLevelData().getGrid()) {
        tile.getTile().resetUpdate();
        if (quadtree.insert(&tile) == false) {
            // std::cout << "Quadtree tile insertion failed" << std::endl;
        }
    }

    std::set<std::tuple<Artist*, TileNode*>> currentTileCollisions;

    // Check for collisions between artists and walls
    for (Artist& artist : mModel->getLevelData().getPeople()) {
        Artist::Location& loc = artist.getLocation();
        if (loc.mX < 0 || loc.mY < 0) {
            artist.collidedWall(false);
        }

        if (loc.mX + artistWidth > cols || loc.mY + artistHeight > rows) {
            artist.collidedWall(true);
        }

        // Check for collisions between artists using quadtree
        Quadtree::Boundary artistBoundary{artist.getLocation().mX - artistWidth, artist.getLocation().mY - artistHeight,
                                          artistWidth * 2, artistHeight * 2};

        std::vector<Artist*> possibleArtistCollisions;
        quadtree.queryArtists(artistBoundary, possibleArtistCollisions);

        for (Artist* other : possibleArtistCollisions) {
            if (&artist != other && isColliding(artist, *other)) {
                artist.collidedOtherArtist();
            }
        }

        // Check for collisions between artists and tiles using quadtree
        std::vector<TileNode*> possibleTileCollisions;
        quadtree.queryTiles(artistBoundary, possibleTileCollisions);

        for (TileNode* tile : possibleTileCollisions) {
            if (isColliding(artist, *tile)) {
                std::tuple<Artist*, TileNode*> collisionKey = std::make_tuple(&artist, tile);

                if (mPreviousTileCollisions.find(collisionKey) == mPreviousTileCollisions.end()) {
                    if (!Configuration::getInstance().getConfig("PauseTiles")) {
                        tile->getTile().updateTile();
                    }
                }
                if (Configuration::getInstance().getConfig("CollisionWithPath")) {
                    if (tile->isPath()) {
                        artist.triggerRed();
                    }
                }

                currentTileCollisions.insert(collisionKey);
            }
        }
    }

    mPreviousTileCollisions = std::move(currentTileCollisions);
}

/**
 * @brief Get the boundaries of the quadtree
 *
 * @return std::vector<Quadtree::Boundary> Vector of quadtree boundaries
 */
std::vector<Quadtree::Boundary> CollisionHandler::getBoundaries() {
    if (!Configuration::getInstance().getConfig("CollisionMethodQuadTree")) {
        return std::vector<Quadtree::Boundary>(0);
    }

    Quadtree::Boundary boundary{0, 0, static_cast<float>(mModel->getLevelData().getCols()),
                                static_cast<float>(mModel->getLevelData().getRows())};

    Quadtree quadtree(boundary, QUADTREE_CAPACITY, 0, QUADTREE_MAX_DEPTH);

    // Insert all artists into the quadtree
    for (Artist& artist : mModel->getLevelData().getPeople()) {
        quadtree.insert(&artist);
    }

    // Insert all tiles into the quadtree
    for (TileNode& tile : mModel->getLevelData().getGrid()) {
        quadtree.insert(&tile);
    }

    return quadtree.getBoundaries();
}
