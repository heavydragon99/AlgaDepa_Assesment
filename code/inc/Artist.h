#ifndef ARTIST_H
#define ARTIST_H

/**
 * @class Artist
 * @brief Represents an artist with a location and velocity, capable of updating its position and handling collisions.
 */
class Artist {
public:
    /**
     * @struct Location
     * @brief Represents the location of the artist.
     */
    struct Location {
        float mX; ///< X-coordinate of the location.
        float mY; ///< Y-coordinate of the location.
    };

public:
    Artist(Location aLocation, float aVelX, float aVelY);
    virtual ~Artist() = default;

    Location update();

    Location& getLocation();
    void setLocation(Location aLocation);

    void collidedWall(bool aTop);
    void collidedOtherArtist();

    bool getRed();

    void triggerRed();
    void resetRed();

private:
    Location mLocation; ///< Current location of the artist.
    float mVelX; ///< Velocity in the X direction.
    float mVelY; ///< Velocity in the Y direction.

    bool mIsRed = false; ///< Indicates if the artist is red.
};

#endif // ARTIST_H
