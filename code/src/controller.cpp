#include "controller.h"
#include "view.h"

#include <chrono>
#include <iostream>
#include <thread>

controller::controller(std::vector<ParsedPerson> aPersons, ParsedGrid aGrid) {
    mPersons = aPersons;
    mGrid = aGrid;
}

void controller::createLevel() { mModel.createLevel(mPersons, mGrid); }

void controller::run() {
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    // Render the data with the view class
    view vw(mModel);

    bool quit = false;

    while (!quit) {
        auto frameStart = std::chrono::high_resolution_clock::now();

        mModel.updateModel();

        vw.handleEvents(quit);
        vw.render();

        auto frameTime = std::chrono::high_resolution_clock::now() - frameStart;
        int frameDuration = std::chrono::duration_cast<std::chrono::milliseconds>(frameTime).count();

        if (frameDelay > frameDuration) {
            std::this_thread::sleep_for(std::chrono::milliseconds(frameDelay - frameDuration));
        }
    }
}
