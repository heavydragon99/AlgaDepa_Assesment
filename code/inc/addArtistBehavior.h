// KillPlayerBehavior.h
#ifndef ADDARTISTBEHAVIOR_H
#define ADDARTISTBEHAVIOR_H

#include "iTileBehavior.h"

class addArtistBehavior : public iTileBehavior {
public:
    addArtistBehavior() = default;
    void doBehavior() override;
};;

#endif // ADDARTISTBEHAVIOR_H