#ifndef STRUCTS_H
#define STRUCTS_H

// #include "personFactory.h"

#include <vector>

enum class personType { Artist, Visitor };

struct ParsedPerson {
    float x;
    float y;
    float vx;
    float vy;
};

struct GridColor {
    char letter;
    int red;
    int green;
    int blue;
    int weight;
};

struct ParsedGrid {
    int rows;
    int cols;
    std::vector<GridColor> gridColors;
    std::vector<char> grid;
};

#endif // STRUCTS_H
