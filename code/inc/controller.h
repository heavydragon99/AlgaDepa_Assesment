#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "CollisionHandler.h"
#include "Command.h"
#include "Input.h"
#include "model.h"
#include "structs.h"
#include "view.h"

#include <optional>
#include <vector>

class Controller {
public:
    Controller(std::vector<ParsedPerson> aPersons, ParsedGrid aGrid);

    void createLevel();
    void run();

private:
    void handleUserInput();

private:
    std::unique_ptr<Model> mModel;
    std::unique_ptr<View> mView;
    std::vector<ParsedPerson> mPersons;
    ParsedGrid mGrid;

    CollisionHandler mCollisionHandler;

    const int mFPSView = 60;
    int mCurrentFPSLogic = 60;

    std::optional<std::pair<int, int>> mPathfindingStart;
    std::optional<std::pair<int, int>> mPathfindingEnd;
    InputHandler mInputHandler;

    void checkInputs();
};

#endif // CONTROLLER_H
