#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "CollisionHandler.h"
#include "Command.h"
#include "Input.h"
#include "Model.h"
#include "Structs.h"
#include "View.h"

#include <optional>
#include <vector>

/**
 * @class Controller
 * @brief Manages the main control flow of the application, including initialization, input handling, and game loop.
 */
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
    std::unique_ptr<Model> mModel; ///< The model of the application.
    std::unique_ptr<View> mView; ///< The view of the application.
    std::vector<ParsedPerson> mPersons; ///< List of parsed persons.
    ParsedGrid mGrid; ///< The parsed grid.

    std::unique_ptr<CollisionHandler> mCollisionHandler; ///< Handles collision detection.
    std::unique_ptr<InputHandler> mInputHandler; ///< Handles user input.

    const int mFPSView = 60; ///< Frames per second for rendering the view.
    int mCurrentFPSLogic = 40; ///< Current frames per second for logic updates.

    std::optional<std::pair<int, int>> mPathfindingStart; ///< Start point for pathfinding.
    std::optional<std::pair<int, int>> mPathfindingEnd; ///< End point for pathfinding.
};

#endif // CONTROLLER_H
