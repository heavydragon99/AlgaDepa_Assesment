#pragma once

#include <vector>

#include "FileLoader.h"
#include "structs.h"

enum FileType { UNDEFINED, CSV, TXT, XML };

// Color struct to store color properties
// struct GridColor {
//     char letter;
//     int r, g, b; // RGB values
//     int weight;
// };

// New struct that consolidates all the grid data
// struct parsedGrid {
//     int rows;
//     int cols;
//     std::vector<char> grid;        // Character grid buffer
//     std::vector<Color> gridColors; // Color mappings
// };

struct LoadedFile {
    std::unique_ptr<std::ifstream> openedFile = nullptr;
    FileType fileType = UNDEFINED;
};

class FileHandler {
public:
    FileHandler();

    std::vector<ParsedPerson> loadArtist(std::string aFilePath);
    ParsedGrid loadGrid(std::string aFilePath);

private:
    FileType getFileType(std::string aFilePath);
};
