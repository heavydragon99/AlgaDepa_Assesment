#ifndef PERSONFACTORY_H
#define PERSONFACTORY_H

#include "artist.h"
#include "structs.h"
#include "visitor.h"

#include <memory>

class personFactory {
public:
    static std::unique_ptr<iPerson> createPerson(personType type, float x, float y, float velX, float velY);
};

#endif // PERSONFACTORY_H
