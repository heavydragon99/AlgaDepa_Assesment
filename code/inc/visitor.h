#ifndef VISITOR_H
#define VISITOR_H

#include "iPerson.h"

class visitor : public iPerson {
public:
    visitor(float aX, float aY, float aVelX, float aVelY);
    void update() override;
};

#endif // VISITOR_H