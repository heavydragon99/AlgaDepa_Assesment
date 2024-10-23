#include "Model.h"
#include "Configuration.h"

#include <iostream>
#include <stdexcept>

/**
 * @brief Constructs a new Model object.
 */
Model::Model()
    : mLevel(std::make_unique<LevelData>()), mMementoManager(std::make_unique<MementoManager>()),
      mPathFinder(std::make_unique<PathFinder>()),
      mLastUpdateTime(std::chrono::steady_clock::now() - MEMENTO_UPDATE_INTERVAL) {}

/**
 * @brief Creates a new level with the given persons and grid data.
 * @param aPersons Vector of parsed persons.
 * @param aGrid Parsed grid data.
 */
void Model::createLevel(std::vector<ParsedPerson> aPersons, ParsedGrid aGrid) {
    mLevel->buildGridData(aGrid);
    mLevel->buildPersonData(aPersons);
}

/**
 * @brief Sets the person data.
 * @param aPersons Vector of parsed persons.
 */
void Model::setPersonData(std::vector<ParsedPerson> aPersons) { mLevel->buildPersonData(aPersons); }

/**
 * @brief Sets the grid data.
 * @param aGrid Parsed grid data.
 */
void Model::setGridData(ParsedGrid aGrid) { mLevel->buildGridData(aGrid); }

/**
 * @brief Gets the level data.
 * @return Reference to the level data.
 */
LevelData& Model::getLevelData() { return *mLevel; }

/**
 * @brief Updates the model.
 */
void Model::updateModel() {
    if (!Configuration::getInstance().getConfig("PauseArtists")) {
        auto now = std::chrono::steady_clock::now();
        if (now - mLastUpdateTime >= MEMENTO_UPDATE_INTERVAL) {
            mMementoManager->addMemento(saveToMemento());
            mLastUpdateTime = now;
        }
        mLevel->updateLevelData();
    }
}

/**
 * @brief Updates a specific tile.
 * @param aX X coordinate of the tile.
 * @param aY Y coordinate of the tile.
 */
void Model::updateTile(int aX, int aY) { mLevel->updateTile(aX, aY); }

/**
 * @brief Saves the current state to a memento.
 * @return The created memento.
 */
Memento Model::saveToMemento() const { return Memento(*mLevel.get()); }

/**
 * @brief Restores the state from a memento.
 * @param memento The memento to restore from.
 */
void Model::restoreFromMemento(Memento&& memento) {
    mLevel->buildGridData(memento.getGrid());
    mLevel->buildPersonData(memento.getPeople());
}

/**
 * @brief Uses the previous memento.
 */
void Model::usePreviousMemento() {
    try {
        restoreFromMemento(mMementoManager->getPreviousMemento());
    } catch (const std::exception& e) {
        std::cerr << "Error using previous memento: " << e.what() << std::endl;
    }
}

/**
 * @brief Uses the next memento.
 */
void Model::useNextMemento() {
    try {
        restoreFromMemento(mMementoManager->getNextMemento());
    } catch (const std::exception& e) {
        std::cerr << "Error using next memento: " << e.what() << std::endl;
    }
}

/**
 * @brief Finds a path between two points.
 * @param aStart Starting point.
 * @param aEnd Ending point.
 */
void Model::findPath(const std::pair<int, int>& aStart, const std::pair<int, int>& aEnd) {
    mPathFinder->findPath(mLevel.get(), aStart, aEnd);
}

/**
 * @brief Gets the pathfinder.
 * @return Reference to the pathfinder.
 */
PathFinder& Model::getPathFinder() { return *mPathFinder; }