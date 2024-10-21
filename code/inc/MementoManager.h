#ifndef MEMENTOMANAGER_H
#define MEMENTOMANAGER_H

#include "Memento.h"
#include <vector>

const int BUFFER_SIZE = 10; // Define the buffer size

class MementoManager {
public:
    MementoManager();
    void addMemento(Memento memento);

    Memento getMemento(int index);

    Memento getPreviousMemento();
    Memento getNextMemento();

private:
    std::vector<Memento> mMementos;
    int mCurrentIndex;
    int mStartIndex;
    int mSize;
};

#endif // MEMENTOMANAGER_H