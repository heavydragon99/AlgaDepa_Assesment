#include "artist.h"

#include <SDL_timer.h>
#include <cmath>
#include <iostream>

Artist::Artist(Location aLocation, float aVelX, float aVelY) : mLocation(aLocation), mVelX(aVelX), mVelY(aVelY) {}

Artist::Location Artist::update() {
    int xOld = mLocation.mX;
    int yOld = mLocation.mY;

    mLocation.mX += mVelX;
    mLocation.mY += mVelY;

    if (std::floor(mLocation.mX) != std::floor(xOld) || std::floor(mLocation.mY) != std::floor(yOld)) {
        return {std::floor(mLocation.mX), std::floor(mLocation.mY)};
    } else {
        return {-1, -1};
    }
}

Artist::Location& Artist::getLocation() { return mLocation; }

void Artist::setLocation(Location aLocation) { mLocation = aLocation; }

void Artist::collidedWall(bool aTop) {
    if (mVelX != 0) {
        if (!aTop) {
            mVelX = abs(mVelX);
        }

        if (aTop) {
            mVelX = -abs(mVelX);
        }
    }
    if (mVelY != 0) {
        if (!aTop) {
            mVelY = abs(mVelY);
        }

        if (aTop) {
            mVelY = -abs(mVelY);
        }
    }

    // this->triggerRed();
}

void Artist::collidedOtherArtist() {
    // if (mVelX != 0) {
    //     mVelX = -mVelX;
    // }
    // if (mVelY != 0) {
    //     mVelY = -mVelY;
    // }

    this->triggerRed();
}

void Artist::resetRed() { mIsRed = false; }

bool Artist::getRed() { return mIsRed; }

void Artist::triggerRed() { mIsRed = true; }
