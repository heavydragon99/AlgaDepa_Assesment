#include "levelData.h"

#include "iPerson.h"
#include "personFactory.h"
#include "tileEdge.h"
#include "tileFactory.h"
#include "tileNode.h"

#include <iostream>

levelData::levelData() : mCols(0), mRows(0) {}

levelData::~levelData() {}

bool levelData::isColliding(std::unique_ptr<iPerson>& person1, std::unique_ptr<iPerson>& person2) {
    const float artistWidth = 0.5f;
    const float artistHeight = 0.5f;

    // std::cout << "Person1 x,y: " << person1->getX() << ", " << person1->getY() << std::endl;
    // std::cout << "Person2 x,y: " << person2->getX() << ", " << person2->getY() << std::endl;

    if (person1->getX() + artistWidth >= person2->getX() && person1->getX() <= person2->getX() + artistWidth &&
        person1->getY() + artistHeight >= person2->getY() && person1->getY() <= person2->getY() + artistHeight) {

        return true;
    }
    return false;
}

bool levelData::checkCollisions() {
    // for (size_t i = 0; i < mPeople.size(); ++i) {
    //     for (size_t j = i + 1; j < mPeople.size(); ++j) {
    //         if (isColliding(mPeople[i], mPeople[j])) {
    //             std::cout << "Collision detected between rectangle " << i << " and rectangle " << j << std::endl;
    //             return true;
    //         }
    //     }
    // for (const auto& basePerson : mPeople) {
    //     for (const auto& checkPerson : mPeople) {
    //         if (isColliding(basePerson, checkPerson)) {
    //             return true;
    //         }
    //     }
    // }
    for (int i = 0; i < getPersonCount(); i++) {
        if (mPeople[i]->getX() > mRows || mPeople[i]->getX() < 0) {
            return true;
        }
        if (mPeople[i]->getY() > mCols || mPeople[i]->getY() < 0) {
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
// bool levelData::somethingColliding() {
//     const float artistWidth = 0.5f;
//     const float artistHeight = 0.5f;
//
//     for (auto& basePerson : mPeople) {
//         if (basePerson->getX() > mCols) {
//             return true;
//         }
//         if (basePerson->getY() > mRows) {
//             return true;
//         }
//         for (auto& checkPerson : mPeople) {
//             if ((basePerson->getX() + artistWidth) > checkPerson->getX()) {
//             }
//         }
//     }
//
//     return false;
// }

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
        std::unique_ptr<iPerson> person = personFactory::createPerson(
            personIterator.type, personIterator.x, personIterator.y, personIterator.vx, personIterator.vy);
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

void levelData::setNodeWeights()
{
    for (int row = 0; row < mRows; ++row)
    {
        for (int col = 0; col < mCols; ++col)
        {
            tileNode& currentNode = *mGrid[row * mCols + col].get();
            float weight = calculateWeight(currentNode);
            currentNode.setWeight(weight);
        }
    }
}

float levelData::calculateWeight(const tileNode& aNode)
{
    char color = aNode.getTile().getColor();
    for (const GridColor &gridColor : mGridColor)
    {
        if (gridColor.letter == color)
        {
            return static_cast<float>(gridColor.weight);
        }
    }
    return 1.0f; // Default weight
}

void levelData::connectNeighbors()
{
    for (int row = 0; row < mRows; ++row)
    {
        for (int col = 0; col < mCols; ++col)
        {
            tileNode &currentNode = *mGrid[row * mCols + col].get();
            if (row > 0)
            {
                auto edge = std::make_shared<tileEdge>(currentNode, *mGrid[(row - 1) * mCols + col].get()); // Up
                currentNode.addEdge(edge);
                mGrid[(row - 1) * mCols + col]->addEdge(edge);
            }
            if (row < mRows - 1)
            {
                auto edge = std::make_shared<tileEdge>(currentNode, *mGrid[(row + 1) * mCols + col].get()); // Down
                currentNode.addEdge(edge);
                mGrid[(row + 1) * mCols + col]->addEdge(edge);
            }
            if (col > 0)
            {
                auto edge = std::make_shared<tileEdge>(currentNode, *mGrid[row * mCols + (col - 1)].get()); // Left
                currentNode.addEdge(edge);
                mGrid[row * mCols + (col - 1)]->addEdge(edge);
            }
            if (col < mCols - 1)
            {
                auto edge = std::make_shared<tileEdge>(currentNode, *mGrid[row * mCols + (col + 1)].get()); // Right
                currentNode.addEdge(edge);
                mGrid[row * mCols + (col + 1)]->addEdge(edge);
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

int levelData::getPersonX(int personIndex) const { return mPeople[personIndex]->getX(); }
int levelData::getPersonY(int personIndex) const { return mPeople[personIndex]->getY(); }
