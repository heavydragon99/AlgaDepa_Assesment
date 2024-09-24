#include "levelData.h"

#include "personFactory.h"
#include "tileFactory.h"
#include "iPerson.h"
#include "tileNode.h"
#include "tileEdge.h"

#include <iostream>

levelData::levelData() : mCols(0), mRows(0) {}

levelData::~levelData() {}

void levelData::updateLevelData()
{
    // Implement the update logic for the level data
}

void levelData::buildLevelData(std::vector<parsedPerson> aPersons, parsedGrid aGrid)
{
    // Clear existing data
    mPeople.clear();
    mGrid.clear();

    // Set rows and cols
    mRows = aGrid.rows;
    mCols = aGrid.cols;

    // Fill mGridColor with all the different colors
    for (const gridColor &color : aGrid.gridColors)
    {
        mGridColor.push_back(color);
    }

    // Create persons and add to mPeople
    for (const parsedPerson &personIterator : aPersons)
    {
        std::unique_ptr<iPerson> person = personFactory::createPerson(personIterator.type, personIterator.x, personIterator.y, personIterator.vx, personIterator.vy);
        mPeople.push_back(std::move(person));
    }

    // Create tiles and add to mGrid
    mGrid.resize(mRows * mCols);
    for (int row = 0; row < mRows; ++row)
    {
        for (int col = 0; col < mCols; ++col)
        {
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
            tileNode *currentNode = mGrid[row * mCols + col].get();
            float weight = calculateWeight(currentNode);
            currentNode->setWeight(weight);
        }
    }
}

float levelData::calculateWeight(tileNode *aNode)
{
    char color = aNode->getTile()->getColor();
    for (const gridColor &gridColor : mGridColor)
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
            tileNode *currentNode = mGrid[row * mCols + col].get();
            if (row > 0)
            {
                auto edge = std::make_shared<tileEdge>(*currentNode, *mGrid[(row - 1) * mCols + col].get()); // Up
                currentNode->addEdge(edge);
                mGrid[(row - 1) * mCols + col]->addEdge(edge);
            }
            if (row < mRows - 1)
            {
                auto edge = std::make_shared<tileEdge>(*currentNode, *mGrid[(row + 1) * mCols + col].get()); // Down
                currentNode->addEdge(edge);
                mGrid[(row + 1) * mCols + col]->addEdge(edge);
            }
            if (col > 0)
            {
                auto edge = std::make_shared<tileEdge>(*currentNode, *mGrid[row * mCols + (col - 1)].get()); // Left
                currentNode->addEdge(edge);
                mGrid[row * mCols + (col - 1)]->addEdge(edge);
            }
            if (col < mCols - 1)
            {
                auto edge = std::make_shared<tileEdge>(*currentNode, *mGrid[row * mCols + (col + 1)].get()); // Right
                currentNode->addEdge(edge);
                mGrid[row * mCols + (col + 1)]->addEdge(edge);
            }
        }
    }
}

int levelData::getCols() const
{
    return mCols;
}

int levelData::getRows() const
{
    return mRows;
}

int levelData::getX(int tileIndex) const
{
    return tileIndex % mCols;
}

int levelData::getY(int tileIndex) const
{
    return tileIndex / mCols;
}

int levelData::getTotalTiles() const
{
    return mCols * mRows;
}

void levelData::getGridColor(int tileIndex, int &red, int &green, int &blue) const
{
    int row = getY(tileIndex);
    int col = getX(tileIndex);
    char color = mGrid[row * mCols + col]->getTile()->getColor();
    for (const gridColor &gridColor : mGridColor)
    {
        if (gridColor.letter == color)
        {
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