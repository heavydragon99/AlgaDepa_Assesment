#include "FileHandler.h"
#include "controller.h"

#include <vector>

int main() {

    // yay text
    FileHandler fileHandler;

    ParsedGrid grid = fileHandler.loadGrid("graph.xml");
    std::vector<ParsedPerson> persons = fileHandler.loadArtist("artists.csv");
    int cols = grid.cols; // specify the number of columns
    int rows = grid.rows; // specify the number of rows

    Controller ctrl(persons, grid);
    ctrl.createLevel();
    ctrl.run();

    return 0;
}
