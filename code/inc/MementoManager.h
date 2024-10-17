#ifndef MEMENTOMANAGER_H
#define MEMENTOMANAGER_H

#include "Memento.h"

#include <vector>

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
};

#endif // MEMENTOMANAGER_H