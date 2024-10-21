#include "MementoManager.h"
#include <stdexcept>
#include <iostream>

MementoManager::MementoManager() : mCurrentIndex(-1), mStartIndex(0), mSize(0) , mValidSize(0) { mMementos.resize(BUFFER_SIZE); }

void MementoManager::addMemento(Memento memento) {
    mSize = mValidSize;
    if (mSize < BUFFER_SIZE) {
        mSize++;
    } else {
        mStartIndex = (mStartIndex + 1) % BUFFER_SIZE;
    }
    mCurrentIndex = (mCurrentIndex + 1) % BUFFER_SIZE;
    mMementos[mCurrentIndex] = std::move(memento);
    mValidSize = mSize;
    std::cout << "Memento added" << std::endl;
}

Memento MementoManager::getMemento(int index) {
    if (index < 0 || index >= mSize) {
        throw std::out_of_range("Index out of range");
    }
    int actualIndex = (mStartIndex + index) % BUFFER_SIZE;
    return mMementos[actualIndex];
}

Memento MementoManager::getPreviousMemento() {
    if (mValidSize <= 1) {
        throw std::out_of_range("No previous memento available");
    }
    int previousIndex = (mCurrentIndex - 1 + BUFFER_SIZE) % BUFFER_SIZE;
    mCurrentIndex = previousIndex;
    mValidSize--;
    return mMementos[mCurrentIndex];
}

Memento MementoManager::getNextMemento() {
    if (mValidSize >= mSize) {
        throw std::out_of_range("No next mementos available");
    }
    int nextIndex = (mCurrentIndex + 1) % BUFFER_SIZE;
    mCurrentIndex = nextIndex;
    mValidSize++;
    return mMementos[mCurrentIndex];
}