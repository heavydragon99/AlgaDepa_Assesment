#ifndef ARTIST_H
#define ARTIST_H

class Artist {
public:
    struct Location {
        float mX;
        float mY;
    };

public:
    Artist(Location aLocation, float aVelX, float aVelY);
    virtual ~Artist() = default;

    Location update();

    Location& getLocation();
    void setLocation(Location aLocation);

    void collidedWall();
    void collidedOtherArtist();

    bool getRed();

    void triggerRed();

private:
    Location mLocation;
    float mVelX;
    float mVelY;

    bool mIsRed = false;
};

#endif // ARTIST_H
