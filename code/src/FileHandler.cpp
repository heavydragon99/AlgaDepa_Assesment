#include "FileHandler.h"
#include "ArtistParserStrategy.h"
#include "FileLoader.h"
#include "GridParserStrategy.h"

FileHandler::FileHandler() {}

std::vector<ArtistData> FileHandler::loadArtist(std::string aFilePath) {

    FileLoaderContext fileLoader;
    std::unique_ptr<std::ifstream> filePointer = fileLoader.loadFile(aFilePath);

    LoadedFile loadedFile;
    loadedFile.fileType = getFileType(aFilePath);
    loadedFile.openedFile = std::move(filePointer);

    ArtistParserStrategy artistParser;

    std::vector<ArtistData> artistData = artistParser.parseFile(loadedFile);

    return artistData;
}
GridData FileHandler::loadGrid(std::string aFilePath) {

    FileLoaderContext fileLoader;
    std::unique_ptr<std::ifstream> filePointer = fileLoader.loadFile(aFilePath);

    LoadedFile loadedFile;
    loadedFile.fileType = getFileType(aFilePath);
    loadedFile.openedFile = std::move(filePointer);

    GridParserStrategy gridParser;

    GridData gridData = gridParser.parseFile(loadedFile);

    return gridData;
}

// Function to get the file type based on file extension
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
