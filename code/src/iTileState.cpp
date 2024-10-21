#include "iTileState.h"
#include "tile.h"
#include "tileFactory.h"

// TileStateYellow Implementation
TileStateYellow::TileStateYellow(std::unique_ptr<ITileBehavior> aBehavior)
    : mBehavior(std::move(aBehavior)), mCounter(0) {}

TileStateYellow::TileStateYellow(const TileStateYellow& other)
    : mBehavior(other.mBehavior->clone()), mCounter(other.mCounter) {}

TileStateYellow& TileStateYellow::operator=(const TileStateYellow& other) {
    if (this != &other) {
        mBehavior = other.mBehavior->clone();
        mCounter = other.mCounter;
    }
    return *this;
}

std::unique_ptr<ITileState> TileStateYellow::clone() const {
    return std::make_unique<TileStateYellow>(*this);
}

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

char TileStateYellow::getColor() const { return 'Y'; }

void TileStateYellow::enter() {
    // Code to execute when entering the yellow state
}

void TileStateYellow::exit() {
    // Code to execute when exiting the yellow state
}

void TileStateYellow::forceBlue(Tile& t) { t.setState(TileFactory::createBlueState()); }

// TileStateWhite Implementation
TileStateWhite::TileStateWhite(std::unique_ptr<ITileBehavior> aBehavior)
    : mBehavior(std::move(aBehavior)) {}

TileStateWhite::TileStateWhite(const TileStateWhite& other) : mBehavior(other.mBehavior->clone()) {}

TileStateWhite& TileStateWhite::operator=(const TileStateWhite& other) {
    if (this != &other) {
        mBehavior = other.mBehavior->clone();
    }
    return *this;
}

std::unique_ptr<ITileState> TileStateWhite::clone() const {
    return std::make_unique<TileStateWhite>(*this);
}

void TileStateWhite::updateTile(Tile& t) {
    if (mBehavior != nullptr) {
        mBehavior->doBehavior(t);
    }
    t.setState(TileFactory::createNextState(getColor()));
}

char TileStateWhite::getColor() const { return 'W'; }

void TileStateWhite::enter() {
    // Code to execute when entering the white state
}

void TileStateWhite::exit() {
    // Code to execute when exiting the white state
}

void TileStateWhite::forceBlue(Tile& t) { t.setState(TileFactory::createBlueState()); }

// TileStateRed Implementation
TileStateRed::TileStateRed(std::unique_ptr<ITileBehavior> aBehavior)
    : mBehavior(std::move(aBehavior)) {}

TileStateRed::TileStateRed(const TileStateRed& other) : mBehavior(other.mBehavior->clone()) {}

TileStateRed& TileStateRed::operator=(const TileStateRed& other) {
    if (this != &other) {
        mBehavior = other.mBehavior->clone();
    }
    return *this;
}

std::unique_ptr<ITileState> TileStateRed::clone() const {
    return std::make_unique<TileStateRed>(*this);
}

void TileStateRed::updateTile(Tile& t) {
    if (mBehavior != nullptr) {
        mBehavior->doBehavior(t);
    }
    t.setState(TileFactory::createNextState(getColor()));
}

char TileStateRed::getColor() const { return 'R'; }

void TileStateRed::enter() {
    // Code to execute when entering the red state
}

void TileStateRed::exit() {
    // Code to execute when exiting the red state
}

void TileStateRed::forceBlue(Tile& t) { t.setState(TileFactory::createBlueState()); }

// TileStateGray Implementation
TileStateGray::TileStateGray(std::unique_ptr<ITileBehavior> aBehavior)
    : mBehavior(std::move(aBehavior)), mCounter(0) {}

TileStateGray::TileStateGray(const TileStateGray& other) : mBehavior(other.mBehavior->clone()), mCounter(other.mCounter) {}

TileStateGray& TileStateGray::operator=(const TileStateGray& other) {
    if (this != &other) {
        mBehavior = other.mBehavior->clone();
        mCounter = other.mCounter;
    }
    return *this;
}

std::unique_ptr<ITileState> TileStateGray::clone() const {
    return std::make_unique<TileStateGray>(*this);
}

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

char TileStateGray::getColor() const { return 'G'; }

void TileStateGray::enter() {
    // Code to execute when entering the gray state
}

void TileStateGray::exit() {
    // Code to execute when exiting the gray state
}

void TileStateGray::forceBlue(Tile& t) { t.setState(TileFactory::createBlueState()); }

// TileStateBlue Implementation
TileStateBlue::TileStateBlue(std::unique_ptr<ITileBehavior> aBehavior)
    : mBehavior(std::move(aBehavior)), mCounter(0) {}

TileStateBlue::TileStateBlue(const TileStateBlue& other) : mBehavior(other.mBehavior->clone()), mCounter(other.mCounter) {}

TileStateBlue& TileStateBlue::operator=(const TileStateBlue& other) {
    if (this != &other) {
        mBehavior = other.mBehavior->clone();
        mCounter = other.mCounter;
    }
    return *this;
}

std::unique_ptr<ITileState> TileStateBlue::clone() const {
    return std::make_unique<TileStateBlue>(*this);
}

void TileStateBlue::updateTile(Tile& t) {
    if (mBehavior != nullptr) {
        mBehavior->doBehavior(t);
    }
    t.setState(TileFactory::createNextState(getColor()));
}

char TileStateBlue::getColor() const { return 'B'; }

void TileStateBlue::enter() {
    // Code to execute when entering the blue state
}

void TileStateBlue::exit() {
    // Code to execute when exiting the blue state
}

void TileStateBlue::forceBlue(Tile& t) { t.setState(TileFactory::createBlueState()); }