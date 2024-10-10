#ifndef MODEL_H
#define MODEL_H

#include "levelData.h"
#include "structs.h"

#include <vector>

class Model {
public:
    Model();
    void createLevel(std::vector<ParsedPerson> aPersons, ParsedGrid aGrid);
    const LevelData& getLevelData() const;

    void updateModel();

private:
    LevelData mLevel;
};

#endif // MODEL_H
