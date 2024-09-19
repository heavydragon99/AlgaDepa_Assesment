#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "structs.h"
#include "model.h"

class controller{
    public:
    controller();

    void createLevel();

    private:
    model mModel;
    std::vector<parsedPerson> mPersons;
    parsedGrid mGrid;


};

#endif // CONTROLLER_H