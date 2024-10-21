#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <unordered_map>

class Configuration {
public:
    static Configuration& getInstance() {
        static Configuration instance;
        return instance;
    }

    // Delete copy constructor and assignment operator to prevent copies
    Configuration(const Configuration&) = delete;
    Configuration& operator=(const Configuration&) = delete;

    // Configuration methods
    void setConfig(const std::string& key, bool value) {
        configs[key] = value;
    }

    bool getConfig(const std::string& key) const {
        auto it = configs.find(key);
        if (it != configs.end()) {
            return it->second;
        }
        return false; // Default value if key not found
    }

private:
    Configuration() {} // Private constructor

    std::unordered_map<std::string, bool> configs;
};

#endif // CONFIGURATION_H