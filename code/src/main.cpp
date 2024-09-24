#include <fstream>
#include <iostream>

#include <curl/curl.h>
#include <curl/easy.h>

#include "FileHandler.h"
#include "GridParserStrategy.h"

void testParseGridtxt() {
    FileHandler fileHandler;
    GridData gridData = fileHandler.loadGrid("grid.txt");

    // Get all grid data in one struct
    // GridData gridData = gridParser.getGridData();

    // Output grid size
    std::cout << "Rows: " << gridData.rows << ", Cols: " << gridData.cols << std::endl;

    // Output color mappings
    std::cout << "Color Mappings:" << std::endl;
    for (const auto& color : gridData.colors) {
        std::cout << "Letter: " << color.letter << " RGB: [" << color.r << "," << color.g << "," << color.b << "]"
                  << " Weight: " << color.weight << std::endl;
    }

    // Output the grid buffer
    std::cout << "Grid Buffer:" << std::endl;
    for (int i = 0; i < gridData.gridBuffer.size(); ++i) {
        std::cout << gridData.gridBuffer[i];
        // if ((i + 1) % gridData.cols == 0)
        //   std::cout << std::endl; // New line after each row
    }

    std::cout << std::endl;

    return;
}

void testParseGridxml() {
    FileHandler fileHandler;
    GridData gridData = fileHandler.loadGrid("graph.xml");

    // Get all grid data in one struct
    // GridData gridData = gridParser.getGridData();

    // Output grid size
    std::cout << "Rows: " << gridData.rows << ", Cols: " << gridData.cols << std::endl;

    // Output color mappings
    std::cout << "Color Mappings:" << std::endl;
    for (const auto& color : gridData.colors) {
        std::cout << "Letter: " << color.letter << " RGB: [" << color.r << "," << color.g << "," << color.b << "]"
                  << " Weight: " << color.weight << std::endl;
    }

    // Output the grid buffer
    std::cout << "Grid Buffer:" << std::endl;
    for (int i = 0; i < gridData.gridBuffer.size(); ++i) {
        std::cout << gridData.gridBuffer[i];
        // if ((i + 1) % gridData.cols == 0)
        //   std::cout << std::endl; // New line after each row
    }

    std::cout << std::endl;

    return;
}

void testParseArtists() {
    FileHandler fileHandler;

    std::vector<ArtistData> artistData = fileHandler.loadArtist("artists.csv");

    for (const auto& artist : artistData) {
        std::cout << "x: " << artist.x << ", y: " << artist.y << ", vx: " << artist.vx << ", vy: " << artist.vy
                  << std::endl;
    }
    return;
}
//
// // Function to print all lines from an ifstream
// void printFileLines(std::ifstream& ifs) {
//     std::string line;
//     while (std::getline(ifs, line)) {
//         std::cout << line << std::endl;
//     }
// }
//
// void testFileLoading() {
//     FileLoaderContext loaderContext;
//
//     std::string localFilePath = "artists.csv"; // Replace with actual file path
//     std::string url = "https://firebasestorage.googleapis.com/v0/b/dpa-files.appspot.com/o/"
//                       "grid.txt?alt=media";
//
//     auto file = loaderContext.loadFile(localFilePath);
//     if (file && file->is_open()) {
//         std::cout << "Local file loaded successfully!" << std::endl;
//         // printFileLines(*file);
//     } else {
//         std::cerr << "Failed to load local file." << std::endl;
//     }
//
//     // Load and print remote file
//     file = loaderContext.loadFile(url);
//     if (file && file->is_open()) {
//         std::cout << "Remote file downloaded and loaded successfully!" << std::endl;
//         // printFileLines(*file);
//     } else {
//         std::cerr << "Failed to download or load remote file." << std::endl;
//     }
// }
//
// Example usage
int main() {
    std::cout << "Test Parse Artists: " << std::endl;
    testParseArtists();

    std::cout << "Test Parse Grid txt: " << std::endl;
    testParseGridtxt();

    std::cout << "Test Parse Grid xml: " << std::endl;
    testParseGridxml();
}
