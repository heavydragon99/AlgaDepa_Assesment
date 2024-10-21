#ifndef POLLING_TUI
#define POLLING_TUI

#include <chrono>
#include <iostream>
#include <sys/ioctl.h>
#include <termios.h>
#include <thread>
#include <unistd.h>

#include "SDL.h"

#include "Command.h"
#include "FileHandler.h"
#include "InputStructs.h"
#include "model.h"
#include "structs.h"

enum MenuState { MainMenu = 0, ChooseShortcutToChange, SetKeyForShortcut, OpenArtistFile, OpenGridFile };

class PollingTUI {
public:
    PollingTUI(InputHandler& aInputHandler, Model& aModel);
    ~PollingTUI();

    // Starts the polling loop
    void update();

private:
    MenuState mMenuState = MenuState::MainMenu;
    Model& mModel;
    InputHandler& mInputHandler;
    int mChosenShortcut = 0;

    void mainMenu();

    void chooseShortcutToChange();

    void openArtistFile();

    void openGridFile();

    void setKeyForShortcut();

    // Disable input buffering for non-blocking input
    void setNonBlockingInput();

    // Reset terminal settings after exit
    void resetInput();

    // Check if a key has been pressed (non-blocking)
    bool kbhit();

    // ANSI escape codes to clear the terminal and move the cursor
    void clearScreen();

    void moveCursor(int x, int y);
};

#endif
