#include "levelData.h"
#include "personFactory.h"
#include "tileFactory.h"
#include "iPerson.h"
#include "tile.h"

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
    for (const char& color : aGrid.grid) {
        std::unique_ptr<tile> tile = tileFactory::createTile(color);
        mGrid.push_back(std::move(tile));
    }
    std::cout << "Level data built successfully!" << std::endl;
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
    char color = mGrid[tileIndex]->getColor();
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