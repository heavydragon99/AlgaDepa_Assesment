#include "Memento.h"

Memento::Memento(std::unique_ptr<LevelData> aState) : mState(std::move(aState)) {}

std::unique_ptr<LevelData> Memento::getState() {
    return std::move(mState);
}