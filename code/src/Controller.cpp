#include "Controller.h"

#include "Command.h"
#include "Configuration.h"
#include "FileHandler.h"
#include "PollingTUI.h"
#include "View.h"

#include <chrono>
#include <iostream>
#include <thread>

/**
 * @brief Constructs a new Controller object and initializes configuration settings.
 */
Controller::Controller() {
    Configuration& config = Configuration::getInstance();
    config.setConfig("RenderQuadtree", true);
    config.setConfig("RenderArtists", true);
    config.setConfig("RenderPath", true);
    config.setConfig("RenderVisited", false);
    config.setConfig("CollisionWithPath", true);
    config.setConfig("PathfindingMethodDijkstra", true);
    config.setConfig("CollisionMethodQuadTree", false);
    config.setConfig("PauseTiles", true);
    config.setConfig("PauseArtists", true);
}

/**
 * @brief Initializes the controller, loads necessary data, and sets up the game level.
 */
void Controller::initialize() {
    FileHandler fileHandler;
    ParsedGrid grid = fileHandler.loadGrid("/home/seger/projects/dpa/code/grid.txt");
    std::vector<ParsedPerson> persons = fileHandler.loadArtist("artists.csv");

    mPersons = persons;
    mGrid = grid;

    createLevel();
    mCollisionHandler = std::make_unique<CollisionHandler>(mModel.get());
    mInputHandler = std::make_unique<InputHandler>();
    setCommands();
}

/**
 * @brief Creates the game level based on the loaded data.
 */
void Controller::createLevel() {
    mModel = std::make_unique<Model>();
    mModel->createLevel(mPersons, mGrid);
    mView = std::make_unique<View>(*mModel);
    mView->setGridColor(mGrid.gridColors);
}

/**
 * @brief Runs the main game loop.
 */
void Controller::run() {
    const int frameDelayView = 1000 / mFPSView;

    bool quit = false;

    auto lastFrameTimeView = std::chrono::high_resolution_clock::now();
    auto lastFrameTimeLogic = std::chrono::high_resolution_clock::now();

    while (!quit) {
        auto currentFrameTime = std::chrono::high_resolution_clock::now();
        int frameDelayLogic = 1000 / mCurrentFPSLogic;

        // Update logic at variable FPS
        auto frameTimeRest = currentFrameTime - lastFrameTimeLogic;
        int frameDurationLogic = std::chrono::duration_cast<std::chrono::milliseconds>(frameTimeRest).count();
        if (frameDurationLogic >= frameDelayLogic) {
            mModel->updateModel();
            mCollisionHandler->handleCollisions();
            lastFrameTimeLogic = currentFrameTime;
        }
        auto frameStart = std::chrono::high_resolution_clock::now();

        // Render view at 60 FPS
        auto frameTimeView = currentFrameTime - lastFrameTimeView;
        int frameDurationView = std::chrono::duration_cast<std::chrono::milliseconds>(frameTimeView).count();
        if (frameDurationView >= frameDelayView) {
            mView->handleEvents(quit);
            checkInputs();

            if (Configuration::getInstance().getConfig("RenderQuadtree")) {
                mView->setQuadtreeBoundaries(mCollisionHandler->getBoundaries());
            }

            mView->render();
            lastFrameTimeView = currentFrameTime;
        }
    }
}

/**
 * @brief Sets up the commands for input handling.
 */
void Controller::setCommands() {
    mInputHandler->setCommand((int)Key::Key_C, std::make_unique<ChangeCollisionMethodCommand>());   // Change Collision
                                                                                                    // Method
    mInputHandler->setCommand((int)Key::Key_Q, std::make_unique<ToggleRenderQuadtreeCommand>());    // Toggle Render
                                                                                                    // Quadtree
    mInputHandler->setCommand((int)Key::Key_W, std::make_unique<ToggleCollisionWithPathCommand>()); // Toggle Collision
                                                                                                    // With Path
    mInputHandler->setCommand((int)Key::Key_P, std::make_unique<ToggleRenderPathCommand>());    // Toggle Render Path
    mInputHandler->setCommand((int)Key::Key_V, std::make_unique<ToggleRenderVisitedCommand>()); // Toggle Render Visited
    mInputHandler->setCommand((int)Key::Key_A, std::make_unique<ToggleRenderArtistsCommand>()); // Toggle Render Artists

    mInputHandler->setCommand((int)Key::Key_D, std::make_unique<ChangePathfindingMethodCommand>(
                                                   [this]() { this->runPathFinding(); })); // Change Pathfinding
                                                                                           // Method
    mInputHandler->setCommand((int)Key::Key_Enter,
                              std::make_unique<RearrangeTileCommand>([this]() { this->rearrangeTile(); })); // Rearrange
                                                                                                            // Tile
    mInputHandler->setCommand((int)Key::Key_Left, std::make_unique<BackwardInTimeCommand>(
                                                      [this]() { this->loadPreviousMemento(); })); // Backward
                                                                                                   // In
                                                                                                   // Time
    mInputHandler->setCommand((int)Key::Key_Right,
                              std::make_unique<ForwardInTimeCommand>([this]() { this->loadNextMemento(); })); // Forward
                                                                                                              // In Time
    mInputHandler->setCommand((int)Key::Key_Space, std::make_unique<PlayPauseArtistsCommand>()); // Play/Pause
                                                                                                 // simulation
    mInputHandler->setCommand((int)Key::Key_LShift, std::make_unique<PlayPauseTilesCommand>());  // Play/Pause
                                                                                                 // artists
    mInputHandler->setCommand((int)Key::Key_Up,
                              std::make_unique<SpeedUpCommand>([this]() { this->speedUp(); })); // Speed
                                                                                                // Up
    mInputHandler->setCommand((int)Key::Key_Down,
                              std::make_unique<SlowDownCommand>([this]() { this->slowDown(); })); // Slow
                                                                                                  // Down
}

/**
 * @brief Handles mouse input events.
 */
void Controller::handleMouseInput() {
    Input& input = Input::getInstance();

    if (input.GetMouseButtonDown(MouseButton::LEFT)) {
        Point tileLocation = input.MousePosition();
        tileLocation.x = tileLocation.x / mView->getTileSize();
        tileLocation.y = tileLocation.y / mView->getTileSize();
        mPathfindingStart = std::make_pair(tileLocation.x, tileLocation.y);
        std::cout << "Start: " << mPathfindingStart->first << ", " << mPathfindingStart->second << std::endl;
        runPathFinding();
    }

    if (input.GetMouseButtonDown(MouseButton::RIGHT)) {
        Point tileLocation = input.MousePosition();
        tileLocation.x = tileLocation.x / mView->getTileSize();
        tileLocation.y = tileLocation.y / mView->getTileSize();
        mPathfindingEnd = std::make_pair(tileLocation.x, tileLocation.y);
        std::cout << "End: " << mPathfindingEnd->first << ", " << mPathfindingEnd->second << std::endl;
        runPathFinding();
    }
}

/**
 * @brief Runs the pathfinding algorithm.
 */
void Controller::runPathFinding() {
    if (mPathfindingStart && mPathfindingEnd) {
        mModel->findPath(mPathfindingStart.value(), mPathfindingEnd.value());
    }
}

/**
 * @brief Checks and processes user inputs.
 */
void Controller::checkInputs() {
    Input& input = Input::getInstance();
    static PollingTUI tui(*mInputHandler.get(), *mModel.get());
    input.update();

    // tui.update();

    std::vector<Uint8> downKeys = input.getDownKeys();

    for (int i = 0; i < downKeys.size(); i++) {
        mInputHandler->handleInput(downKeys[i]);
        std::cout << "Key: " << downKeys[i] << std::endl;
    }

    handleMouseInput();
}

/**
 * @brief Rearranges a tile based on the current mouse position.
 */
void Controller::rearrangeTile() {
    Point tileLocation = Input::getInstance().MousePosition();
    tileLocation.x = tileLocation.x / mView->getTileSize();
    tileLocation.y = tileLocation.y / mView->getTileSize();
    mModel->updateTile(tileLocation.x, tileLocation.y);
}

/**
 * @brief Loads the previous memento state.
 */
void Controller::loadPreviousMemento() {
    Configuration::getInstance().setConfig("PauseArtists", true);
    mModel->usePreviousMemento();
}

/**
 * @brief Loads the next memento state.
 */
void Controller::loadNextMemento() {
    Configuration::getInstance().setConfig("PauseArtists", true);
    mModel->useNextMemento();
}

/**
 * @brief Increases the logic update speed.
 */
void Controller::speedUp() { mCurrentFPSLogic += 1; }

/**
 * @brief Decreases the logic update speed.
 */
void Controller::slowDown() {
    if (mCurrentFPSLogic > 1) {
        mCurrentFPSLogic -= 1;
    }
}
