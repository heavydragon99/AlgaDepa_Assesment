#include "FileHandler.h"
#include "ArtistParser.h"
#include "FileLoader.h"
#include "GridParser.h"

FileHandler::FileHandler() {}

/**
 * @brief Determines if the file is likely an XML file based on the number of XML tags.
 * 
 * @param file A unique pointer to the file stream.
 * @param threshold The minimum number of tags to consider the file as XML.
 * @return true if the file is likely XML, false otherwise.
 */
bool isLikelyXML(std::unique_ptr<std::ifstream>& file, int threshold = 10) {
    if (!file->is_open()) {
        std::cerr << "Error: File stream is not open." << std::endl;
        return false;
    }

    std::string line;
    int tagCount = 0;

    while (std::getline(*file, line)) {
        // Count opening tags
        size_t pos = 0;
        while ((pos = line.find('<', pos)) != std::string::npos) {
            size_t endPos = line.find('>', pos);
            if (endPos != std::string::npos) {
                // Check if it is an opening tag
                if (line[pos + 1] != '/') {
                    tagCount++;
                }
                pos = endPos + 1;
            } else {
                break; // Malformed line, no closing tag found
            }
        }
    }

    file->clear();
    file->seekg(0);

    // Determine if the file is likely XML based on the tag count
    return tagCount >= threshold;
}

/**
 * @brief Loads artist data from the specified file path.
 * 
 * @param aFilePath The path to the file containing artist data.
 * @return A vector of ParsedPerson objects containing the artist data.
 */
std::vector<ParsedPerson> FileHandler::loadArtist(std::string aFilePath) {

    FileLoader fileLoader;
    std::unique_ptr<std::ifstream> filePointer = fileLoader.loadFile(aFilePath);

    LoadedFile loadedFile;
    loadedFile.fileType = getFileType(aFilePath);
    loadedFile.openedFile = std::move(filePointer);

    ArtistParser artistParser;

    std::vector<ParsedPerson> artistData = artistParser.parseFile(loadedFile);

    return artistData;
}

/**
 * @brief Loads grid data from the specified file path.
 * 
 * @param aFilePath The path to the file containing grid data.
 * @return A ParsedGrid object containing the grid data.
 */
ParsedGrid FileHandler::loadGrid(std::string aFilePath) {

    FileLoader fileLoader;
    std::unique_ptr<std::ifstream> filePointer = fileLoader.loadFile(aFilePath);

    LoadedFile loadedFile;
    loadedFile.fileType = getFileType(aFilePath);
    if (loadedFile.fileType == UNDEFINED) {
        if (isLikelyXML(filePointer)) {
            loadedFile.fileType = FileType::XML;
        } else {
            loadedFile.fileType = FileType::TXT;
        }
    }
    loadedFile.openedFile = std::move(filePointer);

    GridParser gridParser;

    ParsedGrid gridData = gridParser.parseFile(loadedFile);

    return gridData;
}

/**
 * @brief Determines the file type based on the file extension.
 * 
 * @param aFilePath The path to the file.
 * @return The FileType corresponding to the file extension.
 */
FileType FileHandler::getFileType(const std::string aFilePath) {
    // Find the position of the last dot '.' in the file path
    size_t dotPos = aFilePath.find_last_of('.');

    if (dotPos == std::string::npos) {
        // No dot found, return UNDEFINED
        return UNDEFINED;
    }

    // Extract the file extension and convert to lowercase
    std::string extension = aFilePath.substr(dotPos + 1);

    // Check the file extension and return the corresponding FileType
    if (extension == "csv") {
        return FileType::CSV;
    } else if (extension == "txt") {
        return FileType::TXT;
    } else if (extension == "xml") {
        return FileType::XML;
    } else {
        return FileType::UNDEFINED; // If the extension is not recognized
    }
}