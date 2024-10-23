#include "ArtistParser.h"

/**
 * @brief Gets the appropriate parser based on the file type.
 * 
 * @param fileType The type of the file.
 * @return A unique pointer to the appropriate parser.
 */
std::unique_ptr<IArtistParser> ArtistParser::getParser(FileType fileType) {
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

/**
 * @brief Loads and parses the given file.
 * 
 * @param aLoadedFile The loaded file to parse.
 * @return A vector of parsed persons.
 */
std::vector<ParsedPerson> ArtistParser::parseFile(LoadedFile& aLoadedFile) {
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