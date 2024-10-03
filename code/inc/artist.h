#ifndef ARTIST_H
#define ARTIST_H

class artist {
public:
    struct Location {
        float mX;
        float mY;
    };

public:
    artist(Location aLocation, float aVelX, float aVelY);
    virtual ~artist() = default;

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
