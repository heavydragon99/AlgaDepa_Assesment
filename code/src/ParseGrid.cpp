#include "ParseGrid.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Constructor
ParseGrid::ParseGrid(const std::string &fileName)
    : fileName(fileName), rows(0), cols(0) {}

// Function to parse a color line like "Y,[250,201,1],1"
Color ParseGrid::parseColor(const std::string &line) const {
  Color color;
  std::stringstream ss(line);
  char ignore, comma;

  ss >> color.letter;      // letter
  ss >> ignore >> ignore;  // "["
  ss >> color.r >> comma;  // red value
  ss >> color.g >> comma;  // green value
  ss >> color.b >> ignore; // blue value
  ss >> ignore;            // "]"
  ss >> color.weight;      // weight

  return color;
}

// Function to parse the grid file and store the data
void ParseGrid::parseFile() {
  std::ifstream file(fileName);
  if (!file.is_open()) {
    std::cerr << "Failed to open the file." << std::endl;
    return;
  }

  std::string line;

  // Step 1: Read grid dimensions
  std::getline(file, line); // e.g., "rows=53,cols=53"
  sscanf(line.c_str(), "rows=%d,cols=%d", &rows, &cols);

  // Step 2: Read the color mapping header
  std::getline(file, line); // e.g., "letter,rgb,weight"

  // Step 3: Read and store the color mappings
  while (std::getline(file, line) && !line.empty()) {
    if (line[0] == '_')
      break; // Break on the grid data section
    Color color = parseColor(line);
    colors.push_back(color);
  }

  // Step 4: Store the grid in a continuous char buffer, including underscores,
  // ignoring linefeeds
  gridBuffer.reserve(rows * cols); // Preallocate buffer size

  do {
    for (char ch : line) {
      if (ch != '\n') { // Ignore linefeed character '\n' (this is implicit in
                        // getline)
        gridBuffer.push_back(
            ch); // Include underscores and any other valid characters
      }
    }
  } while (std::getline(file, line));

  file.close();
}

// Single getter that returns all grid data in one struct
GridData ParseGrid::getGridData() const {
  GridData data;
  data.rows = rows;
  data.cols = cols;
  data.gridBuffer = gridBuffer; // Copy grid buffer
  data.colors = colors;         // Copy color mappings
  return data;
}
