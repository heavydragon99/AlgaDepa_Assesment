#ifndef GRID_PARSER_H
#define GRID_PARSER_H

#include <memory>
#include <stdexcept>
#include <fstream>
#include "IGridParser.h"

/**
 * @class GridParser
 * @brief A class responsible for parsing grid files of various types.
 */
class GridParser {
public:
    std::unique_ptr<IGridParser> getParser(FileType fileType);

    ParsedGrid parseFile(LoadedFile& aLoadedFile);
};

#endif // GRID_PARSER_H