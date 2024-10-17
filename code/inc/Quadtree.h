#pragma once

#include "artist.h"
#include <array>
#include <memory>
#include <vector>

class Quadtree {
public:
    Quadtree(int level, float x, float y, float width, float height);
    void clear();
    void insert(Artist* artist);
    std::vector<Artist*> retrieve(std::vector<Artist*>& returnObjects, Artist* artist);

private:
    int mLevel;
    std::vector<Artist*> mObjects;
    float mX, mY, mWidth, mHeight;
    std::array<std::unique_ptr<Quadtree>, 4> mNodes; // Four children for quadrant subdivision

    const int MAX_OBJECTS = 5;
    const int MAX_LEVELS = 5;

    void subdivide();
    int getIndex(Artist* artist);
};
