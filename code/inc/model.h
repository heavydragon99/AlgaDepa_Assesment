#ifndef MODEL_H
#define MODEL_H

#include "levelData.h"
#include "structs.h"
#include "Memento.h"

#include <memory>

class Model {
public:
    Model();
    void createLevel(std::vector<ParsedPerson> aPersons, ParsedGrid aGrid);
    LevelData& getLevelData();

    void updateModel();

    Memento saveToMemento() const;
    void restoreFromMemento(Memento&& memento);

private:
    std::unique_ptr<LevelData> mLevel;
};

#endif // MODEL_H