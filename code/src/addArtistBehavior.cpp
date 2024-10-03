#include "addArtistBehavior.h"

#include <iostream>

void addArtistBehavior::doBehavior() {
    // Code to infect tiles
        std::pair<int, int> temp{0, 0};
    notify(temp, "addArtist");
}