#include "MementoManager.h"
#include <stdexcept>
#include <iostream>

/**
 * @brief Constructs a new MementoManager object.
 */
MementoManager::MementoManager() : mCurrentIndex(-1), mStartIndex(0), mSize(0) , mValidSize(0) { 
    mMementos.resize(BUFFER_SIZE); 
}

/**
 * @brief Adds a new memento to the manager.
 * 
 * @param memento The memento to add.
 */
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

/**
 * @brief Retrieves a memento by its index.
 * 
 * @param index The index of the memento to retrieve.
 * @return Memento The memento at the specified index.
 * @throws std::out_of_range If the index is out of range.
 */
Memento MementoManager::getMemento(int index) {
    if (index < 0 || index >= mSize) {
        throw std::out_of_range("Index out of range");
    }
    int actualIndex = (mStartIndex + index) % BUFFER_SIZE;
    return mMementos[actualIndex];
}

/**
 * @brief Retrieves the previous memento.
 * 
 * @return Memento The previous memento.
 * @throws std::out_of_range If there is no previous memento available.
 */
Memento MementoManager::getPreviousMemento() {
    if (mValidSize <= 1) {
        throw std::out_of_range("No previous memento available");
    }
    int previousIndex = (mCurrentIndex - 1 + BUFFER_SIZE) % BUFFER_SIZE;
    mCurrentIndex = previousIndex;
    mValidSize--;
    return mMementos[mCurrentIndex];
}

/**
 * @brief Retrieves the next memento.
 * 
 * @return Memento The next memento.
 * @throws std::out_of_range If there are no next mementos available.
 */
Memento MementoManager::getNextMemento() {
    if (mValidSize >= mSize) {
        throw std::out_of_range("No next mementos available");
    }
    int nextIndex = (mCurrentIndex + 1) % BUFFER_SIZE;
    mCurrentIndex = nextIndex;
    mValidSize++;
    return mMementos[mCurrentIndex];
}