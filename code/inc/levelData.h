#ifndef LEVELDATA_H
#define LEVELDATA_H

#define MAX_PEOPLE 50000

#include "artist.h"
#include "structs.h"
#include "tileNode.h"

#include <memory>
#include <vector>
#include <utility>

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
    std::vector<std::pair<char, int>>& getGridWeights();

    void addArtist(const Tile& aTile);
    void deleteArtist(const Tile& aTile);
    void infectTiles(const Tile& aTile);

    void updateTile(int aX, int aY);
    void connectNeighbors();

private:
    void setNodeWeights();
    float calculateWeight(const TileNode& aNode);

private:
    std::vector<Artist> mPeople;
    std::vector<TileNode> mGrid;
    int mCols;
    int mRows;
    std::vector<std::pair<char, int>> mGridWeights;
};

#endif // LEVELDATA_H
