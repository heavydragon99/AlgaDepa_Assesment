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

    // const int FPS = 60;
    // const int frameDelay = 1000 / FPS;
    // Render the data with the view class

    this->mCollisionHandler = CollisionHandler(mModel.get());

    bool quit = false;

    while (!quit) {
        input.update();

        // auto frameStart = std::chrono::high_resolution_clock::now();

        mModel->updateModel();

        mCollisionHandler.handleCollisions();

        mView->handleEvents(quit);

        if (input.GetKeyDown(Key::Key_W)) {
            std::cout << "W pressed once" << std::endl;
        }

        if (input.GetKey(Key::Key_Space)) {
            std::cout << "Space is held" << std::endl;
        }

        mView->render();

        // auto frameTime = std::chrono::high_resolution_clock::now() - frameStart;
        // int frameDuration = std::chrono::duration_cast<std::chrono::milliseconds>(frameTime).count();
        //
        // if (frameDelay > frameDuration) {
        //     std::this_thread::sleep_for(std::chrono::milliseconds(frameDelay - frameDuration));
        // }
    }
}
