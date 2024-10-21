#include "PollingTUI.h"

PollingTUI::PollingTUI(InputHandler& aInputHandler, Model& aModel) : mInputHandler(aInputHandler), mModel(aModel) {
    // Initialize terminal settings
    setNonBlockingInput();
}

PollingTUI::~PollingTUI() {
    // Reset terminal settings before exiting
    resetInput();
}

// Starts the polling loop
void PollingTUI::update() {
    clearScreen(); // Clear the terminal

    switch (mMenuState) {
    case MenuState::MainMenu:
        mainMenu();
        break;
    case MenuState::ChooseShortcutToChange:
        chooseShortcutToChange();
        break;
    case MenuState::SetKeyForShortcut:
        setKeyForShortcut();
        break;
    case MenuState::OpenArtistFile:
        openArtistFile();
        break;
    case MenuState::OpenGridFile:
        openGridFile();
        break;
    default:
        break;
    }
}

void PollingTUI::mainMenu() {
    // Display the polled data
    int curline = 2;
    moveCursor(2, curline += 2);
    std::cout << "Welcome to the best simulation program ever" << std::endl;

    moveCursor(2, curline += 2);
    std::cout << "(1) change key bindings" << std::endl;

    moveCursor(2, curline += 2);
    std::cout << "(2) load artist file" << std::endl;

    moveCursor(2, curline += 2);
    std::cout << "(3) load grid file" << std::endl;

    moveCursor(2, curline += 2);
    std::cout << "Current amount of artists: " << mModel.getLevelData().getPeople().size() << std::endl;

    if (mModel.getPathFinder().getGCost() != 0) {
        moveCursor(2, curline += 2);
        std::cout << "GCost of current path: " << mModel.getPathFinder().getGCost() << std::endl;
    }
    if (mModel.getPathFinder().getSteps() != 0) {
        moveCursor(2, curline += 2);
        std::cout << "Amount of steps in current path: " << mModel.getPathFinder().getSteps() << std::endl;
    }
    moveCursor(2, curline += 2);
    std::cout << "Press 'q' to quit" << std::endl;

    char ch;
    // Check for user input without blocking
    while (kbhit() > 0) {
        ch = getchar();
        if (ch == '1') {
            mMenuState = MenuState::ChooseShortcutToChange;
        }
        if (ch == '2') {
            mMenuState = MenuState::OpenArtistFile;
        }
        if (ch == '3') {
            mMenuState = MenuState::OpenGridFile;
        }
        if (ch == 'q') {
            exit(0);
        }
    }
}

void PollingTUI::chooseShortcutToChange() {
    // Display the polled data
    int curLine = 2;
    moveCursor(2, curLine += 2);
    std::cout << "Enter the number correlating to the action" << std::endl;

    int commandID = 0;

    for (const auto& [key, command] : mInputHandler.getRegistrations()) {
        moveCursor(2, curLine += 2);
        std::cout << "(" << (commandID += 1) << ") " << command->getName() << " is binded to: " << keyToString((Key)key)
                  << std::endl;
    }
    char ch;

    while (kbhit() > 0) {
        ch = getchar();
        if (ch >= '1' && ch <= '6') {
            int chosenShortcut = ch - '1' + 1;
            std::cout << "selected Option: " << chosenShortcut << std::endl;
            mMenuState = MenuState::SetKeyForShortcut;
            mChosenShortcut = chosenShortcut;
        }
    }
}

void PollingTUI::openArtistFile() {
    static std::string fileName = "";

    moveCursor(2, 0);
    std::cout << "Enter file name to be loaded:" << std::endl;

    char ch;

    while (kbhit() > 0) {
        ch = getchar();

        if (ch == '\n') {
            FileHandler fileHandler;

            std::vector<ParsedPerson> persons = fileHandler.loadArtist(fileName);

            mModel.setPersonData(persons);

            mMenuState = MenuState::MainMenu;
            fileName = "";

        } else if (ch == '\b' || ch == 127) {
            if (fileName.size() > 0)
                fileName.resize(fileName.size() - 1);
        } else {
            fileName += ch;
        }
    }
    moveCursor(2, 3);
    std::cout << fileName << std::endl;
    moveCursor(2 + fileName.size(), 3);
    std::cout.flush();
}

void PollingTUI::openGridFile() {
    static std::string fileName = "";

    moveCursor(2, 0);
    std::cout << "Enter file name to be loaded:" << std::endl;

    char ch;

    while (kbhit() > 0) {
        ch = getchar();

        if (ch == '\n') {
            FileHandler fileHandler;

            ParsedGrid grid = fileHandler.loadGrid(fileName);

            mModel.setGridData(grid);

            mMenuState = MenuState::MainMenu;
            fileName = "";

        } else if (ch == '\b' || ch == 127) {
            if (fileName.size() > 0)
                fileName.resize(fileName.size() - 1);
        } else {
            fileName += ch;
        }
    }
    moveCursor(2, 3);
    std::cout << fileName << std::endl;
    moveCursor(2 + fileName.size(), 3);
    std::cout.flush();
}

void PollingTUI::setKeyForShortcut() {
    static std::string newKeyBind = "";

    moveCursor(2, 0);
    std::cout << "Press new key to change shortcut" << std::endl;

    char ch;

    while (kbhit() > 0) {
        ch = getchar();

        if (ch == '\n') {
            std::cout << "newKeyBind: " << newKeyBind << std::endl;

            int commandID = 0;
            for (const auto& [key, command] : mInputHandler.getRegistrations()) {
                commandID += 1;
                if (commandID == mChosenShortcut) {
                    Command* commandCopy = command->clone();

                    mInputHandler.removeCommand(key);

                    mInputHandler.setCommand(stringToKeyID(newKeyBind), std::unique_ptr<Command>(commandCopy));
                    mInputHandler.printCommands();
                    SDL_Delay(10000);
                }
            }

            mMenuState = MenuState::MainMenu;
            newKeyBind = "";
            mChosenShortcut = 0;

        } else if (ch == '\b' || ch == 127) {
            if (newKeyBind.size() > 0)
                newKeyBind.resize(newKeyBind.size() - 1);
        } else {
            newKeyBind += ch;
        }
    }
    moveCursor(2, 5);
    std::cout << newKeyBind << std::endl;
    moveCursor(2 + newKeyBind.size(), 5);
    std::cout.flush();
}

// Disable input buffering for non-blocking input
void PollingTUI::setNonBlockingInput() {
    termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ICANON; // Disable canonical mode
    term.c_lflag &= ~ECHO;   // Disable echo
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// Reset terminal settings after exit
void PollingTUI::resetInput() {
    termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ICANON;
    term.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// Check if a key has been pressed (non-blocking)
bool PollingTUI::kbhit() {
    int bytesWaiting;
    ioctl(STDIN_FILENO, FIONREAD, &bytesWaiting);
    return bytesWaiting > 0;
}

// ANSI escape codes to clear the terminal and move the cursor
void PollingTUI::clearScreen() { std::cout << "\033[2J\033[1;1H"; }

void PollingTUI::moveCursor(int x, int y) { std::cout << "\033[" << y << ";" << x << "H"; }