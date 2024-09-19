#ifndef LEVELDATA_H
#define LEVELDATA_H

#include "structs.h"

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

private:
    std::vector<std::unique_ptr<iPerson>> mPeople;
    std::vector<std::unique_ptr<tile>> mGrid;
    int mCols;
    int mRows;
    std::vector<gridColor> mGridColor;
};

#endif // LEVELDATA_H