#ifndef STRUCTS_H
#define STRUCTS_H

#include <vector>

struct parsedArtist{
    float x;
    float y;
    float vx;
    float vy;
};

struct gridColor{
    char letter;
    int red;
    int green;
    int blue;
    int weight;
};

struct parsedGrid{
    int rows;
    int cols;
    std::vector<gridColor> gridColors;
};

#endif // STRUCTS_H