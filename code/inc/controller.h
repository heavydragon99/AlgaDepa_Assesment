#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "structs.h"
#include "model.h"

class controller
{
public:
    controller(std::vector<parsedPerson> aPersons, parsedGrid aGrid);

    void createLevel();
    void run();

private:
    model mModel;
    std::vector<parsedPerson> mPersons;
    parsedGrid mGrid;
};

#endif // CONTROLLER_H