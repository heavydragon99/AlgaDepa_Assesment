#pragma once

#include <curl/curl.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

// Abstract class for loading files using C++ streams
class FileLoader {
public:
    virtual ~FileLoader() = default;
    virtual std::unique_ptr<std::ifstream> loadFile(const std::string& path) = 0;
};

// URL File Loader (downloads a file and returns an ifstream pointer)
class URLFileLoader : public FileLoader {
public:
    // Helper function to write downloaded data to a temporary file
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
        std::ofstream* ofs = static_cast<std::ofstream*>(userp);
        size_t totalSize = size * nmemb;
        ofs->write(static_cast<char*>(contents), totalSize);
        return totalSize;
    }

    std::unique_ptr<std::ifstream> loadFile(const std::string& url) override {
        std::string tempFilename = "downloaded_file.tmp";
        std::ofstream ofs(tempFilename, std::ios::binary);

        CURL* curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ofs);
            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) {
                std::cerr << "Error downloading file: " << curl_easy_strerror(res) << std::endl;
                return nullptr; // Return empty unique_ptr (no resource managed)
            }
        } else {
            std::cerr << "Failed to initialize CURL." << std::endl;
            return nullptr;
        }

        ofs.close();

        // Try opening the downloaded file as an ifstream
        auto fileStream = std::make_unique<std::ifstream>(tempFilename, std::ios::binary);
        if (!fileStream->is_open()) {
            std::cerr << "Failed to open downloaded file: " << tempFilename << std::endl;
            return nullptr;
        }
        return fileStream;
    }
};

// Local File Loader (opens a local file and returns an ifstream pointer)
class LocalFileLoader : public FileLoader {
public:
    std::unique_ptr<std::ifstream> loadFile(const std::string& path) override {
        // Open the local file as an ifstream
        auto fileStream = std::make_unique<std::ifstream>(path, std::ios::binary);
        if (!fileStream->is_open()) {
            std::cerr << "Failed to open local file: " << path << std::endl;
            return nullptr;
        }
        return fileStream;
    }
};

// Context class for selecting the appropriate file loading strategy
class FileLoaderContext {
public:
    std::unique_ptr<std::ifstream> loadFile(const std::string& path) {
        std::unique_ptr<FileLoader> loader;

        if (isURL(path)) {
            loader = std::make_unique<URLFileLoader>();
        } else {
            loader = std::make_unique<LocalFileLoader>();
        }

        // Return the loaded file stream (which could be empty if failed)
        return loader->loadFile(path);
    }

private:
    // Utility function to check if the path is a URL (rudimentary check)
    bool isURL(const std::string& path) { return path.rfind("http://", 0) == 0 || path.rfind("https://", 0) == 0; }
};
