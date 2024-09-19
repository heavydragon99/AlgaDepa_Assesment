#ifndef STRUCTS_H
#define STRUCTS_H

#include "personFactory.h"

#include <vector>

struct parsedPerson{
    float x;
    float y;
    float vx;
    float vy;
    personType type;
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
    std::vector<char> grid;
};

#endif // STRUCTS_H