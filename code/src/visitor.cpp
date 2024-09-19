#include "visitor.h"

visitor::visitor(float aX, float aY, float aVelX, float aVelY) {
    mX = aX;
    mY = aY;
    mVelX = aVelX;
    mVelY = aVelY;
}

void visitor::update() {
    mX += mVelX;
    mY += mVelY;
}