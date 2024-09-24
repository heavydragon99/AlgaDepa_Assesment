#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
#include "structs.h"

class controller {
public:
    controller(std::vector<ParsedPerson> aPersons, ParsedGrid aGrid);

    void createLevel();
    void run();

private:
    model mModel;
    std::vector<ParsedPerson> mPersons;
    ParsedGrid mGrid;
};

#endif // CONTROLLER_H
