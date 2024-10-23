#ifndef FILELOADER_H
#define FILELOADER_H

#include "IFileLoader.h"
#include <memory>
#include <fstream>
#include <string>

/**
 * @brief Class for selecting the appropriate file loading strategy.
 */
class FileLoader {
public:
    std::unique_ptr<std::ifstream> loadFile(const std::string& path);

private:
    bool isURL(const std::string& path);
};

#endif // FILELOADER_H