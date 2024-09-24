#include "controller.h"
#include "view.h"

#include <iostream>

controller::controller(std::vector<parsedPerson> aPersons, parsedGrid aGrid)
{
    mPersons = aPersons;
    mGrid = aGrid;
}

void controller::createLevel()
{
    mModel.createLevel(mPersons, mGrid);
}

void controller::run()
{
    // Render the data with the view class
    view vw(mModel);
    vw.render();
}