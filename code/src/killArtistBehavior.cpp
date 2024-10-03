#include "killArtistBehavior.h"

#include <iostream>

void killArtistBehavior::doBehavior() {
    // Code to kill player
        std::pair<int, int> temp{0, 0};
    notify(temp, "removeArtist");
}