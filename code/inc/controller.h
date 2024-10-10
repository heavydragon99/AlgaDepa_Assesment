#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
#include "structs.h"
#include "view.h"

#include <vector>

class Controller {
public:
    Controller(std::vector<ParsedPerson> aPersons, ParsedGrid aGrid);

    void createLevel();
    void run();

private:
    std::unique_ptr<Model> mModel;
    std::unique_ptr<View> mView;
    std::vector<ParsedPerson> mPersons;
    ParsedGrid mGrid;
};

#endif // CONTROLLER_H
