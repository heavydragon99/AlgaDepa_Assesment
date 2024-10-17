#ifndef LEVELDATA_H
#define LEVELDATA_H

#define MAX_PEOPLE 2000

#include "artist.h"
#include "structs.h"
#include "tileNode.h"

#include <list>
#include <memory>
#include <vector>

class Tile;

class LevelData {
public:
    LevelData();
    ~LevelData();

    void updateLevelData();
    void buildLevelData(std::vector<ParsedPerson> aPersons, ParsedGrid aGrid);

    int getCols() const;
    int getRows() const;

    std::vector<TileNode>& getGrid();
    std::vector<Artist>& getPeople();

    void addArtist(const Tile& aTile);
    void deleteArtist(const Tile& aTile);
    void infectTiles(const Tile& aTile);

private:
    void setNodeWeights();
    float calculateWeight(const TileNode& aNode);
    void connectNeighbors();

    bool checkCollisions(Artist& aPerson);
    bool isColliding(const Artist& aPerson1, const Artist& aPerson2);

    void addArtist(int aX, int aY);
    void deleteArtist(int aX, int aY);

private:
    std::vector<Artist> mPeople;
    std::vector<TileNode> mGrid;
    int mCols;
    int mRows;
};

#endif // LEVELDATA_H
