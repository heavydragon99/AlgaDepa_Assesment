#include "artist.h"

#include <SDL_timer.h>
#include <cmath>
#include <iostream>

artist::artist(Location aLocation, float aVelX, float aVelY) : mLocation(aLocation), mVelX(aVelX), mVelY(aVelY) {}

artist::Location artist::update() {
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

const artist::Location& artist::getLocation() const { return mLocation; }

void artist::setLocation(Location aLocation) { mLocation = aLocation; }

void artist::collidedWall() {
    if (mVelX != 0) {
        mVelX = -mVelX;
    }
    if (mVelY != 0) {
        mVelY = -mVelY;
    }

    this->triggerRed();
}

void artist::collidedOtherArtist() {
    if (mVelX != 0) {
        mVelX = -mVelX;
    }
    if (mVelY != 0) {
        mVelY = -mVelY;
    }

    this->triggerRed();
}

bool artist::getRed() {
    if (SDL_GetTicks() < mEndOfRedTime) {
        return true;
    } else {
        return false;
    }
}

void artist::triggerRed(int mRedTimeInMs) { mEndOfRedTime = SDL_GetTicks() + mRedTimeInMs; }
