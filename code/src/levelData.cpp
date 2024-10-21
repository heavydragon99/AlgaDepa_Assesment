#include "levelData.h"

#include "artist.h"
#include "tileFactory.h"
#include "tileNode.h"

#include <cmath>
#include <iostream>
#include <utility>

LevelData::LevelData() : mCols(0), mRows(0) { TileFactory::setLevelData(this); }

LevelData::~LevelData() {}

void LevelData::updateLevelData() {
    for (auto& person : mPeople) {
        Artist::Location tile = person.update();
    }
}

void LevelData::buildPersonData(std::vector<ParsedPerson> aPersons) {
    // Clear existing data
    mPeople.clear();

    // Create persons and add to mPeople
    for (const ParsedPerson& personIterator : aPersons) {
        Artist::Location personLocation = {personIterator.x, personIterator.y};
        Artist person(personLocation, personIterator.vx, personIterator.vy);
        mPeople.push_back(person);
    }
}

void LevelData::buildGridData(ParsedGrid aGrid) {
    // Clear existing data
    mGrid.clear();

    // Set rows and cols
    mRows = aGrid.rows;
    mCols = aGrid.cols;

    // Create tiles and add to mGrid
    mGrid.resize(mRows * mCols);
    for (int row = 0; row < mRows; ++row) {
        for (int col = 0; col < mCols; ++col) {
            char color = aGrid.grid[row * mCols + col];
            std::unique_ptr<Tile> tile = TileFactory::createTile(color);
            mGrid[row * mCols + col] = TileNode(std::move(tile), col, row);
        }
    }

    // Set weights for each node
    for (auto& tileNode : mGrid) {
        int weight = 0;
        char color = tileNode.getTile().getColor();
        for (const GridColor& gridColor : aGrid.gridColors) {
            if (gridColor.letter == color) {
                weight = gridColor.weight;
            }
        }
        tileNode.setWeight(weight);
    }

    // Connect neighbors
    connectNeighbors();
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
        Artist person(personLocation, personIterator.vx, personIterator.vy);
        mPeople.push_back(person);
    }

    // Create tiles and add to mGrid
    mGrid.resize(mRows * mCols);
    for (int row = 0; row < mRows; ++row) {
        for (int col = 0; col < mCols; ++col) {
            char color = aGrid.grid[row * mCols + col];
            std::unique_ptr<Tile> tile = TileFactory::createTile(color);
            mGrid[row * mCols + col] = TileNode(std::move(tile), col, row);
        }
    }

    // Set weights for each node
    for (auto& tileNode : mGrid) {
        int weight = 0;
        char color = tileNode.getTile().getColor();
        for (const GridColor& gridColor : aGrid.gridColors) {
            if (gridColor.letter == color) {
                weight = gridColor.weight;
            }
        }
        tileNode.setWeight(weight);
    }

    // Set tile weights
    for(auto& gridColor : aGrid.gridColors) {
        mGridWeights.push_back(std::make_pair(gridColor.letter, gridColor.weight));
    }

    // Connect neighbors
    connectNeighbors();

    std::cout << "Level data built successfully!" << std::endl;
}

void LevelData::connectNeighbors() {
    for (int row = 0; row < mRows; ++row) {
        for (int col = 0; col < mCols; ++col) {
            TileNode& currentNode = mGrid[row * mCols + col];
            if (row > 0) {
                currentNode.addNeighbor(mGrid[(row - 1) * mCols + col]); // Up
            }
            if (row < mRows - 1) {
                currentNode.addNeighbor(mGrid[(row + 1) * mCols + col]); // Down
            }
            if (col > 0) {
                currentNode.addNeighbor(mGrid[row * mCols + (col - 1)]); // Left
            }
            if (col < mCols - 1) {
                currentNode.addNeighbor(mGrid[row * mCols + (col + 1)]); // Right
            }
        }
    }
}

int LevelData::getCols() const { return mCols; }

int LevelData::getRows() const { return mRows; }

std::vector<TileNode>& LevelData::getGrid() { return mGrid; }

std::vector<Artist>& LevelData::getPeople() { return mPeople; }

std::vector<std::pair<char, int>>& LevelData::getGridWeights() { return mGridWeights; }

void LevelData::addArtist(const Tile& aTile) {
    // if (mPeople.size() >= MAX_PEOPLE) {
    //     return; // Do not add a new person if the limit is reached
    // }

    for (auto& tileNode : mGrid) {
        if (&tileNode.getTile() == &aTile) {
            Artist::Location location = {static_cast<float>(tileNode.getX()), static_cast<float>(tileNode.getY())};
            float vx, vy;
            if (rand() % 2 == 0) {
                int randomValue;
                do {
                    randomValue = rand() % 41 - 20; // Generates a number between -20 and 20
                } while (randomValue == 0);
                vx = static_cast<float>(randomValue) / 100.0f; // Converts to a float between -0.2 and 0.2
                vy = 0.0f;
            } else {
                int randomValue;
                do {
                    randomValue = rand() % 41 - 20; // Generates a number between -20 and 20
                } while (randomValue == 0);
                vx = 0.0f;
                vy = static_cast<float>(randomValue) / 100.0f; // Converts to a float between -0.2 and 0.2
            }
            Artist person(location, vx, vy);

            mPeople.push_back(std::move(person));
        }
    }
}

void LevelData::deleteArtist(const Tile& aTile) {
    // return; // added to fix runtime error
    for (auto& tileNode : mGrid) {
        if (&tileNode.getTile() == &aTile) {
            int tileX = static_cast<int>(tileNode.getX());
            int tileY = static_cast<int>(tileNode.getY());
            for (auto it = mPeople.begin(); it != mPeople.end(); ++it) {
                int personX = static_cast<int>(it->getLocation().mX);
                int personY = static_cast<int>(it->getLocation().mY);
                if (personX == tileX && personY == tileY) {
                    mPeople.erase(it);
                    break;
                }
            }
        }
    }
}

void LevelData::infectTiles(const Tile& aTile) {
    for (auto& tileNode : mGrid) {
        if (&tileNode.getTile() == &aTile) {
            int neighborCount = tileNode.getNeighbors().size();
            if (neighborCount == 1) {
                tileNode.getNeighbors().at(0).get().getTile().forceBlue();
            } else if (neighborCount >= 2) {
                int firstIndex = rand() % neighborCount;
                int secondIndex;
                do {
                    secondIndex = rand() % neighborCount;
                } while (secondIndex == firstIndex);

                tileNode.getNeighbors().at(firstIndex).get().getTile().forceBlue();
                tileNode.getNeighbors().at(secondIndex).get().getTile().forceBlue();
            }
        }
    }
}

void LevelData::updateTile(int aX, int aY) {
    for (auto& tileNode : mGrid) {
        if (tileNode.getX() == aX && tileNode.getY() == aY) {
            tileNode.getTile().updateTile();
            break;
        }
    }
}
