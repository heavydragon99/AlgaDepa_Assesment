#ifndef ARTIST_H
#define ARTIST_H

class artist {
public:
    artist(float aX, float aY, float aVelX, float aVelY);
    virtual ~artist() = default;

    void update();

    float getX() const;
    float getY() const;
    void setX(float x);
    void setY(float y);
    
    void collided();

private:
    float mX;
    float mY;
    float mVelX;
    float mVelY;
};

#endif // ARTIST_H
