#include "levelData.h"

#include "artist.h"
#include "tileFactory.h"
#include "tileNode.h"

#include <iostream>

levelData::levelData() : mCols(0), mRows(0) {}

levelData::~levelData() {}

bool levelData::isColliding(std::unique_ptr<artist>& person1, std::unique_ptr<artist>& person2) {
    const float artistWidth = 0.5f;
    const float artistHeight = 0.5f;

    if (person1->getX() + artistWidth >= person2->getX() && person1->getX() <= person2->getX() + artistWidth &&
        person1->getY() + artistHeight >= person2->getY() && person1->getY() <= person2->getY() + artistHeight) {

        return true;
    }
    return false;
}

bool levelData::checkCollisions() {
    const float artistWidth = 0.5f;
    const float artistHeight = 0.5f;

    for (int i = 0; i < getPersonCount(); i++) {
        if (mPeople[i]->getX() + artistWidth > mRows || mPeople[i]->getX() < 0) {
            return true;
        }
        if (mPeople[i]->getY() + artistHeight > mCols || mPeople[i]->getY() < 0) {
            return true;
        }

        for (int j = 0; j < getPersonCount(); j++) {
            if (i == j)
                continue;

            if (isColliding(mPeople[i], mPeople[j])) {
                return true;
            }
        }
    }
    return false;
}

void levelData::updateLevelData() {
    // Implement the update logic for the level data

    for (auto& person : mPeople) {
        float personX = person->getX();
        float personY = person->getY();
        person->update();
        if (checkCollisions()) {
            std::cout << "COLLISIONS" << std::endl;
            person->setX(personX);
            person->setY(personY);
            person->collided();
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

    // Fill mGridColor with all the different colors
    for (const GridColor& color : aGrid.gridColors) {
        mGridColor.push_back(color);
    }

    // Create persons and add to mPeople
    for (const ParsedPerson& personIterator : aPersons) {
        std::unique_ptr<artist> person =
            std::make_unique<artist>(personIterator.x, personIterator.y, personIterator.vx, personIterator.vy);
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
    setNodeWeights();

    // Connect neighbors
    connectNeighbors();

    std::cout << "Level data built successfully!" << std::endl;
}

void levelData::setNodeWeights() {
    for (int row = 0; row < mRows; ++row) {
        for (int col = 0; col < mCols; ++col) {
            tileNode& currentNode = *mGrid[row * mCols + col].get();
            float weight = calculateWeight(currentNode);
            currentNode.setWeight(weight);
        }
    }
}

float levelData::calculateWeight(const tileNode& aNode) {
    char color = aNode.getTile().getColor();
    for (const GridColor& gridColor : mGridColor) {
        if (gridColor.letter == color) {
            return static_cast<float>(gridColor.weight);
        }
    }
    return 1.0f; // Default weight
}

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

int levelData::getX(int tileIndex) const { return tileIndex % mCols; }

int levelData::getY(int tileIndex) const { return tileIndex / mCols; }

int levelData::getTotalTiles() const { return mCols * mRows; }

void levelData::getGridColor(int tileIndex, int& red, int& green, int& blue) const {
    int row = getY(tileIndex);
    int col = getX(tileIndex);
    char color = mGrid[row * mCols + col].get()->getTile().getColor();
    for (const GridColor& gridColor : mGridColor) {
        if (gridColor.letter == color) {
            red = gridColor.red;
            green = gridColor.green;
            blue = gridColor.blue;
            return;
        }
    }
    red = 255;
    green = 255;
    blue = 255;
}

const std::vector<std::unique_ptr<artist>>& levelData::getPeople() const { return mPeople; }
