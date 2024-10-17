#pragma once

#include <chrono>
#include <iostream>
#include <sys/ioctl.h>
#include <termios.h>
#include <thread>
#include <unistd.h>

enum MenuState { MainMenu = 0, ChooseShortcutToChange, SetKeyForShortcut };

class PollingTUI {
public:
    PollingTUI() {
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
        moveCursor(2, 2);
        std::cout << "Enter the number correlating to the action" << std::endl;

        moveCursor(2, 4);
        std::cout << "(1) beweging artists play/pause, currently mapped to: Space" << std::endl;

        moveCursor(2, 6);
        std::cout << "(2) herschik het vakje waar de muispointer zich bevindt, currently mapped to: Enter" << std::endl;

        moveCursor(2, 8);
        std::cout << "(3) bestand openen, currently mapped to: o" << std::endl;

        moveCursor(2, 10);
        std::cout << "(4) render artists, currently mapped to: a" << std::endl;

        moveCursor(2, 12);
        std::cout << "(5) terug in de tijd gaan  x-ticks (bepaal x zelf), currently mapped to: Key_Left" << std::endl;

        moveCursor(2, 14);
        std::cout << "(6) vooruit in de tijd gaan x-ticks (bepaal x zelf), currently mapped to: Key_Right" << std::endl;

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
            }
        }
    }

    void setKeyForShortcut() {
        static std::string newKeyBind = "";

        moveCursor(2, 2);
        std::cout << "Press new key to change shortcut" << std::endl;

        char ch;

        while (kbhit() > 0) {
            ch = getchar();

            if (ch == '\n') {
                std::cout << "newKeyBind: " << newKeyBind << std::endl;
                newKeyBind = "";

            } else if (ch == '\b' || ch == 127) {
                // else if (ch == '\b') {
                // std::cout << "JAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << std::endl;
                if (newKeyBind.size() > 0)
                    newKeyBind.resize(newKeyBind.size() - 1);
            }

            else {
                newKeyBind += ch;
            }
        }
        std::cout << newKeyBind << std::endl;
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
