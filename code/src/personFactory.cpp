#include "personFactory.h"

std::unique_ptr<iPerson> personFactory::createPerson(personType type, float x, float y, float velX, float velY) {
    switch (type) {
        case personType::Artist:
            return std::make_unique<artist>(x, y, velX, velY);
        case personType::Visitor:
            return std::make_unique<visitor>(x, y, velX, velY);
        default:
            return nullptr;
    }
}