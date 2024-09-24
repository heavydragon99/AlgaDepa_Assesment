#pragma once

#include <vector>

#include "FileLoader.h"

enum FileType { UNDEFINED, CSV, TXT, XML };

struct ArtistData {
    double x;
    double y;
    double vx;
    double vy;
};

// Color struct to store color properties
struct Color {
    char letter;
    int r, g, b; // RGB values
    int weight;
};

// New struct that consolidates all the grid data
struct GridData {
    int rows;
    int cols;
    std::vector<char> gridBuffer; // Character grid buffer
    std::vector<Color> colors;    // Color mappings
};

struct LoadedFile {
    std::unique_ptr<std::ifstream> openedFile = nullptr;
    FileType fileType = UNDEFINED;
};

class FileHandler {
public:
    FileHandler();

    std::vector<ArtistData> loadArtist(std::string aFilePath);
    GridData loadGrid(std::string aFilePath);

private:
    FileType getFileType(std::string aFilePath);
};
