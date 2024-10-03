#include "levelData.h"

#include "artist.h"
#include "tileFactory.h"
#include "tileNode.h"

#include <cmath>
#include <iostream>
#include <unordered_set>
#include <utility>

// Hash function for std::pair<int, int> to use in unordered_set
struct pair_hash {
    template <class T1, class T2> std::size_t operator()(const std::pair<T1, T2>& pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

levelData::levelData() : mCols(0), mRows(0) {}

levelData::~levelData() {}

bool levelData::isColliding(const std::unique_ptr<artist>& person1, const std::unique_ptr<artist>& person2) {
    const float artistWidth = 0.5f;
    const float artistHeight = 0.5f;

    const auto& loc1 = person1->getLocation();
    const auto& loc2 = person2->getLocation();

    if (loc1.mX + artistWidth >= loc2.mX && loc1.mX <= loc2.mX + artistWidth && loc1.mY + artistHeight >= loc2.mY &&
        loc1.mY <= loc2.mY + artistHeight) {
        return true;
    }
    return false;
}

bool levelData::checkCollisions(std::unique_ptr<artist>& aPerson) {
    const float artistWidth = 0.5f;
    const float artistHeight = 0.5f;

    const auto& loc = aPerson->getLocation();
    if (loc.mX + artistWidth > mCols || loc.mX < 0 || loc.mY + artistHeight > mRows || loc.mY < 0) {
        return true;
    }

    for (const auto& otherPerson : mPeople) {
        if (aPerson == otherPerson)
            continue;

        if (isColliding(aPerson, otherPerson)) {
            return true;
        }
    }
    return false;
}

void levelData::updateLevelData() {
    std::unordered_set<std::pair<int, int>, pair_hash> collisionMap;
    std::pair<int, int> intLocation;

    for (auto& person : mPeople) {
        artist::Location oldLocation = person->getLocation();
        artist::Location tile = person->update();
        if (checkCollisions(person)) {
            std::cout << "COLLISIONS" << std::endl;
            person->setLocation(oldLocation);
            person->collidedWall();
        }

        intLocation = {round(tile.mX), round(tile.mY)};
        collisionMap.insert(intLocation);
    }

    // Iterate over the collisionMap and update the corresponding tileNode
    for (const auto& loc : collisionMap) {
        int x = loc.first;
        int y = loc.second;

        // Calculate the index of the tileNode in the vector
        int index = y * mCols + x;

        // Ensure the index is within bounds
        if (index >= 0 && index < mGrid.size()) {
            mGrid.at(index)->getTile().updateTile();
        }
    }
}

void levelData::buildLevelData(std::vector<ParsedPerson> aPersons, ParsedGrid aGrid) {
    // Clear existing data
    mPeople.clear();
    mGrid.clear();

    // Set rows and cols
    mRows = aGrid.rows;
    mCols = aGrid.cols;

    // Create persons and add to mPeople
    for (const ParsedPerson& personIterator : aPersons) {
        artist::Location personLocation = {personIterator.x, personIterator.y};
        std::unique_ptr<artist> person = std::make_unique<artist>(personLocation, personIterator.vx, personIterator.vy);
        mPeople.push_back(std::move(person));
    }

    // Create tiles and add to mGrid
    mGrid.resize(mRows * mCols);
    for (int row = 0; row < mRows; ++row) {
        for (int col = 0; col < mCols; ++col) {
            char color = aGrid.grid[row * mCols + col];
            std::unique_ptr<tile> tile = tileFactory::createTile(color);
            mGrid[row * mCols + col] = std::make_unique<tileNode>(std::move(tile));
        }
    }

    // Set weights for each node
    // setNodeWeights();

    // Connect neighbors
    connectNeighbors();

    std::cout << "Level data built successfully!" << std::endl;
}

// void levelData::setNodeWeights() {
//     for (int row = 0; row < mRows; ++row) {
//         for (int col = 0; col < mCols; ++col) {
//             tileNode& currentNode = *mGrid[row * mCols + col].get();
//             float weight = calculateWeight(currentNode);
//             currentNode.setWeight(weight);
//         }
//     }
// }

// float levelData::calculateWeight(const tileNode& aNode) {
//     char color = aNode.getTile().getColor();
//     for (const GridColor& gridColor : mGridColor) {
//         if (gridColor.letter == color) {
//             return static_cast<float>(gridColor.weight);
//         }
//     }
//     return 1.0f; // Default weight
// }

void levelData::connectNeighbors() {
    for (int row = 0; row < mRows; ++row) {
        for (int col = 0; col < mCols; ++col) {
            tileNode& currentNode = *mGrid[row * mCols + col].get();
            if (row > 0) {
                currentNode.addNeighbor(*mGrid[(row - 1) * mCols + col].get()); // Up
            }
            if (row < mRows - 1) {
                currentNode.addNeighbor(*mGrid[(row + 1) * mCols + col].get()); // Down
            }
            if (col > 0) {
                currentNode.addNeighbor(*mGrid[row * mCols + (col - 1)].get()); // Left
            }
            if (col < mCols - 1) {
                currentNode.addNeighbor(*mGrid[row * mCols + (col + 1)].get()); // Right
            }
        }
    }
}

int levelData::getCols() const { return mCols; }

int levelData::getRows() const { return mRows; }

const std::vector<std::unique_ptr<tileNode>>& levelData::getGrid() const { return mGrid; }

const std::vector<std::unique_ptr<artist>>& levelData::getPeople() const { return mPeople; }

void levelData::update(const std::pair<int, int>& tilePos, const std::string& action) {
    {
        if (action == "addArtist") {
            // addArtistOnTile(tilePos);
            std::cout << "Adding artist on tile: " << tilePos.first << ", " << tilePos.second << std::endl;
        } else if (action == "removeArtist") {
            // removeArtistsOnTile(tilePos);
            std::cout << "Removing artist on tile: " << tilePos.first << ", " << tilePos.second << std::endl;
        }
    }
}
