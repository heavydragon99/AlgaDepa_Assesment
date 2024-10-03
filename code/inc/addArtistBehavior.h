// KillPlayerBehavior.h
#ifndef ADDARTISTBEHAVIOR_H
#define ADDARTISTBEHAVIOR_H

#include "iTileBehavior.h"
#include "iSubject.h"

class addArtistBehavior : public iTileBehavior, public iSubject {
public:
    addArtistBehavior() = default;
    void doBehavior() override;
};;

#endif // ADDARTISTBEHAVIOR_H