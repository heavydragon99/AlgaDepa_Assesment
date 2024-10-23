#ifndef LEVELDATA_H
#define LEVELDATA_H

#define MAX_PEOPLE 20000

#include "Artist.h"
#include "Structs.h"
#include "TileNode.h"

#include <memory>
#include <vector>
#include <utility>

class Tile;

/**
 * @brief Class representing the level data, including grid and people (artists) management.
 */
class LevelData {
public:
    LevelData();
    ~LevelData();

    void updateLevelData();
    void buildPersonData(std::vector<ParsedPerson> aPersons);
    void buildPersonData(std::vector<Artist> aPersons);
    void buildGridData(ParsedGrid aGrid);

    int getCols() const;
    int getRows() const;

    std::vector<TileNode>& getGrid();
    std::vector<Artist>& getPeople();
    std::vector<std::pair<char, int>>& getGridWeights();

    virtual void addArtist(const Tile& aTile); //Virtual so test can overwrite it
    virtual void deleteArtist(const Tile& aTile); //Virtual so test can overwrite it
    virtual void infectTiles(const Tile& aTile); //Virtual so test can overwrite it

    void updateTile(int aX, int aY);
    void connectNeighbors();

private:
    void setNodeWeights();
    float calculateWeight(const TileNode& aNode);

private:
    std::vector<Artist> mPeople; ///< Vector of artists (people) in the level.
    std::vector<TileNode> mGrid; ///< Vector of tile nodes representing the grid.
    int mCols; ///< Number of columns in the grid.
    int mRows; ///< Number of rows in the grid.
    std::vector<std::pair<char, int>> mGridWeights; ///< Vector of pairs representing grid weights.
};

#endif // LEVELDATA_H