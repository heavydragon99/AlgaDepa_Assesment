#ifndef MEMENTOMANAGER_H
#define MEMENTOMANAGER_H

#include "Memento.h"
#include <vector>

const int BUFFER_SIZE = 200; // Define the buffer size

/**
 * @class MementoManager
 * @brief Manages a collection of Memento objects with a fixed buffer size.
 */
class MementoManager {
public:
    MementoManager();
    void addMemento(Memento memento);

    Memento getMemento(int index);

    Memento getPreviousMemento();
    Memento getNextMemento();

private:
    std::vector<Memento> mMementos; ///< Vector to store mementos
    int mCurrentIndex; ///< Current index in the memento buffer
    int mStartIndex; ///< Start index for the circular buffer
    int mSize; ///< Current size of the buffer
    int mValidSize; ///< Valid size of the buffer
};

#endif // MEMENTOMANAGER_H