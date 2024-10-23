#ifndef IGRIDPARSER_H
#define IGRIDPARSER_H

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <tinyxml2.h>

#include "FileHandler.h"

/**
 * @brief Interface for grid parsers.
 */
class IGridParser {
public:
    virtual ~IGridParser() = default;

    /**
     * @brief Parses the grid file and stores the data.
     *
     * @param aFileStream The input file stream containing the grid data.
     * @return ParsedGrid The parsed grid data.
     */
    virtual ParsedGrid parseFile(std::ifstream& aFileStream) = 0;
};

/**
 * @brief Parser for CSV grid files.
 */
class GridCSVParser : public IGridParser {
public:
    GridCSVParser() {}
    ParsedGrid parseFile(std::ifstream& aFileStream) override;
};

/**
 * @brief Parser for TXT grid files.
 */
class GridTXTParser : public IGridParser {
public:
    ParsedGrid parseFile(std::ifstream& aFileStream);

private:
    GridColor parseColor(const std::string& line) const;
};

/**
 * @brief Parser for XML grid files.
 */
class GridXMLParser : public IGridParser {
public:
    ParsedGrid parseFile(std::ifstream& aFileStream) override;

private:
    void parseNodeTypes(tinyxml2::XMLElement* nodeTypesElement, ParsedGrid& gridData);
    void parseNodes(tinyxml2::XMLElement* nodesElement, ParsedGrid& gridData);
};

#endif // IGRIDPARSER_H
