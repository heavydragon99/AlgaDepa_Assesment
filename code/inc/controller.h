#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "CollisionHandler.h"
#include "Input.h"
#include "model.h"
#include "structs.h"
#include "view.h"

#include <vector>

class controller {
public:
    controller(std::vector<ParsedPerson> aPersons, ParsedGrid aGrid);

    void createLevel();
    void run();

private:
    std::unique_ptr<model> mModel;
    std::unique_ptr<view> mView;
    std::vector<ParsedPerson> mPersons;
    ParsedGrid mGrid;

    CollisionHandler mCollisionHandler;
};

#endif // CONTROLLER_H
