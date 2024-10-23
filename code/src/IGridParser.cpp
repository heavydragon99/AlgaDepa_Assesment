#include "IGridParser.h"
#include <fstream>
#include <iostream>
#include <sstream>

#include "Structs.h"

/**
 * @brief Unimplemented method to parse a CSV grid file.
 * 
 * @param aFileStream The input file stream containing the grid data.
 * @return ParsedGrid The parsed grid data.
 */
ParsedGrid GridCSVParser::parseFile(std::ifstream& aFileStream) {
    ParsedGrid gridData;
    std::cout << "CSV grid loading not implemented" << std::endl;
    return gridData;
}

/**
 * @brief Parses a color line in the format "Y,[250,201,1],1".
 * 
 * @param line The line containing the color information.
 * @return GridColor The parsed color information.
 */
GridColor GridTXTParser::parseColor(const std::string& line) const {
    GridColor color;
    std::stringstream ss(line);
    char ignore, comma;

    ss >> color.letter;         // letter
    ss >> ignore >> ignore;     // "["
    ss >> color.red >> comma;   // red value
    ss >> color.green >> comma; // green value
    ss >> color.blue >> ignore; // blue value
    ss >> ignore;               // "]"
    ss >> color.weight;         // weight

    return color;
}

/**
 * @brief Parses the grid file and stores the data.
 * 
 * @param aFileStream The input file stream containing the grid data.
 * @return ParsedGrid The parsed grid data.
 */
ParsedGrid GridTXTParser::parseFile(std::ifstream& aFileStream) {
    int rows, cols;
    std::vector<GridColor> colors;
    std::vector<char> gridBuffer;

    if (!aFileStream.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return ParsedGrid();
    }

    std::string line;

    // Step 1: Read grid dimensions
    std::getline(aFileStream, line); // e.g., "rows=53,cols=53"
    sscanf(line.c_str(), "rows=%d,cols=%d", &rows, &cols);

    // Step 2: Read the color mapping header
    std::getline(aFileStream, line); // e.g., "letter,rgb,weight"

    // Step 3: Read and store the color mappings
    while (std::getline(aFileStream, line) && !line.empty()) {
        if (line[0] == '_')
            break; // Break on the grid data section
        GridColor color = parseColor(line);
        colors.push_back(color);
    }

    // Step 4: Store the grid in a continuous char buffer, including underscores,
    // ignoring linefeeds
    gridBuffer.reserve(rows * cols); // Preallocate buffer size

    do {
        for (int i = 0; i < line.size() - 1; i++) {
            gridBuffer.push_back(line[i]);
        }
    } while (std::getline(aFileStream, line));

    ParsedGrid data;
    data.rows = rows;
    data.cols = cols;
    data.grid = gridBuffer;   // Copy grid buffer
    data.gridColors = colors; // Copy color mappings
    return data;
}

/**
 * @brief Parses the XML grid file and stores the data.
 * 
 * @param aFileStream The input file stream containing the XML grid data.
 * @return ParsedGrid The parsed grid data.
 * @throws std::runtime_error If the file cannot be opened or parsed.
 */
ParsedGrid GridXMLParser::parseFile(std::ifstream& aFileStream) {
    ParsedGrid gridData;

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

/**
 * @brief Helper function to parse <nodeTypes> and fill color information.
 * 
 * @param nodeTypesElement The XML element containing node types.
 * @param gridData The parsed grid data to be filled.
 */
void GridXMLParser::parseNodeTypes(tinyxml2::XMLElement* nodeTypesElement, ParsedGrid& gridData) {
    for (tinyxml2::XMLElement* nodeType = nodeTypesElement->FirstChildElement("nodeType"); nodeType != nullptr;
         nodeType = nodeType->NextSiblingElement("nodeType")) {

        GridColor color;
        color.letter = nodeType->Attribute("tag")[0];
        nodeType->QueryIntAttribute("red", &color.red);
        nodeType->QueryIntAttribute("green", &color.green);
        nodeType->QueryIntAttribute("blue", &color.blue);
        nodeType->QueryIntAttribute("weight", &color.weight);

        gridData.gridColors.push_back(color);
    }
}

/**
 * @brief Helper function to parse <nodes> and fill grid buffer information.
 * 
 * @param nodesElement The XML element containing nodes.
 * @param gridData The parsed grid data to be filled.
 */
void GridXMLParser::parseNodes(tinyxml2::XMLElement* nodesElement, ParsedGrid& gridData) {
    gridData.grid.resize(gridData.rows * gridData.cols, '_'); // Initialize with spaces

    for (tinyxml2::XMLElement* node = nodesElement->FirstChildElement(); node != nullptr;
         node = node->NextSiblingElement()) {

        const char* tag = node->Value(); // Get the node tag (Y, R, etc.)
        int x, y;
        node->QueryIntAttribute("x", &x);
        node->QueryIntAttribute("y", &y);

        // Place the tag in the corresponding position in the grid
        if (x < gridData.cols && y < gridData.rows) {
            gridData.grid[y * gridData.cols + x] = tag[0];
        }
    }
}