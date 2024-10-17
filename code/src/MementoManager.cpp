#include "MementoManager.h"

MementoManager::MementoManager() : mCurrentIndex(-1) {}

void MementoManager::addMemento(Memento memento) {
    // Remove all mementos after the current index
    if (mCurrentIndex < mMementos.size() - 1) {
        mMementos.erase(mMementos.begin() + mCurrentIndex + 1, mMementos.end());
    }
    mMementos.push_back(std::move(memento));
    mCurrentIndex++;
}

Memento MementoManager::getMemento(int index) {
    return std::move(mMementos.at(index));
}

Memento MementoManager::getPreviousMemento() {
    if (mCurrentIndex > 0) {
        mCurrentIndex--;
    }
    return std::move(mMementos.at(mCurrentIndex));
}

Memento MementoManager::getNextMemento() {
    if (mCurrentIndex < mMementos.size() - 1) {
        mCurrentIndex++;
    }
    return std::move(mMementos.at(mCurrentIndex));
}