#include "Memento.h"

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
}

ParsedGrid Memento::getState() { return mGrid; }