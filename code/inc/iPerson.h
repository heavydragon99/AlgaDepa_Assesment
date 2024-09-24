#ifndef IPERSON_H
#define IPERSON_H

class iPerson {
public:
    virtual ~iPerson() = default;

    virtual void update() = 0;

    virtual float getX() const { return mX; }
    virtual float getY() const { return mY; }

protected:
    float mX;
    float mY;
    float mVelX;
    float mVelY;
};

#endif // IPERSON_H
