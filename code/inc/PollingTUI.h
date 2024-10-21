#pragma once

#include <chrono>
#include <iostream>
#include <sys/ioctl.h>
#include <termios.h>
#include <thread>
#include <unistd.h>

#include "SDL.h"

#include "Command.h"
#include "InputStructs.h"

enum MenuState { MainMenu = 0, ChooseShortcutToChange, SetKeyForShortcut };

class PollingTUI {
public:
    PollingTUI(InputHandler& aInputHandler) : mInputHandler(aInputHandler) {
        // Initialize terminal settings
        setNonBlockingInput();
    }

    ~PollingTUI() {
        // Reset terminal settings before exiting
        resetInput();
    }

    // Starts the polling loop
    void update() {
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
        default:
            break;
        }
    }

private:
    MenuState mMenuState = MenuState::MainMenu;
    InputHandler& mInputHandler;
    int mChosenShortcut = 0;

    void mainMenu() {
        // Display the polled data
        moveCursor(2, 2);
        std::cout << "Welcome to the best simulation program ever" << std::endl;

        moveCursor(2, 4);
        std::cout << "(1) change key bindings" << std::endl;

        moveCursor(2, 6);
        std::cout << "Press 'q' to quit" << std::endl;

        char ch;
        // Check for user input without blocking
        while (kbhit() > 0) {
            ch = getchar();
            if (ch == '1') {
                mMenuState = MenuState::ChooseShortcutToChange;
            }
        }
    }

    void chooseShortcutToChange() {
        // Display the polled data
        int curLine = 2;
        moveCursor(2, curLine += 2);
        std::cout << "Enter the number correlating to the action" << std::endl;

        int commandID = 0;

        for (const auto& [key, command] : mInputHandler.getRegistrations()) {
            moveCursor(2, curLine += 2);
            std::cout << "(" << (commandID += 1) << ") " << command->getName()
                      << " is binded to: " << keyToString((Key)key) << std::endl;
        }
        /*
         *
         *   Spatie: beweging artists    play/pause
             Enter: herschik het vakje waar de muispointer zich bevindt
                (Zie herschikken hierboven)
             o:       bestand openen
             a:       render artists       aan/uit
             left arrow:   terug in de tijd gaan  x-ticks (bepaal x zelf)
             right arrow:  vooruit in de tijd gaan  x-ticks (bepaal x zelf)
         *
         */
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

    void setKeyForShortcut() {
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
    void setNonBlockingInput() {
        termios term;
        tcgetattr(STDIN_FILENO, &term);
        term.c_lflag &= ~ICANON; // Disable canonical mode
        term.c_lflag &= ~ECHO;   // Disable echo
        tcsetattr(STDIN_FILENO, TCSANOW, &term);
    }

    // Reset terminal settings after exit
    void resetInput() {
        termios term;
        tcgetattr(STDIN_FILENO, &term);
        term.c_lflag |= ICANON;
        term.c_lflag |= ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &term);
    }

    // Check if a key has been pressed (non-blocking)
    bool kbhit() {
        int bytesWaiting;
        ioctl(STDIN_FILENO, FIONREAD, &bytesWaiting);
        return bytesWaiting > 0;
    }

    // // Simulate external data polling
    // int pollExternalData() {
    //     static int data = 0;
    //     return ++data;
    // }

    // ANSI escape codes to clear the terminal and move the cursor
    void clearScreen() { std::cout << "\033[2J\033[1;1H"; }

    void moveCursor(int x, int y) { std::cout << "\033[" << y << ";" << x << "H"; }
};
