#include "controller.h"
#include "view.h"

#include <chrono>
#include <iostream>
#include <thread>

controller::controller(std::vector<ParsedPerson> aPersons, ParsedGrid aGrid) {
    mPersons = aPersons;
    mGrid = aGrid;
}

void controller::createLevel() {
    mModel = std::make_unique<model>();
    mModel->createLevel(mPersons, mGrid);
    mView = std::make_unique<view>(*mModel);
    mView->setGridColor(mGrid.gridColors);
}

void controller::run() {
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
