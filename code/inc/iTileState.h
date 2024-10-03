#ifndef ITILESTATE_H
#define ITILESTATE_H

class tile;

class iTileState {
public:
    virtual ~iTileState() = default;
    virtual void updateTile(tile& t) = 0;
    virtual char getColor() const = 0;
    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual void forceBlue(tile& t) = 0;

protected:
    std::unique_ptr<iTileBehavior> mBehavior;
};

#endif // ITILESTATE_H