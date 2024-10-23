#ifndef STRUCTS_H
#define STRUCTS_H

#include <vector>

/**
 * @brief Structure to represent a person with position and velocity.
 */
struct ParsedPerson {
    float x; ///< X-coordinate of the person
    float y; ///< Y-coordinate of the person
    float vx; ///< Velocity in the X direction
    float vy; ///< Velocity in the Y direction
};

/**
 * @brief Structure to represent a color in the grid.
 */
struct GridColor {
    char letter; ///< Letter representing the color
    int red; ///< Red component of the color
    int green; ///< Green component of the color
    int blue; ///< Blue component of the color
    int weight; ///< Weight of the color
};

/**
 * @brief Structure to represent a parsed grid.
 */
struct ParsedGrid {
    int rows; ///< Number of rows in the grid
    int cols; ///< Number of columns in the grid
    std::vector<GridColor> gridColors; ///< Vector of grid colors
    std::vector<char> grid; ///< Vector representing the grid
};

/**
 * @brief Structure to represent a point with x and y coordinates.
 */
struct Point {
    int x = 0; ///< X-coordinate of the point
    int y = 0; ///< Y-coordinate of the point
};

#endif // STRUCTS_H