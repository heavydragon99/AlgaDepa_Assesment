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

LevelData::LevelData() : mCols(0), mRows(0) { TileFactory::setLevelData(this); }

LevelData::~LevelData() {}

void LevelData::updateLevelData() {
    for (auto& person : mPeople) {
        Artist::Location tile = person->update();
    }
}

void LevelData::buildLevelData(std::vector<ParsedPerson> aPersons, ParsedGrid aGrid) {
    // Clear existing data
    mPeople.clear();
    mGrid.clear();

    // Set rows and cols
    mRows = aGrid.rows;
    mCols = aGrid.cols;

    // Create persons and add to mPeople
    for (const ParsedPerson& personIterator : aPersons) {
        Artist::Location personLocation = {personIterator.x, personIterator.y};
        std::unique_ptr<Artist> person = std::make_unique<Artist>(personLocation, personIterator.vx, personIterator.vy);
        mPeople.push_back(std::move(person));
    }

    // Create tiles and add to mGrid
    mGrid.resize(mRows * mCols);
    for (int row = 0; row < mRows; ++row) {
        for (int col = 0; col < mCols; ++col) {
            char color = aGrid.grid[row * mCols + col];
            std::unique_ptr<Tile> tile = TileFactory::createTile(color);
            mGrid[row * mCols + col] = std::make_unique<TileNode>(std::move(tile), col, row);
        }
    }

    // Set weights for each node
    for (auto& tileNode : mGrid) {
        int weight = 0;
        char color = tileNode->getTile().getColor();
        for (const GridColor& gridColor : aGrid.gridColors) {
            if (gridColor.letter == color) {
                weight = gridColor.weight;
            }
        }
        tileNode->setWeight(weight);
    }

    // Connect neighbors
    connectNeighbors();

    std::cout << "Level data built successfully!" << std::endl;
}

void LevelData::connectNeighbors() {
    for (int row = 0; row < mRows; ++row) {
        for (int col = 0; col < mCols; ++col) {
            TileNode& currentNode = *mGrid[row * mCols + col].get();
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

int LevelData::getCols() const { return mCols; }

int LevelData::getRows() const { return mRows; }

const std::vector<std::unique_ptr<TileNode>>& LevelData::getGrid() const { return mGrid; }

const std::list<std::unique_ptr<Artist>>& LevelData::getPeople() const { return mPeople; }

void LevelData::addArtist(const Tile& aTile) {
    if (mPeople.size() >= MAX_PEOPLE) {
        return; // Do not add a new person if the limit is reached
    }

    for (auto& tileNode : mGrid) {
        if (&tileNode->getTile() == &aTile) {
            Artist::Location location = {static_cast<float>(tileNode->getX()), static_cast<float>(tileNode->getY())};
            float vx, vy;
            if (rand() % 2 == 0) {
                do {
                    vx = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f - 1.0f;
                } while (vx == 0.0f);
                vy = 0.0f;
            } else {
                vx = 0.0f;
                do {
                    vy = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f - 1.0f;
                } while (vy == 0.0f);
            }
            std::unique_ptr<Artist> person = std::make_unique<Artist>(location, vx, vy);

            mPeople.push_back(std::move(person));
        }
    }
}

void LevelData::deleteArtist(const Tile& aTile) {
    for (auto& tileNode : mGrid) {
        if (&tileNode->getTile() == &aTile) {
            int tileX = static_cast<int>(tileNode->getX());
            int tileY = static_cast<int>(tileNode->getY());
            for (auto it = mPeople.begin(); it != mPeople.end(); ++it) {
                int personX = static_cast<int>((*it)->getLocation().mX);
                int personY = static_cast<int>((*it)->getLocation().mY);
                if (personX == tileX && personY == tileY) {
                    mPeople.erase(it);
                    break;
                }
            }
        }
    }
}
