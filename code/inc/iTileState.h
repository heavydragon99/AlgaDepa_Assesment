#ifndef ITILESTATE_H
#define ITILESTATE_H

class tile;

class iTileState {
public:
    virtual ~iTileState() {}
    virtual void updateTile(tile* t) = 0;
};

#endif // ITILESTATE_H