#include "artist.h"

artist::artist(float aX, float aY, float aVelX, float aVelY) {
    mX = aX;
    mY = aY;
    mVelX = aVelX;
    mVelY = aVelY;
}

#include <iostream>

void artist::update() {
    // std::cout << "artist update" << std::endl;
    //
    // std::cout << mX << std::endl;
    // std::cout << mY << std::endl;
    // std::cout << mVelX << std::endl;
    // std::cout << mVelY << std::endl;
    mX += mVelX;
    mY += mVelY;
}
