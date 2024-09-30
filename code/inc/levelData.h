#ifndef LEVELDATA_H
#define LEVELDATA_H

#include "structs.h"
#include "tileNode.h"

#include <memory>
#include <vector>

class artist;
class tile;

class levelData {
public:
    levelData();
    ~levelData();

    void updateLevelData();
    void buildLevelData(std::vector<ParsedPerson> aPersons, ParsedGrid aGrid);

    int getCols() const;
    int getRows() const;

    int getX(int tileIndex) const;
    int getY(int tileIndex) const;
    int getTotalTiles() const;
    void getGridColor(int tileIndex, int& red, int& green, int& blue) const;

    int getPersonCount() const { return mPeople.size(); }
    const std::vector<std::unique_ptr<artist>>& getPeople() const;

private:
    void setNodeWeights();
    float calculateWeight(const tileNode& aNode);
    void connectNeighbors();

    bool checkCollisions();
    bool isColliding(std::unique_ptr<artist>& person1, std::unique_ptr<artist>& person2);

private:
    std::vector<std::unique_ptr<artist>> mPeople;
    std::vector<std::unique_ptr<tileNode>> mGrid;
    int mCols;
    int mRows;
    std::vector<GridColor> mGridColor;
};

#endif // LEVELDATA_H
