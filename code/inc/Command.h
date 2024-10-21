#ifndef COMMAND_H
#define COMMAND_H

#include "configuration.h"

#include <iostream>
#include <map>
#include <memory>
#include <functional>

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
    RearrangeTileCommand(std::function<void()> aAction) : mAction(aAction) {}

    RearrangeTileCommand(const RearrangeTileCommand& other) : mAction(other.mAction) {}

    void execute() override {
        std::cout << "Executing Rearrange Tile Command" << std::endl;
        if (mAction) {
            mAction();
        }
    }

    std::string getName() override { return "Rearrange Tile Command"; }

    RearrangeTileCommand* clone() const override {
        return new RearrangeTileCommand(*this); // Creates a new instance using the copy constructor
    }

private:
    std::function<void()> mAction;
};

class FileOpenCommand : public Command {
public:
    void execute() override {
        std::cout << "Executing File Open Command" << std::endl;
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
        bool newValue = !Configuration::getInstance().getConfig("RenderArtists");
        Configuration::getInstance().setConfig("RenderArtists", newValue);
        std::cout << "Executing Toggle Render Artists Command, new RenderArtists value: " << newValue << std::endl;
    }
    std::string getName() override { return "Toggle Render Artists Command"; }

    ToggleRenderArtistsCommand* clone() const override {
        return new ToggleRenderArtistsCommand(*this); // Creates a new instance using the copy constructor
    }
};

class BackwardInTimeCommand : public Command {
public:
    BackwardInTimeCommand(std::function<void()> aAction) : mAction(aAction) {}

    BackwardInTimeCommand(const BackwardInTimeCommand& other) : mAction(other.mAction) {}

    void execute() override {
        std::cout << "Executing Backward In Time Command" << std::endl;
        if (mAction) {
            mAction();
        }
    }

    std::string getName() override { return "Backward In Time Command"; }

    BackwardInTimeCommand* clone() const override {
        return new BackwardInTimeCommand(*this); // Creates a new instance using the copy constructor
    }

private:
    std::function<void()> mAction;
};

class ForwardInTimeCommand : public Command {
public:
    ForwardInTimeCommand(std::function<void()> aAction) : mAction(aAction) {}

    ForwardInTimeCommand(const ForwardInTimeCommand& other) : mAction(other.mAction) {}

    void execute() override {
        std::cout << "Executing Forward In Time Command" << std::endl;
        if (mAction) {
            mAction();
        }
    }

    std::string getName() override { return "Forward In Time Command"; }

    ForwardInTimeCommand* clone() const override {
        return new ForwardInTimeCommand(*this); // Creates a new instance using the copy constructor
    }

private:
    std::function<void()> mAction;
};

class PlayPauseTilesCommand : public Command {
public:
    void execute() override {
        bool newValue = !Configuration::getInstance().getConfig("PauseTiles");
        Configuration::getInstance().setConfig("PauseTiles", newValue);
        std::cout << "Executing Play Pause Tiles Command, new PauseTiles value: " << newValue << std::endl;
    }
    std::string getName() override { return "Play Pause Command"; }

    PlayPauseTilesCommand* clone() const override {
        return new PlayPauseTilesCommand(*this); // Creates a new instance using the copy constructor
    }
};

class ToggleRenderQuadtreeCommand : public Command {
public:
    void execute() override {
        bool newValue = !Configuration::getInstance().getConfig("RenderQuadtree");
        Configuration::getInstance().setConfig("RenderQuadtree", newValue);
        std::cout << "Executing Toggle Render Quadtree Command, new RenderQuadtree value: " << newValue << std::endl;
    }
    std::string getName() override { return "Toggle Render Quadtree Command"; }

    ToggleRenderQuadtreeCommand* clone() const override {
        return new ToggleRenderQuadtreeCommand(*this); // Creates a new instance using the copy constructor
    }
};

class ToggleRenderPathCommand : public Command {
public:
    void execute() override {
        bool newValue = !Configuration::getInstance().getConfig("RenderPath");
        Configuration::getInstance().setConfig("RenderPath", newValue);
        std::cout << "Executing Toggle Render Path Command, new RenderPath value: " << newValue << std::endl;
    }
    std::string getName() override { return "Toggle Render Path Command"; }

    ToggleRenderPathCommand* clone() const override {
        return new ToggleRenderPathCommand(*this); // Creates a new instance using the copy constructor
    }
};

class ToggleRenderVisitedCommand : public Command {
public:
    void execute() override {
        bool newValue = !Configuration::getInstance().getConfig("RenderVisited");
        Configuration::getInstance().setConfig("RenderVisited", newValue);
        std::cout << "Executing Toggle Render Visited Command, new RenderVisited value: " << newValue << std::endl;
    }
    std::string getName() override { return "Toggle Render Visited Command"; }

    ToggleRenderVisitedCommand* clone() const override {
        return new ToggleRenderVisitedCommand(*this); // Creates a new instance using the copy constructor
    }
};

class ChangeCollisionMethodCommand : public Command {
public:
    void execute() override {
        bool newValue = !Configuration::getInstance().getConfig("CollisionMethodQuadTree");
        Configuration::getInstance().setConfig("CollisionMethodQuadTree", newValue);
        std::cout << "Executing Change Collision Method Command, new CollisionMethodQuadTree value: " << newValue << std::endl;
    }
    std::string getName() override { return "Change Collision Method Command"; }

    ChangeCollisionMethodCommand* clone() const override {
        return new ChangeCollisionMethodCommand(*this); // Creates a new instance using the copy constructor
    }
};

class ToggleCollisionWithPathCommand : public Command {
public:
    void execute() override {
        bool newValue = !Configuration::getInstance().getConfig("CollisionWithPath");
        Configuration::getInstance().setConfig("CollisionWithPath", newValue);
        std::cout << "Executing Toggle Collision With Path Command, new CollisionWithPath value: " << newValue << std::endl;
    }
    std::string getName() override { return "Toggle Collision With Path Command"; }

    ToggleCollisionWithPathCommand* clone() const override {
        return new ToggleCollisionWithPathCommand(*this); // Creates a new instance using the copy constructor
    }
};

class ChangePathfindingMethodCommand : public Command {
public:
    void execute() override {
        bool newValue = !Configuration::getInstance().getConfig("PathfindingMethodDijkstra");
        Configuration::getInstance().setConfig("PathfindingMethodDijkstra", newValue);
        std::cout << "Executing Change Pathfinding Method Command, new PathfindingMethodDijkstra value: " << newValue << std::endl;
    }
    std::string getName() override { return "Change Pathfinding Method Command"; }

    ChangePathfindingMethodCommand* clone() const override {
        return new ChangePathfindingMethodCommand(*this); // Creates a new instance using the copy constructor
    }
};

class PlayPauseArtistsCommand : public Command {
public:
    void execute() override {
        bool newValue = !Configuration::getInstance().getConfig("PauseArtists");
        Configuration::getInstance().setConfig("PauseArtists", newValue);
        std::cout << "Executing Play Pause Artists Command, new pauseArtists value: " << newValue << std::endl;
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