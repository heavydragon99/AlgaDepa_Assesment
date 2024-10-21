#include "MementoManager.h"

#include <stdexcept>

MementoManager::MementoManager() : mCurrentIndex(-1), mStartIndex(0), mSize(0) {
    mMementos.resize(BUFFER_SIZE);
}

void MementoManager::addMemento(Memento memento) {
    if (mSize < BUFFER_SIZE) {
        mSize++;
    } else {
        mStartIndex = (mStartIndex + 1) % BUFFER_SIZE;
    }
    mCurrentIndex = (mCurrentIndex + 1) % BUFFER_SIZE;
    mMementos[mCurrentIndex] = std::move(memento);
}

Memento MementoManager::getMemento(int index) {
    if (index < 0 || index >= mSize) {
        throw std::out_of_range("Index out of range");
    }
    int actualIndex = (mStartIndex + index) % BUFFER_SIZE;
    return mMementos[actualIndex];
}

Memento MementoManager::getPreviousMemento() {
    if (mSize == 0) {
        throw std::out_of_range("No mementos available");
    }
    if (mCurrentIndex == mStartIndex) {
        throw std::out_of_range("No previous memento available");
    }
    mCurrentIndex = (mCurrentIndex - 1 + BUFFER_SIZE) % BUFFER_SIZE;
    return mMementos[mCurrentIndex];
}

Memento MementoManager::getNextMemento() {
    if (mSize == 0) {
        throw std::out_of_range("No mementos available");
    }
    int nextIndex = (mCurrentIndex + 1) % BUFFER_SIZE;
    if (nextIndex == (mStartIndex + mSize) % BUFFER_SIZE) {
        throw std::out_of_range("No next memento available");
    }
    mCurrentIndex = nextIndex;
    return mMementos[mCurrentIndex];
}