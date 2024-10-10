#ifndef ITILESTATE_H
#define ITILESTATE_H

class Tile;

class ITileState {
public:
    virtual ~ITileState() = default;
    virtual void updateTile(Tile& t) = 0;
    virtual char getColor() const = 0;
    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual void forceBlue(Tile& t) = 0;
   
};

#endif // ITILESTATE_H