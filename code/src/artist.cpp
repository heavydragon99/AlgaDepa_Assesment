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

const Artist::Location& Artist::getLocation() const { return mLocation; }

void Artist::setLocation(Location aLocation) { mLocation = aLocation; }

void Artist::collidedWall() {
    if (mVelX != 0) {
        mVelX = -mVelX;
    }
    if (mVelY != 0) {
        mVelY = -mVelY;
    }

    this->triggerRed();
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

bool Artist::getRed() {
    if (SDL_GetTicks() < mEndOfRedTime) {
        return true;
    } else {
        return false;
    }
}

void Artist::triggerRed(int mRedTimeInMs) { mEndOfRedTime = SDL_GetTicks() + mRedTimeInMs; }
