#ifndef ITILESTATE_H
#define ITILESTATE_H

class tile;

class iTileState
{
public:
    virtual ~iTileState() = default;
    virtual void updateTile(tile *t) = 0;
    virtual char getColor() const = 0;
    virtual void enter(tile *t) = 0;
    virtual void exit(tile *t) = 0;
};

#endif // ITILESTATE_H