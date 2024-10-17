#pragma once

#include <iostream>
#include <map>
#include <memory>

class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0; // Pure virtual function to execute the command
};

class MoveUpCommand : public Command {
public:
    void execute() override {
        // Action for moving up
        std::cout << "Character moves up." << std::endl;
    }
};

class MoveDownCommand : public Command {
public:
    void execute() override {
        // Action for moving down
        std::cout << "Character moves down." << std::endl;
    }
};

class PlayPauseCommand : public Command {
public:
    PlayPauseCommand(bool& aPauseState) : mPauseState(aPauseState) {}

    void execute() override { mPauseState = !mPauseState; }

private:
    bool& mPauseState; // The receiver
};

class InputHandler {
private:
    std::map<int, std::unique_ptr<Command>> commandMap; // Maps input codes to commands

public:
    void setCommand(int input, std::unique_ptr<Command> command) { commandMap[input] = std::move(command); }

    void handleInput(int input) {
        if (commandMap.find(input) != commandMap.end()) {
            commandMap[input]->execute();
        } else {
            std::cout << "No command assigned to this input." << std::endl;
        }
    }

    // Remove a command associated with an input
    void removeCommand(int input) {
        auto it = commandMap.find(input);
        if (it != commandMap.end()) {
            commandMap.erase(it);
            std::cout << "Command for input " << input << " removed." << std::endl;
        } else {
            std::cout << "No command found for input " << input << " to remove." << std::endl;
        }
    }
};
