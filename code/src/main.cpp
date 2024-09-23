#include <iostream>

#include "ParseArtists.h"
#include "ParseGrid.h"

void testParseGrid() {
  // Create ParseGrid object and parse the file
  ParseGrid gridParser("grid.txt");
  gridParser.parseFile();

  // Get all grid data in one struct
  GridData gridData = gridParser.getGridData();

  // Output grid size
  std::cout << "Rows: " << gridData.rows << ", Cols: " << gridData.cols
            << std::endl;

  // Output color mappings
  std::cout << "Color Mappings:" << std::endl;
  for (const auto &color : gridData.colors) {
    std::cout << "Letter: " << color.letter << " RGB: [" << color.r << ","
              << color.g << "," << color.b << "]" << " Weight: " << color.weight
              << std::endl;
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
  ParseArtists parser("artists.csv");
  const std::vector<ArtistData> &data = parser.getArtistsData();

  for (const auto &artist : data) {
    std::cout << "x: " << artist.x << ", y: " << artist.y
              << ", vx: " << artist.vx << ", vy: " << artist.vy << std::endl;
  }
}

int main() {
  testParseGrid();

  testParseArtists();

  return 0;
}
