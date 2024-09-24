#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "ArtistParserStrategy.h"

// class ArtistCSVParser : public ArtistParser {
// public:
//     ArtistCSVParser(const std::string& filename) { parseFile(filename); }
//
//     std::vector<ArtistData> getArtistsData() const { return artistsData; }
//
// private:
//     std::vector<ArtistData> artistsData;
//
//     void parseFile(const std::string& filename) {
//         std::ifstream file(filename);
//         if (!file.is_open()) {
//             std::cerr << "Failed to open file: " << filename << std::endl;
//             return;
//         }
//
//         std::string line;
//         // Skip the header line
//         std::getline(file, line);
//
//         while (std::getline(file, line)) {
//             std::stringstream ss(line);
//             ArtistData artist;
//             char comma;
//
//             ss >> artist.x >> comma >> artist.y >> comma >> artist.vx >> comma >> artist.vy;
//
//             if (ss.fail()) {
//                 std::cerr << "Error parsing line: " << line << std::endl;
//                 continue;
//             }
//
//             artistsData.push_back(artist);
//         }
//
//         file.close();
//     }
// };
