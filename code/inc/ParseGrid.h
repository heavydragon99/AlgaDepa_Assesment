#ifndef PARSEGRID_H
#define PARSEGRID_H

#include <map>
#include <string>
#include <vector>

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

class ParseGrid {
public:
  // Constructor that takes the file name
  ParseGrid(const std::string &fileName);

  // Function to parse the file and store data
  void parseFile();

  // Single getter that returns all grid data in one struct
  GridData getGridData() const;

private:
  std::string fileName;
  int rows, cols;
  std::vector<Color> colors;
  std::vector<char> gridBuffer;

  // Helper function to parse a color line
  Color parseColor(const std::string &line) const;
};

#endif
