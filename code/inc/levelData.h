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

    const std::vector<std::unique_ptr<tileNode>>& getGrid() const;
    const std::vector<std::unique_ptr<artist>>& getPeople() const;

private:
    // void setNodeWeights();
    // float calculateWeight(const tileNode& aNode);
    void connectNeighbors();

    bool checkCollisions();
    bool isColliding(std::unique_ptr<artist>& person1, std::unique_ptr<artist>& person2);

private:
    std::vector<std::unique_ptr<artist>> mPeople;
    std::vector<std::unique_ptr<tileNode>> mGrid;
    int mCols;
    int mRows;
};

#endif // LEVELDATA_H
