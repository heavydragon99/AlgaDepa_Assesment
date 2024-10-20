#include <chrono>
#include <iostream>
#include <thread>

#include "Command.h"
#include "PollingTUI.h"
#include "controller.h"
#include "view.h"

Controller::Controller(std::vector<ParsedPerson> aPersons, ParsedGrid aGrid)
    : mCollisionHandler(CollisionHandler(mModel.get())) {
    mPersons = aPersons;
    mGrid = aGrid;
}

void Controller::createLevel() {
    mModel = std::make_unique<Model>();
    mModel->createLevel(mPersons, mGrid);
    mView = std::make_unique<View>(*mModel);
    mView->setGridColor(mGrid.gridColors);
}

void Controller::checkInputs() {
    Input& input = Input::getInstance();

    const int frameDelayView = 1000 / mFPSView;
    input.update();

    std::vector<Uint8> downKeys = input.getDownKeys();

    for (int i = 0; i < downKeys.size(); i++) {
        mInputHandler.handleInput(downKeys[i]);
    }
}

void Controller::run() {
    bool pause = true;

    PollingTUI tui(mInputHandler);

    // Example input codes:
    // const int KEY_UP = 1;
    // const int KEY_DOWN = 2;
    // const int KEY_JUMP = 3;

    // Bind inputs to commands
    // inputHandler.setCommand(KEY_UP, std::make_unique<MoveUpCommand>());
    // inputHandler.setCommand(KEY_DOWN, std::make_unique<MoveDownCommand>());
    mInputHandler.setCommand((int)Key::Key_Space, std::make_unique<PlayPauseCommand>(pause));
    mInputHandler.setCommand((int)Key::Key_Enter, std::make_unique<RearrangeTileCommand>());
    mInputHandler.setCommand((int)Key::Key_O, std::make_unique<FileOpenCommand>());
    mInputHandler.setCommand((int)Key::Key_A, std::make_unique<ToggleRenderArtistsCommand>());
    mInputHandler.setCommand((int)Key::Key_Left, std::make_unique<BackwardInTimeCommand>());
    mInputHandler.setCommand((int)Key::Key_Right, std::make_unique<ForwardInTimeCommand>());

    const int frameDelayView = 1000 / mFPSView;
    // Render the data with the view class

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
            // tui.update();
            mView->render();
            handleUserInput();
            lastFrameTimeView = currentFrameTime;
        }
    }
}

void Controller::handleUserInput() {
    Input& input = Input::getInstance();
    input.update();
    if (!pause)
        mModel->updateModel();

    // mCollisionHandler.handleCollisions();

    if (input.GetKeyDown(Key::Key_Space)) {
        mModel->startStopSimulation();
    }

    if (input.GetKeyDown(Key::Key_Up)) {
        mCurrentFPSLogic++;
        std::cout << "Current FPS: " << mCurrentFPSLogic << std::endl;
    }
    if (input.GetKeyDown(Key::Key_Down)) {
        mCurrentFPSLogic = std::max(1, mCurrentFPSLogic - 1); // Ensure FPS doesn't go below 1
        std::cout << "Current FPS: " << mCurrentFPSLogic << std::endl;
    }

    if (input.GetKeyDown(Key::Key_D)) {
        mModel->setPathfindingAlgorithm();
    }

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
    }
}
