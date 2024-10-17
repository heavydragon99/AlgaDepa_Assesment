#include "controller.h"
#include "view.h"

#include <chrono>
#include <iostream>
#include <thread>

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

void Controller::run() {
    Input& input = Input::getInstance();

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

        // Render view at 60 FPS
        auto frameTimeView = currentFrameTime - lastFrameTimeView;
        int frameDurationView = std::chrono::duration_cast<std::chrono::milliseconds>(frameTimeView).count();
        if (frameDurationView >= frameDelayView) {
            mView->handleEvents(quit);
            mView->render();
            handleUserInput();
            lastFrameTimeView = currentFrameTime;
        }
    }
}

void Controller::handleUserInput() {
    Input& input = Input::getInstance();
    input.update();

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
        if (mPathfindingStart || mPathfindingEnd) {
            mPathfindingStart.reset();
            mPathfindingEnd.reset();
        }
        mPathfindingStart->first = tileLocation.x;
        mPathfindingStart->second = tileLocation.y;
        std::cout << "Start: " << mPathfindingStart->first << ", " << mPathfindingStart->second << std::endl;
        if (mPathfindingStart && mPathfindingEnd) {
            mModel->findPath(mPathfindingStart.value(), mPathfindingEnd.value());
        }
    }

    if (input.GetMouseButtonDown(MouseButton::RIGHT)) {
        Point tileLocation = input.MousePosition();
        tileLocation.x = tileLocation.x / mView->getTileSize();
        tileLocation.y = tileLocation.y / mView->getTileSize();
        if (mPathfindingStart || mPathfindingEnd) {
            mPathfindingStart.reset();
            mPathfindingEnd.reset();
        }
        mPathfindingEnd->first = tileLocation.x;
        mPathfindingEnd->second = tileLocation.y;
        std::cout << "End: " << mPathfindingEnd->first << ", " << mPathfindingEnd->second << std::endl;
        if (mPathfindingStart && mPathfindingEnd) {
            mModel->findPath(mPathfindingStart.value(), mPathfindingEnd.value());
        }
    }
}
