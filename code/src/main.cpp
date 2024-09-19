#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "controller.h"

int main()
{
    struct gridColor{
    char letter;
    int red;
    int green;
    int blue;
    int weight;
};
    parsedGrid grid;
    std::vector<parsedPerson> persons;
    grid.gridColors.push_back({'R', 255, 0, 0, 0});   // Red
    grid.gridColors.push_back({'B', 0, 0, 255, 0});   // Blue
    grid.gridColors.push_back({'Y', 255, 255, 0, 0}); // Yellow
    grid.gridColors.push_back({'G', 128, 128, 128, 0}); // Gray
    grid.gridColors.push_back({'W', 255, 255, 255, 0}); // White


    int cols{10};      // specify the number of columns
    int rows{10};      // specify the number of rows
    int numPersons{5}; // specify the number of persons


    // Initialize random seed
    std::srand(std::time(0));

    // Create the grid with all white tiles
    for (int i = 0; i < cols * rows; i++)
    {
        grid.grid.push_back('W');
    }
    grid.cols = cols;
    grid.rows = rows;

    // Set 25% of the tiles to another color (e.g., 'B' for black)
    char color[4]{'R', 'B', 'Y', 'G'};
    int numBlackTiles = (rows * cols) / 4;
    for (int i = 0; i < numBlackTiles; ++i)
    {
        int randomPosition = std::rand() % (rows * cols);
        int randomColor = std::rand() % 4;
        grid.grid[randomPosition] = color[randomColor];
    }

    // Create persons at random positions
    for (int i = 0; i < numPersons; ++i)
    {
        int randomPosition = std::rand() % (rows * cols);
        bool randomDirection = std::rand() % 2;
        parsedPerson person;
        person.x = (randomPosition % cols);
        person.y = (randomPosition / cols);
        person.vx = randomDirection ? 1 : 0;
        person.vy = randomDirection ? 0 : 1;
        persons.push_back(person);
    }

    controller ctrl(persons, grid);
    ctrl.createLevel();

    return 0;
}