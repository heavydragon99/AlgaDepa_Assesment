#include "ITileState.h"
#include "Tile.h"
#include "TileFactory.h"

// TileStateYellow Implementation

/**
 * @brief Constructs a new TileStateYellow object.
 * 
 * @param aBehavior A unique pointer to an ITileBehavior object.
 */
TileStateYellow::TileStateYellow(std::unique_ptr<ITileBehavior> aBehavior)
    : mBehavior(std::move(aBehavior)), mCounter(0) {}

/**
 * @brief Copy constructor for TileStateYellow.
 * 
 * @param other The TileStateYellow object to copy from.
 */
TileStateYellow::TileStateYellow(const TileStateYellow& other)
    : mBehavior(other.mBehavior->clone()), mCounter(other.mCounter) {}

/**
 * @brief Assignment operator for TileStateYellow.
 * 
 * @param other The TileStateYellow object to assign from.
 * @return TileStateYellow& A reference to the assigned object.
 */
TileStateYellow& TileStateYellow::operator=(const TileStateYellow& other) {
    if (this != &other) {
        mBehavior = other.mBehavior->clone();
        mCounter = other.mCounter;
    }
    return *this;
}

/**
 * @brief Clones the current TileStateYellow object.
 * 
 * @return std::unique_ptr<ITileState> A unique pointer to the cloned object.
 */
std::unique_ptr<ITileState> TileStateYellow::clone() const {
    return std::make_unique<TileStateYellow>(*this);
}

/**
 * @brief Updates the tile with the current behavior and transitions state if required actions are met.
 * 
 * @param t The Tile object to update.
 */
void TileStateYellow::updateTile(Tile& t) {
    if (mBehavior != nullptr) {
        mBehavior->doBehavior(t);
    }
    mCounter++; // Increment the action counter
    if (mCounter >= requiredActions) {
        // Transition to the next state after required amount of actions
        t.setState(TileFactory::createNextState(getColor()));
    }
}

/**
 * @brief Gets the color of the tile state.
 * 
 * @return char The color of the tile state.
 */
char TileStateYellow::getColor() const { return 'Y'; }

/**
 * @brief Code to execute when entering the yellow state.
 */
void TileStateYellow::enter() {
    // Code to execute when entering the yellow state
}

/**
 * @brief Code to execute when exiting the yellow state.
 */
void TileStateYellow::exit() {
    // Code to execute when exiting the yellow state
}

/**
 * @brief Forces the tile to transition to the blue state.
 * 
 * @param t The Tile object to update.
 */
void TileStateYellow::forceBlue(Tile& t) { t.setState(TileFactory::createBlueState()); }

// TileStateWhite Implementation

/**
 * @brief Constructs a new TileStateWhite object.
 * 
 * @param aBehavior A unique pointer to an ITileBehavior object.
 */
TileStateWhite::TileStateWhite(std::unique_ptr<ITileBehavior> aBehavior)
    : mBehavior(std::move(aBehavior)) {}

/**
 * @brief Copy constructor for TileStateWhite.
 * 
 * @param other The TileStateWhite object to copy from.
 */
TileStateWhite::TileStateWhite(const TileStateWhite& other) : mBehavior(other.mBehavior->clone()) {}

/**
 * @brief Assignment operator for TileStateWhite.
 * 
 * @param other The TileStateWhite object to assign from.
 * @return TileStateWhite& A reference to the assigned object.
 */
TileStateWhite& TileStateWhite::operator=(const TileStateWhite& other) {
    if (this != &other) {
        mBehavior = other.mBehavior->clone();
    }
    return *this;
}

/**
 * @brief Clones the current TileStateWhite object.
 * 
 * @return std::unique_ptr<ITileState> A unique pointer to the cloned object.
 */
std::unique_ptr<ITileState> TileStateWhite::clone() const {
    return std::make_unique<TileStateWhite>(*this);
}

/**
 * @brief Updates the tile with the current behavior and transitions state.
 * 
 * @param t The Tile object to update.
 */
void TileStateWhite::updateTile(Tile& t) {
    if (mBehavior != nullptr) {
        mBehavior->doBehavior(t);
    }
    t.setState(TileFactory::createNextState(getColor()));
}

/**
 * @brief Gets the color of the tile state.
 * 
 * @return char The color of the tile state.
 */
char TileStateWhite::getColor() const { return 'W'; }

/**
 * @brief Code to execute when entering the white state.
 */
void TileStateWhite::enter() {
    // Code to execute when entering the white state
}

/**
 * @brief Code to execute when exiting the white state.
 */
void TileStateWhite::exit() {
    // Code to execute when exiting the white state
}

/**
 * @brief Forces the tile to transition to the blue state.
 * 
 * @param t The Tile object to update.
 */
void TileStateWhite::forceBlue(Tile& t) { t.setState(TileFactory::createBlueState()); }

// TileStateRed Implementation

/**
 * @brief Constructs a new TileStateRed object.
 * 
 * @param aBehavior A unique pointer to an ITileBehavior object.
 */
TileStateRed::TileStateRed(std::unique_ptr<ITileBehavior> aBehavior)
    : mBehavior(std::move(aBehavior)) {}

/**
 * @brief Copy constructor for TileStateRed.
 * 
 * @param other The TileStateRed object to copy from.
 */
TileStateRed::TileStateRed(const TileStateRed& other) : mBehavior(other.mBehavior->clone()) {}

/**
 * @brief Assignment operator for TileStateRed.
 * 
 * @param other The TileStateRed object to assign from.
 * @return TileStateRed& A reference to the assigned object.
 */
TileStateRed& TileStateRed::operator=(const TileStateRed& other) {
    if (this != &other) {
        mBehavior = other.mBehavior->clone();
    }
    return *this;
}

/**
 * @brief Clones the current TileStateRed object.
 * 
 * @return std::unique_ptr<ITileState> A unique pointer to the cloned object.
 */
std::unique_ptr<ITileState> TileStateRed::clone() const {
    return std::make_unique<TileStateRed>(*this);
}

/**
 * @brief Updates the tile with the current behavior and transitions state.
 * 
 * @param t The Tile object to update.
 */
void TileStateRed::updateTile(Tile& t) {
    if (mBehavior != nullptr) {
        mBehavior->doBehavior(t);
    }
    t.setState(TileFactory::createNextState(getColor()));
}

/**
 * @brief Gets the color of the tile state.
 * 
 * @return char The color of the tile state.
 */
char TileStateRed::getColor() const { return 'R'; }

/**
 * @brief Code to execute when entering the red state.
 */
void TileStateRed::enter() {
    // Code to execute when entering the red state
}

/**
 * @brief Code to execute when exiting the red state.
 */
void TileStateRed::exit() {
    // Code to execute when exiting the red state
}

/**
 * @brief Forces the tile to transition to the blue state.
 * 
 * @param t The Tile object to update.
 */
void TileStateRed::forceBlue(Tile& t) { t.setState(TileFactory::createBlueState()); }

// TileStateGray Implementation

/**
 * @brief Constructs a new TileStateGray object.
 * 
 * @param aBehavior A unique pointer to an ITileBehavior object.
 */
TileStateGray::TileStateGray(std::unique_ptr<ITileBehavior> aBehavior)
    : mBehavior(std::move(aBehavior)), mCounter(0) {}

/**
 * @brief Copy constructor for TileStateGray.
 * 
 * @param other The TileStateGray object to copy from.
 */
TileStateGray::TileStateGray(const TileStateGray& other) : mBehavior(other.mBehavior->clone()), mCounter(other.mCounter) {}

/**
 * @brief Assignment operator for TileStateGray.
 * 
 * @param other The TileStateGray object to assign from.
 * @return TileStateGray& A reference to the assigned object.
 */
TileStateGray& TileStateGray::operator=(const TileStateGray& other) {
    if (this != &other) {
        mBehavior = other.mBehavior->clone();
        mCounter = other.mCounter;
    }
    return *this;
}

/**
 * @brief Clones the current TileStateGray object.
 * 
 * @return std::unique_ptr<ITileState> A unique pointer to the cloned object.
 */
std::unique_ptr<ITileState> TileStateGray::clone() const {
    return std::make_unique<TileStateGray>(*this);
}

/**
 * @brief Updates the tile with the current behavior and transitions state if required actions are met.
 * 
 * @param t The Tile object to update.
 */
void TileStateGray::updateTile(Tile& t) {
    if (mBehavior != nullptr) {
        mBehavior->doBehavior(t);
    }
    mCounter++; // Increment the action counter
    if (mCounter >= requiredActions) {
        // Transition to the next state after required amount of actions
        t.setState(TileFactory::createNextState(getColor()));
    }
}

/**
 * @brief Gets the color of the tile state.
 * 
 * @return char The color of the tile state.
 */
char TileStateGray::getColor() const { return 'G'; }

/**
 * @brief Code to execute when entering the gray state.
 */
void TileStateGray::enter() {
    // Code to execute when entering the gray state
}

/**
 * @brief Code to execute when exiting the gray state.
 */
void TileStateGray::exit() {
    // Code to execute when exiting the gray state
}

/**
 * @brief Forces the tile to transition to the blue state.
 * 
 * @param t The Tile object to update.
 */
void TileStateGray::forceBlue(Tile& t) { t.setState(TileFactory::createBlueState()); }

// TileStateBlue Implementation

/**
 * @brief Constructs a new TileStateBlue object.
 * 
 * @param aBehavior A unique pointer to an ITileBehavior object.
 */
TileStateBlue::TileStateBlue(std::unique_ptr<ITileBehavior> aBehavior)
    : mBehavior(std::move(aBehavior)), mCounter(0) {}

/**
 * @brief Copy constructor for TileStateBlue.
 * 
 * @param other The TileStateBlue object to copy from.
 */
TileStateBlue::TileStateBlue(const TileStateBlue& other) : mBehavior(other.mBehavior->clone()), mCounter(other.mCounter) {}

/**
 * @brief Assignment operator for TileStateBlue.
 * 
 * @param other The TileStateBlue object to assign from.
 * @return TileStateBlue& A reference to the assigned object.
 */
TileStateBlue& TileStateBlue::operator=(const TileStateBlue& other) {
    if (this != &other) {
        mBehavior = other.mBehavior->clone();
        mCounter = other.mCounter;
    }
    return *this;
}

/**
 * @brief Clones the current TileStateBlue object.
 * 
 * @return std::unique_ptr<ITileState> A unique pointer to the cloned object.
 */
std::unique_ptr<ITileState> TileStateBlue::clone() const {
    return std::make_unique<TileStateBlue>(*this);
}

/**
 * @brief Updates the tile with the current behavior and transitions state.
 * 
 * @param t The Tile object to update.
 */
void TileStateBlue::updateTile(Tile& t) {
    if (mBehavior != nullptr) {
        mBehavior->doBehavior(t);
    }
    t.setState(TileFactory::createNextState(getColor()));
}

/**
 * @brief Gets the color of the tile state.
 * 
 * @return char The color of the tile state.
 */
char TileStateBlue::getColor() const { return 'B'; }

/**
 * @brief Code to execute when entering the blue state.
 */
void TileStateBlue::enter() {
    // Code to execute when entering the blue state
}

/**
 * @brief Code to execute when exiting the blue state.
 */
void TileStateBlue::exit() {
    // Code to execute when exiting the blue state
}

/**
 * @brief Forces the tile to transition to the blue state.
 * 
 * @param t The Tile object to update.
 */
void TileStateBlue::forceBlue(Tile& t) { t.setState(TileFactory::createBlueState()); }