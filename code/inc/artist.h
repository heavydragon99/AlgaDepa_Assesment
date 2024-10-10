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

    const Location& getLocation() const;
    void setLocation(Location aLocation);

    void collidedWall();

private:
    Location mLocation;
    float mVelX;
    float mVelY;
};

#endif // ARTIST_H
