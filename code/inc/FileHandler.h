#pragma once

#include <vector>

#include "FileLoader.h"
#include "structs.h"

enum FileType { UNDEFINED, CSV, TXT, XML };

struct LoadedFile {
    std::unique_ptr<std::ifstream> openedFile;
    FileType fileType = UNDEFINED;
};

class FileHandler {
public:
    FileHandler();

    std::vector<ParsedPerson> loadArtist(std::string aFilePath);
    ParsedGrid loadGrid(std::string aFilePath);

private:
    FileType getFileType(std::string aFilePath);
};
