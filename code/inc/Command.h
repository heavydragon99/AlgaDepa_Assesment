#pragma once

#include <iostream>
#include <map>
#include <memory>

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

class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0; // Pure virtual function to execute the command
    virtual std::string getName() = 0;

    Command() {}

    /// Assume Command has a copy constructor
    Command(const Command& other) {
        // Copy constructor logic (copy the necessary data)
    }

    // Clone method to return a copy of this command
    virtual Command* clone() const = 0;
    // return new Command(*this); // Creates a new instance using the copy constructor
    // // return nullptr;
    // }
};

class RearrangeTileCommand : public Command {
public:
    void execute() override {
        // action
        std::cout << "Rearrage Tile Command" << std::endl;
    }
    std::string getName() override { return "Rearrage Tile Command"; }

    RearrangeTileCommand* clone() const override {
        return new RearrangeTileCommand(*this); // Creates a new instance using the copy constructor
        // return nullptr;
    }
};

class FileOpenCommand : public Command {
public:
    void execute() override {
        // Action for moving down
        std::cout << "File Open Command" << std::endl;
    }
    std::string getName() override { return "File Open Command"; }

    FileOpenCommand* clone() const override {
        return new FileOpenCommand(*this); // Creates a new instance using the copy constructor
        // return nullptr;
    }
};

class ToggleRenderArtistsCommand : public Command {
public:
    void execute() override {
        // Action for moving down
        std::cout << "Toggle Render Artists Command" << std::endl;
    }
    std::string getName() override { return "Toggle Render Artists Command"; }

    ToggleRenderArtistsCommand* clone() const override {
        return new ToggleRenderArtistsCommand(*this); // Creates a new instance using the copy constructor
        // return nullptr;
    }
};

class BackwardInTimeCommand : public Command {
public:
    void execute() override {
        // Action for moving down
        std::cout << "Backward In Time Command" << std::endl;
    }
    std::string getName() override { return "Backward In Time Command"; }

    BackwardInTimeCommand* clone() const override {
        return new BackwardInTimeCommand(*this); // Creates a new instance using the copy constructor
        // return nullptr;
    }
};

class ForwardInTimeCommand : public Command {
public:
    void execute() override {
        // Action for moving down
        std::cout << "Forward In Time Command" << std::endl;
    }
    std::string getName() override { return "Forward In Time Command"; }

    ForwardInTimeCommand* clone() const override {
        return new ForwardInTimeCommand(*this); // Creates a new instance using the copy constructor
        // return nullptr;
    }
};

class PlayPauseCommand : public Command {
public:
    // PlayPauseCommand() {}
    PlayPauseCommand(bool& aPauseState) : mPauseState(aPauseState) {}
    /// Assume Command has a copy constructor
    PlayPauseCommand(const PlayPauseCommand& other) : mPauseState(other.mPauseState) {
        // Copy constructor logic (copy the necessary data)
        // this->mPauseState = other.mPauseState;
    }

    void execute() override { mPauseState = !mPauseState; }
    std::string getName() override { return "Play Pause Command"; }

    PlayPauseCommand* clone() const override {
        return new PlayPauseCommand(*this); // Creates a new instance using the copy constructor
        // return nullptr;
    }

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

    // Print all commands currently in the map
    void printCommands() const {
        for (const auto& pair : commandMap) {
            // Print key and command name
            std::cout << "Key: " << pair.first << " -> Command: " << pair.second->getName() << std::endl;
        }
    }

    std::map<int, std::unique_ptr<Command>>& getRegistrations() { return commandMap; }
};
