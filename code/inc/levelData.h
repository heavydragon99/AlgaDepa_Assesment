#ifndef LEVELDATA_H
#define LEVELDATA_H

#include "structs.h"
#include "tileNode.h"

#include <vector>
#include <memory>

class iPerson;
class tile;

class levelData {
public:
    levelData();
    ~levelData();

    void updateLevelData();
    void buildLevelData(std::vector<parsedPerson> aPersons, parsedGrid aGrid);

    int getX(int tileIndex) const;
    int getY(int tileIndex) const;
    int getTotalTiles() const;
    void getGridColor(int tileIndex, int &red, int &green, int &blue) const;

    int getPersonCount() const { return mPeople.size(); }
    int getPersonX(int personIndex) const { return mPeople[personIndex]->getX(); }
    int getPersonY(int personIndex) const { return mPeople[personIndex]->getY(); }

    private:
    void setNodeWeights();
    float calculateWeight(tileNode* aNode);
    void connectNeighbors();

private:
    std::vector<std::unique_ptr<iPerson>> mPeople;
    std::vector<std::unique_ptr<tileNode>> mGrid;
    int mCols;
    int mRows;
    std::vector<gridColor> mGridColor;
};

#endif // LEVELDATA_H