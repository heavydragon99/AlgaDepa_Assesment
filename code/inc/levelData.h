#ifndef LEVELDATA_H
#define LEVELDATA_H

#define MAX_PEOPLE 100

#include "structs.h"
#include "tileNode.h"

#include <list>
#include <memory>
#include <vector>

class Artist;
class Tile;

class LevelData {
public:
    LevelData();
    ~LevelData();

    void updateLevelData();
    void buildLevelData(std::vector<ParsedPerson> aPersons, ParsedGrid aGrid);

    int getCols() const;
    int getRows() const;

    const std::vector<std::unique_ptr<TileNode>>& getGrid() const;
    const std::list<std::unique_ptr<Artist>>& getPeople() const;

    void addArtist(const Tile& aTile);
    void deleteArtist(const Tile& aTile);
    void infectTiles(const Tile& aTile);
private:
    void setNodeWeights();
    float calculateWeight(const TileNode& aNode);
    void connectNeighbors();

    bool checkCollisions(std::unique_ptr<Artist>& aPerson);
    bool isColliding(const std::unique_ptr<Artist>& aPerson1, const std::unique_ptr<Artist>& aPerson2);

    void addArtist(int aX, int aY);
    void deleteArtist(int aX, int aY);

private:
    std::list<std::unique_ptr<Artist>> mPeople;
    std::vector<std::unique_ptr<TileNode>> mGrid;
    int mCols;
    int mRows;
};

#endif // LEVELDATA_H
