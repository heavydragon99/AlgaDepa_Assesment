#include "GridParserStrategy.h"
#include <fstream>
#include <iostream>
#include <sstream>

#include "structs.h"

// Function to parse a color line like "Y,[250,201,1],1"
GridColor GridTXTParser::parseColor(const std::string& line) const {
    GridColor color;
    std::stringstream ss(line);
    char ignore, comma;

    ss >> color.letter;         // letter
    ss >> ignore >> ignore;     // "["
    ss >> color.red >> comma;   // red value
    ss >> color.green >> comma; // green value
    ss >> color.blue >> ignore; // blue value
    ss >> ignore;               // "]"
    ss >> color.weight;         // weight

    return color;
}

// Function to parse the grid file and store the data
ParsedGrid GridTXTParser::parseFile(std::ifstream& aFileStream) {
    int rows, cols;
    std::vector<GridColor> colors;
    std::vector<char> gridBuffer;

    if (!aFileStream.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return ParsedGrid();
    }

    std::string line;

    // Step 1: Read grid dimensions
    std::getline(aFileStream, line); // e.g., "rows=53,cols=53"
    sscanf(line.c_str(), "rows=%d,cols=%d", &rows, &cols);

    // Step 2: Read the color mapping header
    std::getline(aFileStream, line); // e.g., "letter,rgb,weight"

    // Step 3: Read and store the color mappings
    while (std::getline(aFileStream, line) && !line.empty()) {
        if (line[0] == '_')
            break; // Break on the grid data section
        GridColor color = parseColor(line);
        colors.push_back(color);
    }

    // Step 4: Store the grid in a continuous char buffer, including underscores,
    // ignoring linefeeds
    gridBuffer.reserve(rows * cols); // Preallocate buffer size

    do {
        for (int i = 0; i < line.size() - 1; i++) {
            gridBuffer.push_back(line[i]);
        }
    } while (std::getline(aFileStream, line));

    ParsedGrid data;
    data.rows = rows;
    data.cols = cols;
    data.grid = gridBuffer;   // Copy grid buffer
    data.gridColors = colors; // Copy color mappings
    return data;
}

// // Single getter that returns all grid data in one struct
// GridData GridTXTParser::getGridData() const {
//     GridData data;
//     data.rows = rows;
//     data.cols = cols;
//     data.gridBuffer = gridBuffer; // Copy grid buffer
//     data.colors = colors;         // Copy color mappings
//     return data;
// }
