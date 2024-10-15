#ifndef MODEL_H
#define MODEL_H

#include "levelData.h"
#include "structs.h"

#include <vector>

class Model {
public:
    Model();
    void createLevel(std::vector<ParsedPerson> aPersons, ParsedGrid aGrid);
    LevelData& getLevelData();

    void updateModel();

private:
    LevelData mLevel;
};

#endif // MODEL_H
