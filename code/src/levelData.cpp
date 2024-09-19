#include "levelData.h"
#include "personFactory.h"
#include "tileFactory.h"
#include "iPerson.h"
#include "tile.h"

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
        tileColor tileColor;
        switch (color) {
            case 'R':
                tileColor = tileColor::Red;
                break;
            case 'B':
                tileColor = tileColor::Blue;
                break;
            case 'Y':
                tileColor = tileColor::Yellow;
                break;
            case 'G':
                tileColor = tileColor::Gray;
                break;
            case 'W':
                tileColor = tileColor::White;
                break;
            default:
                tileColor = tileColor::White; // Default to white if unknown
                break;
        }
        std::unique_ptr<tile> tile = tileFactory::createTile(tileColor);
        mGrid.push_back(std::move(tile));
    }
}