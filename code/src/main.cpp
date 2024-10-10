#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

#include "controller.h"

#include "FileHandler.h"
#include "GridParserStrategy.h"

#include "structs.h"

int main() {
    // struct gridColor {
    //     char letter;
    //     int red;
    //     int green;
    //     int blue;
    //     int weight;
    // };

    // yay text
    FileHandler fileHandler;

    ParsedGrid grid = fileHandler.loadGrid("grid.txt");
    std::vector<ParsedPerson> persons = fileHandler.loadArtist("artists.csv");
    // grid.gridColors.push_back({'R', 255, 0, 0, 0});     // Red
    // grid.gridColors.push_back({'B', 0, 0, 255, 0});     // Blue
    // grid.gridColors.push_back({'Y', 255, 255, 0, 0});   // Yellow
    // grid.gridColors.push_back({'G', 128, 128, 128, 0}); // Gray
    // grid.gridColors.push_back({'W', 255, 255, 255, 0}); // White
    //
    int cols = grid.cols; // specify the number of columns
    int rows = grid.rows; // specify the number of rows
    int numPersons{5};    // specify the number of persons
    //
    // // Initialize random seed
    // std::srand(std::time(0));
    //
    // // Create the grid with all white tiles
    // for (int i = 0; i < cols * rows; i++) {
    //     grid.grid.push_back('W');
    // }
    // grid.cols = cols;
    // grid.rows = rows;
    //
    // // Set 25% of the tiles to another color (e.g., 'B' for black)
    // char color[4]{'R', 'B', 'Y', 'G'};
    // int numBlackTiles = (rows * cols) / 4;
    // for (int i = 0; i < numBlackTiles; ++i) {
    //     int randomPosition = std::rand() % (rows * cols);
    //     int randomColor = std::rand() % 4;
    //     grid.grid[randomPosition] = color[randomColor];
    // }

    // Create persons at random positions
    // for (int i = 0; i < numPersons; ++i) {
    //     int randomPosition = std::rand() % (rows * cols);
    //     bool randomDirection = std::rand() % 2;
    //     ParsedPerson person;
    //     person.x = (randomPosition % cols);
    //     person.y = (randomPosition / cols);
    //     person.vx = randomDirection ? 0.1 : 0;
    //     person.vy = randomDirection ? 0 : 0.1;
    //     persons.push_back(person);
    // }

    controller ctrl(persons, grid);
    ctrl.createLevel();
    ctrl.run();

    return 0;
}

void testParseGridtxt() {
    FileHandler fileHandler;
    ParsedGrid gridData = fileHandler.loadGrid("grid.txt");

    // Get all grid data in one struct
    // GridData gridData = gridParser.getGridData();

    // Output grid size
    std::cout << "Rows: " << gridData.rows << ", Cols: " << gridData.cols << std::endl;

    // Output color mappings
    std::cout << "Color Mappings:" << std::endl;
    for (const auto& color : gridData.gridColors) {
        std::cout << "Letter: " << color.letter << " RGB: [" << color.red << "," << color.green << "," << color.blue
                  << "]" << " Weight: " << color.weight << std::endl;
    }

    // Output the grid buffer
    std::cout << "Grid Buffer:" << std::endl;
    for (int i = 0; i < gridData.grid.size(); ++i) {
        std::cout << gridData.grid[i];
        // if ((i + 1) % gridData.cols == 0)
        //   std::cout << std::endl; // New line after each row
    }

    std::cout << std::endl;

    return;
}

void testParseGridxml() {
    FileHandler fileHandler;
    ParsedGrid gridData = fileHandler.loadGrid("graph.xml");

    // Get all grid data in one struct
    // GridData gridData = gridParser.getGridData();

    // Output grid size
    std::cout << "Rows: " << gridData.rows << ", Cols: " << gridData.cols << std::endl;

    // Output color mappings
    std::cout << "Color Mappings:" << std::endl;
    for (const auto& color : gridData.gridColors) {
        std::cout << "Letter: " << color.letter << " RGB: [" << color.red << "," << color.green << "," << color.blue
                  << "]" << " Weight: " << color.weight << std::endl;
    }

    // Output the grid buffer
    std::cout << "Grid Buffer:" << std::endl;
    for (int i = 0; i < gridData.grid.size(); ++i) {
        std::cout << gridData.grid[i];
        // if ((i + 1) % gridData.cols == 0)
        //   std::cout << std::endl; // New line after each row
    }

    std::cout << std::endl;

    return;
}

void testParseArtists() {
    FileHandler fileHandler;

    std::vector<ParsedPerson> artistData = fileHandler.loadArtist("artists.csv");

    for (const auto& artist : artistData) {
        std::cout << "x: " << artist.x << ", y: " << artist.y << ", vx: " << artist.vx << ", vy: " << artist.vy
                  << std::endl;
    }
    return;
}

// Function to print all lines from an ifstream
void printFileLines(std::ifstream& ifs) {
    std::string line;
    while (std::getline(ifs, line)) {
        std::cout << line << std::endl;
    }
}

void testFileLoading() {
    FileLoaderContext loaderContext;

    std::string localFilePath = "artists.csv"; // Replace with actual file path
    std::string url = "https://firebasestorage.googleapis.com/v0/b/dpa-files.appspot.com/o/"
                      "grid.txt?alt=media";

    auto file = loaderContext.loadFile(localFilePath);
    if (file && file->is_open()) {
        std::cout << "Local file loaded successfully!" << std::endl;
        // printFileLines(*file);
    } else {
        std::cerr << "Failed to load local file." << std::endl;
    }

    // Load and print remote file
    file = loaderContext.loadFile(url);
    if (file && file->is_open()) {
        std::cout << "Remote file downloaded and loaded successfully!" << std::endl;
        // printFileLines(*file);
    } else {
        std::cerr << "Failed to download or load remote file." << std::endl;
    }
}

// Example usage
// int main() {
//     std::cout << "Test Parse Artists: " << std::endl;
//     testParseArtists();
//
//     std::cout << "Test Parse Grid txt: " << std::endl;
//     testParseGridtxt();
//
//     std::cout << "Test Parse Grid xml: " << std::endl;
//     testParseGridxml();
// }
