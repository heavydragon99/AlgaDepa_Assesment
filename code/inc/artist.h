#ifndef ARTIST_H
#define ARTIST_H

#include "iPerson.h"

class artist : public iPerson {
public:
    artist(float aX, float aY, float aVelX, float aVelY);
    void update() override;
};

#endif // ARTIST_H