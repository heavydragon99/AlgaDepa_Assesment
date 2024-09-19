#include "artist.h"

artist::artist(float aX, float aY, float aVelX, float aVelY) {
    mX = aX;
    mY = aY;
    mVelX = aVelX;
    mVelY = aVelY;
}

void artist::update() {
    mX += mVelX;
    mY += mVelY;
}