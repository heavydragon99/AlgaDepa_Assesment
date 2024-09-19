#ifndef ITILESTATE_H
#define ITILESTATE_H

class tile;

class iTileState {
public:
    virtual ~iTileState() = default;
    virtual void updateTile(tile* t) = 0;
};

#endif // ITILESTATE_H