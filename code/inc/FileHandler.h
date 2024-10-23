#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <vector>

#include "FileLoader.h"
#include "Structs.h"

/**
 * @brief Enum representing different file types.
 */
enum FileType { UNDEFINED, CSV, TXT, XML };

/**
 * @brief Struct representing a loaded file with its type.
 */
struct LoadedFile {
    std::unique_ptr<std::ifstream> openedFile;
    FileType fileType = UNDEFINED;
};

/**
 * @brief Class responsible for handling file operations.
 */
class FileHandler {
public:
    FileHandler();

    std::vector<ParsedPerson> loadArtist(std::string aFilePath);
    ParsedGrid loadGrid(std::string aFilePath);

private:
    FileType getFileType(std::string aFilePath);
};

#endif // FILEHANDLER_H
