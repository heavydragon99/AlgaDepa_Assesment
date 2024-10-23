#ifndef IFILELOADER_H
#define IFILELOADER_H

#include <curl/curl.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

/**
 * @brief Interface for file loaders.
 */
class IFileLoader {
public:
    virtual ~IFileLoader() = default;
    virtual std::unique_ptr<std::ifstream> loadFile(const std::string& path) = 0;
};

/**
 * @brief Class to load files from a URL.
 */
class URLFileLoader : public IFileLoader {
public:
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
    std::unique_ptr<std::ifstream> loadFile(const std::string& url) override;
};

/**
 * @brief Class to load files from the local filesystem.
 */
class LocalFileLoader : public IFileLoader {
public:
    std::unique_ptr<std::ifstream> loadFile(const std::string& path) override;
};

#endif // IFILELOADER_H