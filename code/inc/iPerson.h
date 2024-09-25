#ifndef IPERSON_H
#define IPERSON_H

class iPerson {
public:
    virtual ~iPerson() = default;

    virtual void update() = 0;

    virtual float getX() const { return mX; }
    virtual float getY() const { return mY; }
    virtual void setX(float x) { mX = x; }
    virtual void setY(float y) { mY = y; }

    virtual void collided() {
        if (mVelX != 0) {
            mVelX = -mVelX;
        }
        if (mVelY != 0) {
            mVelY = -mVelY;
        }
    }

protected:
    float mX;
    float mY;
    float mVelX;
    float mVelY;
};

#endif // IPERSON_H
