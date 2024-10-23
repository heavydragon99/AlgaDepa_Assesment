#include "IArtistParser.h"

/**
 * @brief Parses the given CSV file stream.
 * 
 * @param aFileStream The CSV file stream to parse.
 * @return A vector of parsed persons.
 */
std::vector<ParsedPerson> ArtistCSVParser::parseFile(std::ifstream& aFileStream) {
    std::vector<ParsedPerson> artistsData;

    if (!aFileStream.is_open()) {
        std::cerr << "Failed to open file: ArtistCSVParser" << std::endl;
        return std::vector<ParsedPerson>();
    }

    std::string line;
    // Skip the header line
    std::getline(aFileStream, line);

    while (std::getline(aFileStream, line)) {
        std::stringstream ss(line);
        ParsedPerson artist;
        char comma;

        ss >> artist.x >> comma >> artist.y >> comma >> artist.vx >> comma >> artist.vy;

        if (ss.fail()) {
            std::cerr << "Error parsing line: " << line << std::endl;
            continue;
        }

        artistsData.push_back(artist);
    }

    return artistsData;
}

/**
 * @brief Parses the given TXT file stream.
 * 
 * @param fileStream The TXT file stream to parse.
 * @return A vector of parsed persons.
 */
std::vector<ParsedPerson> ArtistTXTParser::parseFile(std::ifstream& fileStream) {
    std::cout << "Parsing TXT file..." << std::endl;
    // Implement TXT parsing logic here
    return std::vector<ParsedPerson>();
}

/**
 * @brief Parses the given XML file stream.
 * 
 * @param fileStream The XML file stream to parse.
 * @return A vector of parsed persons.
 */
std::vector<ParsedPerson> ArtistXMLParser::parseFile(std::ifstream& fileStream) {
    std::cout << "Parsing XML file..." << std::endl;
    // Implement XML parsing logic here
    return std::vector<ParsedPerson>();
}