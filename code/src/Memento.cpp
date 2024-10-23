#include "Memento.h"

/**
 * @brief Constructs a Memento with the given LevelData.
 * @param aLevelData The LevelData to store.
 */
Memento::Memento(LevelData& aLevelData) {
    ParsedGrid grid;

    grid.rows = aLevelData.getRows();
    grid.cols = aLevelData.getCols();

    for(auto& gridWeight : aLevelData.getGridWeights()) {
        GridColor gridColor;
        gridColor.letter = gridWeight.first;
        gridColor.weight = gridWeight.second;
        grid.gridColors.push_back(gridColor);
    }

    for(auto& tileNode : aLevelData.getGrid()) {
        grid.grid.push_back(tileNode.getTile().getColor());
    }

    mPeople = aLevelData.getPeople();
    mGrid = grid;
}

/**
 * @brief Gets the stored grid.
 * @return The stored ParsedGrid.
 */
ParsedGrid Memento::getGrid() {
    return mGrid;
}

/**
 * @brief Gets the stored people.
 * @return A reference to the stored vector of Artist.
 */
std::vector<Artist>& Memento::getPeople() {
    return mPeople;
}