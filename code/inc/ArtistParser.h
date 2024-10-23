#ifndef ARTISTPARSER_H
#define ARTISTPARSER_H

#include <memory>
#include <stdexcept>
#include "IArtistParser.h"
#include "FileHandler.h"

/**
 * @brief Strategy class for parsing artist files.
 */
class ArtistParser {
public:
    std::unique_ptr<IArtistParser> getParser(FileType fileType);
    std::vector<ParsedPerson> parseFile(LoadedFile& aLoadedFile);
};

#endif // ARTISTPARSERSTRATEGY_H