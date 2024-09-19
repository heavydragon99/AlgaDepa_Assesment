#ifndef PERSONFACTORY_H
#define PERSONFACTORY_H

#include "artist.h"
#include "visitor.h"

#include <memory>

enum class personType {
    Artist,
    Visitor
};

class personFactory {
public:
    static std::unique_ptr<iPerson> createPerson(personType type, float x, float y, float velX, float velY);
};

#endif // PERSONFACTORY_H