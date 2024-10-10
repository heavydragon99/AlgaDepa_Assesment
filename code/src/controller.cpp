#include "controller.h"
#include "view.h"

#include <chrono>
#include <iostream>
#include <thread>

Controller::Controller(std::vector<ParsedPerson> aPersons, ParsedGrid aGrid) {
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
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    // Render the data with the view class

    bool quit = false;

    while (!quit) {
        auto frameStart = std::chrono::high_resolution_clock::now();

        mModel->updateModel();

        mView->handleEvents(quit);
        mView->render();

        auto frameTime = std::chrono::high_resolution_clock::now() - frameStart;
        int frameDuration = std::chrono::duration_cast<std::chrono::milliseconds>(frameTime).count();

        if (frameDelay > frameDuration) {
            std::this_thread::sleep_for(std::chrono::milliseconds(frameDelay - frameDuration));
        }
    }
}
