#ifndef MODEL_H
#define MODEL_H

#include "structs.h"
#include "levelData.h"

#include <vector>

class model {
public:
    model();
    void createLevel(std::vector<parsedPerson> aPersons, parsedGrid aGrid);

private:
    levelData mLevel;

};

#endif // MODEL_H