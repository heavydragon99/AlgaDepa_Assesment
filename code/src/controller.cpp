#include <chrono>
#include <iostream>
#include <thread>

#include "Command.h"
#include "PollingTUI.h"
#include "configuration.h"
#include "controller.h"
#include "view.h"

Controller::Controller(std::vector<ParsedPerson> aPersons, ParsedGrid aGrid)
    : mCollisionHandler(CollisionHandler(mModel.get())) {
    mPersons = aPersons;
    mGrid = aGrid;

    Configuration& config = Configuration::getInstance();
    config.setConfig("RenderQuadtree", false);
    config.setConfig("RenderArtists", true);
    config.setConfig("RenderPath", true);
    config.setConfig("RenderVisited", false);
    config.setConfig("CollisionWithPath", false);
    config.setConfig("PathfindingMethodDijkstra", true);
    config.setConfig("CollisionMethodQuadTree", true);
    config.setConfig("PauseTiles", true);
    config.setConfig("PauseArtists", true);

    mInputHandler.setCommand((int)Key::Key_O, std::make_unique<FileOpenCommand>());                // File Open
    mInputHandler.setCommand((int)Key::Key_C, std::make_unique<ChangeCollisionMethodCommand>());   // Change Collision
                                                                                                   // Method
    mInputHandler.setCommand((int)Key::Key_Q, std::make_unique<ToggleRenderQuadtreeCommand>());    // Toggle Render
                                                                                                   // Quadtree
    mInputHandler.setCommand((int)Key::Key_W, std::make_unique<ToggleCollisionWithPathCommand>()); // Toggle Collision
                                                                                                   // With Path
    mInputHandler.setCommand((int)Key::Key_P, std::make_unique<ToggleRenderPathCommand>());        // Toggle Render Path
    mInputHandler.setCommand((int)Key::Key_V, std::make_unique<ToggleRenderVisitedCommand>()); // Toggle Render Visited
    mInputHandler.setCommand((int)Key::Key_A, std::make_unique<ToggleRenderArtistsCommand>()); // Toggle Render Artists
    mInputHandler.setCommand((int)Key::Key_A, std::make_unique<ToggleRenderArtistsCommand>()); // Toggle Render Artists

    mInputHandler.setCommand((int)Key::Key_D, std::make_unique<ChangePathfindingMethodCommand>()); // Change Pathfinding
                                                                                                   // Method
    mInputHandler.setCommand((int)Key::Key_Enter, std::make_unique<RearrangeTileCommand>());       // Rearrange Tile
    mInputHandler.setCommand((int)Key::Key_Left, std::make_unique<BackwardInTimeCommand>());       // Backward In Time
    mInputHandler.setCommand((int)Key::Key_Right, std::make_unique<ForwardInTimeCommand>());       // Forward In Time
    mInputHandler.setCommand((int)Key::Key_Space, std::make_unique<PlayPauseTilesCommand>());      // Play/Pause
                                                                                                   // simulation
    mInputHandler.setCommand((int)Key::Key_LShift, std::make_unique<PlayPauseTilesCommand>());     // Play/Pause
                                                                                                   // artists
}

void Controller::createLevel() {
    mModel = std::make_unique<Model>();
    mModel->createLevel(mPersons, mGrid);
    mView = std::make_unique<View>(*mModel);
    mView->setGridColor(mGrid.gridColors);
}

void Controller::run() {
    const int frameDelayView = 1000 / mFPSView;

    this->mCollisionHandler = CollisionHandler(mModel.get());

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
            mCollisionHandler.handleCollisions();
            lastFrameTimeLogic = currentFrameTime;
        }
        auto frameStart = std::chrono::high_resolution_clock::now();

        // Render view at 60 FPS
        auto frameTimeView = currentFrameTime - lastFrameTimeView;
        int frameDurationView = std::chrono::duration_cast<std::chrono::milliseconds>(frameTimeView).count();
        if (frameDurationView >= frameDelayView) {
            mView->handleEvents(quit);
            checkInputs();
            mView->render();
            lastFrameTimeView = currentFrameTime;
        }
    }
}

void Controller::handleMouseInput() {
    Input& input = Input::getInstance();

    if (input.GetMouseButtonDown(MouseButton::LEFT)) {
        Point tileLocation = input.MousePosition();
        tileLocation.x = tileLocation.x / mView->getTileSize();
        tileLocation.y = tileLocation.y / mView->getTileSize();
        if (mPathfindingStart) {
            mPathfindingStart.reset();
            mPathfindingEnd.reset();
        }
        mPathfindingStart = std::make_pair(tileLocation.x, tileLocation.y);
        std::cout << "Start: " << mPathfindingStart->first << ", " << mPathfindingStart->second << std::endl;
        if (mPathfindingStart && mPathfindingEnd) {
            mModel->findPath(mPathfindingStart.value(), mPathfindingEnd.value());
            mPathfindingStart.reset();
            mPathfindingEnd.reset();
        }
    }

    if (input.GetMouseButtonDown(MouseButton::RIGHT)) {
        Point tileLocation = input.MousePosition();
        tileLocation.x = tileLocation.x / mView->getTileSize();
        tileLocation.y = tileLocation.y / mView->getTileSize();
        if (mPathfindingEnd) {
            mPathfindingStart.reset();
            mPathfindingEnd.reset();
            mView->render();
        }
        mPathfindingEnd = std::make_pair(tileLocation.x, tileLocation.y);
        std::cout << "End: " << mPathfindingEnd->first << ", " << mPathfindingEnd->second << std::endl;
        if (mPathfindingStart && mPathfindingEnd) {
            mModel->findPath(mPathfindingStart.value(), mPathfindingEnd.value());
            mPathfindingStart.reset();
            mPathfindingEnd.reset();
        }
    }
}

void Controller::checkInputs() {
    Input& input = Input::getInstance();
    static PollingTUI tui(mInputHandler);
    input.update();

    std::vector<Uint8> downKeys = input.getDownKeys();

    for (int i = 0; i < downKeys.size(); i++) {
        mInputHandler.handleInput(downKeys[i]);
    }

    handleMouseInput();
}
