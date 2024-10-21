#ifndef COMMAND_H
#define COMMAND_H

#include "configuration.h"

#include <iostream>
#include <map>
#include <memory>

class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
    virtual std::string getName() = 0;

    Command() {}

    /// Assume Command has a copy constructor
    Command(const Command& other) {}

    // Clone method to return a copy of this command
    virtual Command* clone() const = 0;
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
    }
};

class ToggleRenderArtistsCommand : public Command {
public:
    void execute() override {
        Configuration::getInstance().setConfig("RenderArtists",
                                               !Configuration::getInstance().getConfig("RenderArtists"));
    }
    std::string getName() override { return "Toggle Render Artists Command"; }

    ToggleRenderArtistsCommand* clone() const override {
        return new ToggleRenderArtistsCommand(*this); // Creates a new instance using the copy constructor
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
    }
};

class PlayPauseTilesCommand : public Command {
public:
    void execute() override {
        Configuration::getInstance().setConfig("PauseTiles", !Configuration::getInstance().getConfig("PauseTiles"));
    }
    std::string getName() override { return "Play Pause Command"; }

    PlayPauseTilesCommand* clone() const override {
        return new PlayPauseTilesCommand(*this); // Creates a new instance using the copy constructor
    }
};

class ToggleRenderQuadtreeCommand : public Command {
public:
    void execute() override {
        Configuration::getInstance().setConfig("RenderQuadtree",
                                               !Configuration::getInstance().getConfig("RenderQuadtree"));
    }
    std::string getName() override { return "Toggle Render Quadtree Command"; }

    ToggleRenderQuadtreeCommand* clone() const override {
        return new ToggleRenderQuadtreeCommand(*this); // Creates a new instance using the copy constructor
    }
};

class ToggleRenderPathCommand : public Command {
public:
    void execute() override {
        Configuration::getInstance().setConfig("RenderPath", !Configuration::getInstance().getConfig("RenderPath"));
    }
    std::string getName() override { return "Toggle Render Path Command"; }

    ToggleRenderPathCommand* clone() const override {
        return new ToggleRenderPathCommand(*this); // Creates a new instance using the copy constructor
    }
};

class ToggleRenderVisitedCommand : public Command {
public:
    void execute() override {
        Configuration::getInstance().setConfig("RenderVisited",
                                               !Configuration::getInstance().getConfig("RenderVisited"));
    }
    std::string getName() override { return "Toggle Render Visited Command"; }

    ToggleRenderVisitedCommand* clone() const override {
        return new ToggleRenderVisitedCommand(*this); // Creates a new instance using the copy constructor
    }
};

class ChangeCollisionMethodCommand : public Command {
public:
    void execute() override {
        Configuration::getInstance().setConfig("CollisionMethodQuadTree",
                                               !Configuration::getInstance().getConfig("CollisionMethodQuadTree"));
        std::cout << "Change collision method" << std::endl;
    }
    std::string getName() override { return "Change Collision Method Command"; }

    ChangeCollisionMethodCommand* clone() const override {
        return new ChangeCollisionMethodCommand(*this); // Creates a new instance using the copy constructor
    }
};

class ToggleCollisionWithPathCommand : public Command {
public:
    void execute() override {
        Configuration::getInstance().setConfig("CollisionWithPath",
                                               !Configuration::getInstance().getConfig("CollisionWithPath"));
    }
    std::string getName() override { return "Toggle Collision With Path Command"; }

    ToggleCollisionWithPathCommand* clone() const override {
        return new ToggleCollisionWithPathCommand(*this); // Creates a new instance using the copy constructor
    }
};

class ChangePathfindingMethodCommand : public Command {
public:
    void execute() override {
        Configuration::getInstance().setConfig("PathfindingMethodDijkstra",
                                               !Configuration::getInstance().getConfig("PathfindingMethodDijkstra"));
    }
    std::string getName() override { return "Change Pathfinding Method Command"; }

    ChangePathfindingMethodCommand* clone() const override {
        return new ChangePathfindingMethodCommand(*this); // Creates a new instance using the copy constructor
    }
};

class PlayPauseArtistsCommand : public Command {
public:
    void execute() override {
        Configuration::getInstance().setConfig("pauseArtists", !Configuration::getInstance().getConfig("pauseArtists"));
    }
    std::string getName() override { return "Play Pause Artists Command"; }

    PlayPauseArtistsCommand* clone() const override {
        return new PlayPauseArtistsCommand(*this); // Creates a new instance using the copy constructor
    }
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

#endif // COMMAND_H
