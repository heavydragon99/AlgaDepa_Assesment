#ifndef MODEL_H
#define MODEL_H

#include "Memento.h"
#include "MementoManager.h"
#include "levelData.h"
#include "structs.h"

#include <memory>
#include <chrono>

class Model {
public:
    Model();
    void createLevel(std::vector<ParsedPerson> aPersons, ParsedGrid aGrid);
    LevelData& getLevelData();

    void updateModel();

    void usePreviousMemento();
    void useNextMemento();

private:
    Memento saveToMemento() const;
    void restoreFromMemento(Memento&& memento);

private:
    std::unique_ptr<LevelData> mLevel;
    std::unique_ptr<MementoManager> mMementoManager;
    std::chrono::time_point<std::chrono::steady_clock> mLastUpdateTime;
    static constexpr std::chrono::seconds UPDATE_INTERVAL{1}; // Define the interval here
};


#endif // MODEL_H