#include "FileLoader.h"

#include <iostream>

/**
 * @brief Loads a file from the given path.
 * 
 * This function determines whether the path is a URL or a local file path,
 * and uses the appropriate loader to load the file.
 * 
 * @param path The path to the file, which can be a URL or a local file path.
 * @return std::unique_ptr<std::ifstream> A unique pointer to the loaded file stream.
 */
std::unique_ptr<std::ifstream> FileLoader::loadFile(const std::string& path) {
    std::unique_ptr<IFileLoader> loader;

    if (isURL(path)) {
        std::cout << path << " is a URL" << std::endl;
        loader = std::make_unique<URLFileLoader>();
    } else {
        std::cout << path << " is not a URL" << std::endl;
        loader = std::make_unique<LocalFileLoader>();
    }

    // Return the loaded file stream (which could be empty if failed)
    return loader->loadFile(path);
}

/**
 * @brief Checks if the given path is a URL.
 * 
 * This function checks if the path starts with "http://" or "https://".
 * 
 * @param path The path to check.
 * @return true If the path is a URL.
 * @return false If the path is not a URL.
 */
bool FileLoader::isURL(const std::string& path) {
    return path.rfind("http://", 0) == 0 || path.rfind("https://", 0) == 0;
}