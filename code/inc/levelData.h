#ifndef LEVELDATA_H
#define LEVELDATA_H

#include "iObserver.h"
#include "structs.h"
#include "tileNode.h"

#include <memory>
#include <vector>

class artist;
class tile;

class levelData : public iObserver {
public:
    levelData();
    ~levelData();

    void updateLevelData();
    void buildLevelData(std::vector<ParsedPerson> aPersons, ParsedGrid aGrid);

    int getCols() const;
    int getRows() const;

    const std::vector<std::unique_ptr<tileNode>>& getGrid() const;
    const std::vector<std::unique_ptr<artist>>& getPeople() const;

    void update(const std::pair<int, int>& tilePos, const std::string& action) override;

private:
    // void setNodeWeights();
    // float calculateWeight(const tileNode& aNode);
    void connectNeighbors();

    bool checkCollisions(std::unique_ptr<artist>& aPerson);
    bool isColliding(const std::unique_ptr<artist>& aPerson1, const std::unique_ptr<artist>& aPerson2);

    void addArtist(int aX, int aY);
    void deleteArtist(int aX, int aY);

private:
    std::vector<std::unique_ptr<artist>> mPeople;
    std::vector<std::unique_ptr<tileNode>> mGrid;
    int mCols;
    int mRows;
};

#endif // LEVELDATA_H
