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

// // Define a struct to hold grid data (replace with your actual structure)
// struct GridData {
//     int rows;
//     int columns;
//     std::vector<std::vector<int>> gridValues; // Assuming a grid of integers
// };

// Base class for all grid parsers
class GridParser {
public:
    virtual ~GridParser() = default;

    // Virtual method for parsing, to be overridden by derived parsers
    virtual GridData parseFile(std::ifstream& aFileStream) = 0;
};

// CSV Parser
class GridCSVParser : public GridParser {
public:
    GridCSVParser() {}

    GridData parseFile(std::ifstream& aFileStream) override {
        GridData gridData;
        std::cout << "CSV grid loading not implemented" << std::endl;
        return gridData;
    }
};

// // TXT Parser
// class GridTXTParser : public GridParser {
// public:
//     GridData parseFile(std::ifstream& fileStream) override {
//         GridData gridData;
//         std::cout << "CSV grid loading not implemented" << std::endl;
//         return gridData;
//     }
// };
class GridTXTParser : public GridParser {
public:
    // Function to parse file and return GridData
    GridData parseFile(std::ifstream& aFileStream);

private:
    // Helper function to parse a color line
    Color parseColor(const std::string& line) const;
};

// XML Parser (placeholder, implement XML parsing logic)
// class GridXMLParser : public GridParser {
// public:
//     GridData parseFile(std::ifstream& aFileStream) override {
//         GridData gridData;
//         std::cout << "XML grid parsing not implemented" << std::endl;
//         return gridData;
//     }
// };
// GridXMLParser to parse grid data from an XML file
class GridXMLParser : public GridParser {
public:
    GridData parseFile(std::ifstream& aFileStream) override {
        GridData gridData;

        // Check if the file stream is open
        if (!aFileStream.is_open()) {
            throw std::runtime_error("Failed to open XML file");
        }

        // Convert the file stream to a string
        std::string xmlContent((std::istreambuf_iterator<char>(aFileStream)), std::istreambuf_iterator<char>());

        // Parse the XML content using TinyXML2
        tinyxml2::XMLDocument doc;
        tinyxml2::XMLError error = doc.Parse(xmlContent.c_str());
        if (error != tinyxml2::XML_SUCCESS) {
            throw std::runtime_error("Failed to parse XML file");
        }

        // Parse the <canvas> element to extract rows and cols
        tinyxml2::XMLElement* canvasElement = doc.FirstChildElement("canvas");
        if (canvasElement == nullptr) {
            throw std::runtime_error("Missing <canvas> element in XML");
        }

        canvasElement->QueryIntAttribute("rows", &gridData.rows);
        canvasElement->QueryIntAttribute("cols", &gridData.cols);

        // Parse <nodeTypes> to extract color information
        tinyxml2::XMLElement* nodeTypesElement = canvasElement->FirstChildElement("nodeTypes");
        if (nodeTypesElement != nullptr) {
            parseNodeTypes(nodeTypesElement, gridData);
        }

        // Parse <nodes> to extract grid data
        tinyxml2::XMLElement* nodesElement = canvasElement->FirstChildElement("nodes");
        if (nodesElement != nullptr) {
            parseNodes(nodesElement, gridData);
        }

        return gridData;
    }

private:
    // Helper function to parse <nodeTypes> and fill color information
    void parseNodeTypes(tinyxml2::XMLElement* nodeTypesElement, GridData& gridData) {
        for (tinyxml2::XMLElement* nodeType = nodeTypesElement->FirstChildElement("nodeType"); nodeType != nullptr;
             nodeType = nodeType->NextSiblingElement("nodeType")) {

            Color color;
            color.letter = nodeType->Attribute("tag")[0];
            nodeType->QueryIntAttribute("red", &color.r);
            nodeType->QueryIntAttribute("green", &color.g);
            nodeType->QueryIntAttribute("blue", &color.b);
            nodeType->QueryIntAttribute("weight", &color.weight);

            gridData.colors.push_back(color);
        }
    }

    // Helper function to parse <nodes> and fill grid buffer information
    void parseNodes(tinyxml2::XMLElement* nodesElement, GridData& gridData) {
        gridData.gridBuffer.resize(gridData.rows * gridData.cols, '_'); // Initialize with spaces

        for (tinyxml2::XMLElement* node = nodesElement->FirstChildElement(); node != nullptr;
             node = node->NextSiblingElement()) {

            const char* tag = node->Value(); // Get the node tag (Y, R, etc.)
            int x, y;
            node->QueryIntAttribute("x", &x);
            node->QueryIntAttribute("y", &y);

            // Place the tag in the corresponding position in the grid
            if (x < gridData.cols && y < gridData.rows) {
                gridData.gridBuffer[y * gridData.cols + x] = tag[0];
            }
        }
    }
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
    GridData parseFile(LoadedFile& aLoadedFile) {
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
