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

    // Simulate input events
    // inputHandler.handleInput(KEY_UP);   // Output: Character moves up.
    // inputHandler.handleInput(KEY_DOWN); // Output: Character moves down.
    // inputHandler.handleInput(KEY_JUMP); // Output: Character jumps.

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    // Render the data with the view class

    this->mCollisionHandler = CollisionHandler(mModel.get());

    bool quit = false;

    while (!quit) {
        auto frameStart = std::chrono::high_resolution_clock::now();

        tui.update();

        this->checkInputs();

        if (!pause)
            mModel->updateModel();

        mCollisionHandler.handleCollisions();

        mView->handleEvents(quit);

        // if (input.GetKeyDown(Key::Key_W)) {
        //     std::cout << "W pressed once" << std::endl;
        // }
        //
        // if (input.GetKey(Key::Key_Space)) {
        //     std::cout << "Space is held" << std::endl;
        // }

        mView->render();

        auto frameTime = std::chrono::high_resolution_clock::now() - frameStart;
        int frameDuration = std::chrono::duration_cast<std::chrono::milliseconds>(frameTime).count();

        if (frameDelay > frameDuration) {
            std::this_thread::sleep_for(std::chrono::milliseconds(frameDelay - frameDuration));
        }
    }
}
