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
    Controller();

    void initialize();
    void run();

private:
    void setCommands();
    void handleMouseInput();
    void checkInputs();
    void handleUserInput();
    void rearrangeTile();
    void loadPreviousMemento();
    void loadNextMemento();
    void speedUp();
    void slowDown();
    void runPathFinding();
    void createLevel();

private:
    std::unique_ptr<Model> mModel;
    std::unique_ptr<View> mView;
    std::vector<ParsedPerson> mPersons;
    ParsedGrid mGrid;

    std::unique_ptr<CollisionHandler> mCollisionHandler;
    std::unique_ptr<InputHandler> mInputHandler;

    const int mFPSView = 60;
    int mCurrentFPSLogic = 40;

    std::optional<std::pair<int, int>> mPathfindingStart;
    std::optional<std::pair<int, int>> mPathfindingEnd;
};

#endif // CONTROLLER_H
