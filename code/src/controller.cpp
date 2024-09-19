#include "controller.h"

controller::controller(std::vector<parsedPerson> aPersons, parsedGrid aGrid)
{
    mPersons = aPersons;
    mGrid = aGrid;
}

void controller::createLevel()
{
    mModel.createLevel(mPersons, mGrid);
}