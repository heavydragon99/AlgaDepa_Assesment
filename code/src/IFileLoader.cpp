#include "IFileLoader.h"

/**
 * @brief Callback function for writing data received from CURL to a file.
 * 
 * @param contents Pointer to the data received.
 * @param size Size of each data element.
 * @param nmemb Number of data elements.
 * @param userp Pointer to the user data (in this case, an ofstream object).
 * @return size_t The total number of bytes written.
 */
size_t URLFileLoader::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    std::ofstream* ofs = static_cast<std::ofstream*>(userp);
    size_t totalSize = size * nmemb;
    ofs->write(static_cast<char*>(contents), totalSize);
    return totalSize;
}

/**
 * @brief Downloads a file from a given URL and returns a unique pointer to an ifstream object for reading the file.
 * 
 * @param url The URL of the file to download.
 * @return std::unique_ptr<std::ifstream> A unique pointer to an ifstream object for reading the downloaded file.
 */
std::unique_ptr<std::ifstream> URLFileLoader::loadFile(const std::string& url) {
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
            return nullptr;
        }
    } else {
        std::cerr << "Failed to initialize CURL." << std::endl;
        return nullptr;
    }

    ofs.close();

    auto fileStream = std::make_unique<std::ifstream>(tempFilename, std::ios::binary);
    if (!fileStream->is_open()) {
        std::cerr << "Failed to open downloaded file: " << tempFilename << std::endl;
        return nullptr;
    }
    return fileStream;
}

/**
 * @brief Loads a local file and returns a unique pointer to an ifstream object for reading the file.
 * 
 * @param path The path to the local file.
 * @return std::unique_ptr<std::ifstream> A unique pointer to an ifstream object for reading the local file.
 */
std::unique_ptr<std::ifstream> LocalFileLoader::loadFile(const std::string& path) {
    auto fileStream = std::make_unique<std::ifstream>(path, std::ios::binary);
    if (!fileStream->is_open()) {
        std::cerr << "Failed to open local file: " << path << std::endl;
        return nullptr;
    }
    return fileStream;
}