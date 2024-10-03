// KillPlayerBehavior.h
#ifndef KILLPLAYERBEHAVIOR_H
#define KILLPLAYERBEHAVIOR_H

#include "iTileBehavior.h"
#include "iSubject.h"

class killArtistBehavior : public iTileBehavior, public iSubject {
public:
    killArtistBehavior() = default;
    void doBehavior() override;
};;

#endif // KILLPLAYERBEHAVIOR_H