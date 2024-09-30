#ifndef MODEL_H
#define MODEL_H

#include "levelData.h"
#include "structs.h"

#include <vector>

class model {
public:
    model();
    void createLevel(std::vector<ParsedPerson> aPersons, ParsedGrid aGrid);
    const levelData& getLevelData() const;

    void updateModel();

private:
    levelData mLevel;
};

#endif // MODEL_H
