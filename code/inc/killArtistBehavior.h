// KillPlayerBehavior.h
#ifndef KILLPLAYERBEHAVIOR_H
#define KILLPLAYERBEHAVIOR_H

#include "iTileBehavior.h"

class killArtistBehavior : public iTileBehavior {
public:
    killArtistBehavior() = default;
    void doBehavior() override;
};;

#endif // KILLPLAYERBEHAVIOR_H