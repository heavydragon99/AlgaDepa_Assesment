#include "levelData.h"
#include "personFactory.h"
#include "tileFactory.h"
#include "iPerson.h"
#include "tile.h"
#include "tileNode.h"
#include "tileEdge.h"

#include <iostream>

levelData::levelData() : mCols(0), mRows(0) {}

levelData::~levelData() {}

void levelData::updateLevelData() {
    // Implement the update logic for the level data
}

void levelData::buildLevelData(std::vector<parsedPerson> aPersons, parsedGrid aGrid) {
    // Clear existing data
    mPeople.clear();
    mGrid.clear();

    // Set rows and cols
    mRows = aGrid.rows;
    mCols = aGrid.cols;

    // Fill mGridColor with all the different colors
    for (const gridColor& color : aGrid.gridColors) {
        mGridColor.push_back(color);
    }

    // Create persons and add to mPeople
    for (const parsedPerson& personIterator : aPersons) {
        std::unique_ptr<iPerson> person = personFactory::createPerson(personIterator.type, personIterator.x, personIterator.y, personIterator.vx, personIterator.vy);
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

    // Connect neighbors
    connectNeighbors();

    std::cout << "Level data built successfully!" << std::endl;
}

void levelData::connectNeighbors() {
    for (int row = 0; row < mRows; ++row) {
        for (int col = 0; col < mCols; ++col) {
            tileNode* currentNode = mGrid[row * mCols + col].get();
            if (row > 0) currentNode->addEdge(std::make_unique<tileEdge>(currentNode, mGrid[(row - 1) * mCols + col].get())); // Up
            if (row < mRows - 1) currentNode->addEdge(std::make_unique<tileEdge>(currentNode, mGrid[(row + 1) * mCols + col].get())); // Down
            if (col > 0) currentNode->addEdge(std::make_unique<tileEdge>(currentNode, mGrid[row * mCols + (col - 1)].get())); // Left
            if (col < mCols - 1) currentNode->addEdge(std::make_unique<tileEdge>(currentNode, mGrid[row * mCols + (col + 1)].get())); // Right
        }
    }
}

int levelData::getX(int tileIndex) const {
    return tileIndex % mCols;
}

int levelData::getY(int tileIndex) const {
    return tileIndex / mCols;
}

int levelData::getTotalTiles() const {
    return mCols * mRows;
}

void levelData::getGridColor(int tileIndex, int &red, int &green, int &blue) const {
    int row = getY(tileIndex);
    int col = getX(tileIndex);
    char color = mGrid[row][col]->getTile()->getColor();
    for (const gridColor& gridColor : mGridColor) {
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