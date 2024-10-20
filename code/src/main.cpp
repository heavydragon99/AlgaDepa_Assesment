#include "FileHandler.h"
#include "PollingTUI.h"
#include "Quadtree.h"
#include "controller.h"

#include <vector>

// const float COLLISION_THRESHOLD = 5.0f;
//
// bool isColliding(const Artist& a1, const Artist& a2) {
//     float dx = a1.getLocation().mX - a2.getLocation().mX;
//     float dy = a1.getLocation().mY - a2.getLocation().mY;
//     float distanceSquared = dx * dx + dy * dy;
//     return distanceSquared < COLLISION_THRESHOLD * COLLISION_THRESHOLD;
// }
//
// void checkCollisions(Quadtree& quadtree, std::vector<Artist>& artists) {
//     for (Artist& artist : artists) {
//         std::vector<Artist*> potentialCollisions;
//         quadtree.retrieve(potentialCollisions, &artist);
//
//         for (Artist* other : potentialCollisions) {
//             if (&artist != other && isColliding(artist, *other)) {
//                 artist.collidedOtherArtist();
//                 other->collidedOtherArtist();
//             }
//         }
//     }
// }
//
// int main() {
//     std::vector<Artist> artists;
//     Quadtree quadtree(0, 0, 0, 100, 100);
//
//     // Example: Adding artists to the list and quadtree
//     artists.emplace_back(Artist({10, 10}, 1, 1));
//     artists.emplace_back(Artist({20, 20}, -1, -1));
//
//     for (Artist& artist : artists) {
//         quadtree.insert(&artist);
//     }
//
//     checkCollisions(quadtree, artists);
//
//     return 0;
// }

int main() {
    // PollingTUI tui;
    //
    // while (true) {
    //     tui.update();
    //     SDL_Delay(50);
    // }

    // yay text
    FileHandler fileHandler;

    std::string urlgrid = "https://firebasestorage.googleapis.com/v0/b/dpa-files.appspot.com/o/grid.txt?alt=media";
    std::string urlgraph = "https://firebasestorage.googleapis.com/v0/b/dpa-files.appspot.com/o/graph.xml?alt=media";

    ParsedGrid grid = fileHandler.loadGrid(urlgraph);
    std::vector<ParsedPerson> persons = fileHandler.loadArtist("artists.csv");
    int cols = grid.cols; // specify the number of columns
    int rows = grid.rows; // specify the number of rows

    Controller ctrl(persons, grid);
    ctrl.createLevel();
    ctrl.run();

    return 0;
}
