#pragma once

#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "ArtistCSVParser.h"
#include "FileHandler.h"

#include "structs.h"

// Base class for all parsers
class ArtistParser {
public:
    virtual ~ArtistParser() = default;

    // Virtual method for parsing, to be overridden by derived parsers
    virtual std::vector<ParsedPerson> parseFile(std::ifstream& aFileStream) = 0;
};

class ArtistCSVParser : public ArtistParser {
public:
    ArtistCSVParser() {}

    std::vector<ParsedPerson> parseFile(std::ifstream& aFileStream) override {
        std::vector<ParsedPerson> artistsData;

        // std::ifstream file(filename);

        if (!aFileStream.is_open()) {
            std::cerr << "Failed to open file: ArtistCSParser" << std::endl;
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

private:
};
// // CSV Parser
// class ArtistCSVParser : public ArtistParser {
// public:
//     std::vector<ArtistData> parseFile(std::ifstream& fileStream) override {
//         std::cout << "Parsing CSV file..." << std::endl;
//         // Implement CSV parsing logic here
//         //
//         return std::vector<ArtistData>();
//     }
// };

// TXT Parser
class ArtistTXTParser : public ArtistParser {
public:
    std::vector<ParsedPerson> parseFile(std::ifstream& fileStream) override {
        std::cout << "Parsing TXT file..." << std::endl;
        // Implement TXT parsing logic here
        return std::vector<ParsedPerson>();
    }
};

// XML Parser
class ArtistXMLParser : public ArtistParser {
public:
    std::vector<ParsedPerson> parseFile(std::ifstream& fileStream) override {
        std::cout << "Parsing XML file..." << std::endl;
        // Implement XML parsing logic here
        return std::vector<ParsedPerson>();
    }
};

// ArtistParserStrategy class that selects the appropriate parser based on file type
class ArtistParserStrategy {
public:
    // Method to get the appropriate parser based on file type
    std::unique_ptr<ArtistParser> getParser(FileType fileType) {
        switch (fileType) {
        case FileType::CSV:
            return std::make_unique<ArtistCSVParser>();
        case FileType::TXT:
            return std::make_unique<ArtistTXTParser>();
        case FileType::XML:
            return std::make_unique<ArtistXMLParser>();
        default:
            throw std::invalid_argument("Unsupported file type");
        }
    }

    // Method to load and parse the file
    std::vector<ParsedPerson> parseFile(LoadedFile& aLoadedFile) {
        // Open the file
        std::ifstream& fileStream = *(aLoadedFile.openedFile);
        if (!fileStream.is_open()) {
            throw std::runtime_error("Failed to open file in artist parsing");
        }

        // Get the appropriate parser for the file type
        auto parser = getParser(aLoadedFile.fileType);

        // Parse the file using the selected parser
        return parser->parseFile(fileStream);
    }
};
