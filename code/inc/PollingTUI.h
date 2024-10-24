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
#include "Model.h"
#include "Structs.h"

/**
 * @enum MenuState
 * @brief Represents the different states of the menu.
 */
enum MenuState { MainMenu = 0, ChooseShortcutToChange, SetKeyForShortcut, OpenArtistFile, OpenGridFile };

/**
 * @class PollingTUI
 * @brief A class that handles the text-based user interface for polling input.
 */
class PollingTUI {
public:
    PollingTUI(InputHandler& aInputHandler, Model& aModel);
    ~PollingTUI();

    int update();

private:
    MenuState mMenuState = MenuState::MainMenu; ///< Current state of the menu.
    Model& mModel; ///< Reference to the model.
    InputHandler& mInputHandler; ///< Reference to the input handler.
    int mChosenShortcut = 0; ///< Currently chosen shortcut.

    int mainMenu();

    void chooseShortcutToChange();

    void openArtistFile();

    void openGridFile();

    void setKeyForShortcut();

    void setNonBlockingInput();

    void resetInput();

    bool kbhit();

    void clearScreen();

    void moveCursor(int x, int y);
};

#endif