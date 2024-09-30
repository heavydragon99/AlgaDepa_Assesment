#include "artist.h"

artist::artist(float aX, float aY, float aVelX, float aVelY): mX(aX), mY(aY), mVelX(aVelX), mVelY(aVelY) {}


#include <iostream>

void artist::update() {
    mX += mVelX;
    mY += mVelY;
}

    float artist::getX() const { return mX; }

    float artist::getY() const { return mY; }

    void artist::setX(float x) { mX = x; }

    void artist::setY(float y) { mY = y; }

    void artist::collided() {
        if (mVelX != 0) {
            mVelX = -mVelX;
        }
        if (mVelY != 0) {
            mVelY = -mVelY;
        }
    }
