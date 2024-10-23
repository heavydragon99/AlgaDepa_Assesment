#include "Artist.h"

#include <SDL_timer.h>
#include <cmath>
#include <iostream>

/**
 * @brief Constructs a new Artist object.
 * @param aLocation Initial location of the artist.
 * @param aVelX Initial velocity in the X direction.
 * @param aVelY Initial velocity in the Y direction.
 */
Artist::Artist(Location aLocation, float aVelX, float aVelY) : mLocation(aLocation), mVelX(aVelX), mVelY(aVelY) {}

/**
 * @brief Updates the artist's location based on its velocity.
 * @return The new location if it has changed, otherwise {-1, -1}.
 */
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

/**
 * @brief Gets the current location of the artist.
 * @return Reference to the current location.
 */
Artist::Location& Artist::getLocation() { return mLocation; }

/**
 * @brief Sets the location of the artist.
 * @param aLocation The new location to set.
 */
void Artist::setLocation(Location aLocation) { mLocation = aLocation; }

/**
 * @brief Handles collision with a wall.
 * @param aTop Indicates if the collision was with the top wall.
 */
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

}

/**
 * @brief Handles collision with another artist.
 */
void Artist::collidedOtherArtist() {
    triggerRed();
}

/**
 * @brief Resets the red state of the artist.
 */
void Artist::resetRed() { mIsRed = false; }

/**
 * @brief Checks if the artist is red.
 * @return True if the artist is red, otherwise false.
 */
bool Artist::getRed() { return mIsRed; }

/**
 * @brief Triggers the red state of the artist.
 */
void Artist::triggerRed() { mIsRed = true; }