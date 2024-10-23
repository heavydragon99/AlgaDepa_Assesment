#ifndef IARTISTPARSER_H
#define IARTISTPARSER_H

#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>

#include "Structs.h"


/**
 * @brief Base class for all artist parsers.
 */
class IArtistParser {
public:
    virtual ~IArtistParser() = default;

    virtual std::vector<ParsedPerson> parseFile(std::ifstream& aFileStream) = 0;
};

/**
 * @brief Base class for all artist parsers.
 */
class ArtistCSVParser : public IArtistParser {
public:
    std::vector<ParsedPerson> parseFile(std::ifstream& aFileStream) override;
};

/**
 * @brief TXT parser for artist data.
 */
class ArtistTXTParser : public IArtistParser {
public:
    std::vector<ParsedPerson> parseFile(std::ifstream& fileStream) override;
};

/**
 * @brief XML parser for artist data.
 */
class ArtistXMLParser : public IArtistParser {
public:
    std::vector<ParsedPerson> parseFile(std::ifstream& fileStream) override;
};

#endif // IARTISTPARSER_H