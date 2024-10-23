#include "GridParser.h"

/**
 * @brief Factory method to get the appropriate parser for the given file type.
 * 
 * @param fileType The type of the file to be parsed.
 * @return std::unique_ptr<IGridParser> A unique pointer to the appropriate parser.
 * @throws std::invalid_argument If the file type is unsupported.
 */
std::unique_ptr<IGridParser> GridParser::getParser(FileType fileType) {
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

/**
 * @brief Parses the given loaded file using the appropriate parser.
 * 
 * @param aLoadedFile The loaded file to be parsed.
 * @return ParsedGrid The parsed grid data.
 * @throws std::runtime_error If the file cannot be opened.
 */
ParsedGrid GridParser::parseFile(LoadedFile& aLoadedFile) {
    std::ifstream& fileStream = *(aLoadedFile.openedFile);
    if (!fileStream.is_open()) {
        throw std::runtime_error("Failed to open file in grid parsing");
    }

    // Get the appropriate parser for the file type
    auto parser = getParser(aLoadedFile.fileType);

    // Parse the file using the selected parser
    return parser->parseFile(fileStream);
}