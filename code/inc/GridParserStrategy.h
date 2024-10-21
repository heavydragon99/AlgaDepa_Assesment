#pragma once

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <tinyxml2.h> // Using TinyXML2 library for XML parsing

#include "FileHandler.h"

// Base class for all grid parsers
class GridParser {
public:
    virtual ~GridParser() = default;

    // Virtual method for parsing, to be overridden by derived parsers
    virtual ParsedGrid parseFile(std::ifstream& aFileStream) = 0;
};

// CSV Parser
class GridCSVParser : public GridParser {
public:
    GridCSVParser() {}

    ParsedGrid parseFile(std::ifstream& aFileStream) override {
        ParsedGrid gridData;
        std::cout << "CSV grid loading not implemented" << std::endl;
        return gridData;
    }
};

class GridTXTParser : public GridParser {
public:
    // Function to parse file and return GridData
    ParsedGrid parseFile(std::ifstream& aFileStream);

private:
    // Helper function to parse a color line
    GridColor parseColor(const std::string& line) const;
};

// GridXMLParser to parse grid data from an XML file
class GridXMLParser : public GridParser {
public:
    ParsedGrid parseFile(std::ifstream& aFileStream) override;

private:
    // Helper function to parse <nodeTypes> and fill color information
    void parseNodeTypes(tinyxml2::XMLElement* nodeTypesElement, ParsedGrid& gridData);

    // Helper function to parse <nodes> and fill grid buffer information
    void parseNodes(tinyxml2::XMLElement* nodesElement, ParsedGrid& gridData);
};

// Strategy class that selects the appropriate grid parser based on file type
class GridParserStrategy {
public:
    // Method to get the appropriate parser based on file type
    std::unique_ptr<GridParser> getParser(FileType fileType) {
        switch (fileType) {
        case FileType::CSV:
            return std::make_unique<GridCSVParser>();
        case FileType::TXT:
            return std::make_unique<GridTXTParser>();
        case FileType::XML:
            return std::make_unique<GridXMLParser>();
        default:
            throw std::invalid_argument("Unsupported file type");
        }
    }

    // Method to load and parse the file
    ParsedGrid parseFile(LoadedFile& aLoadedFile) {
        std::ifstream& fileStream = *(aLoadedFile.openedFile);
        if (!fileStream.is_open()) {
            throw std::runtime_error("Failed to open file in grid parsing");
        }

        // Get the appropriate parser for the file type
        auto parser = getParser(aLoadedFile.fileType);

        // Parse the file using the selected parser
        return parser->parseFile(fileStream);
    }
};
