cmake_minimum_required(VERSION 3.20)

# Set the project name
project(depaAlgo)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories
include_directories(inc)

# Find all source files in the src directory
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Find the CURL package
find_package(CURL REQUIRED)

add_subdirectory(external/tinyxml2)

# Add the executable
add_executable(depaAlgo ${SOURCES})

# Link the CURL library to your project
target_link_libraries(depaAlgo PRIVATE tinyxml2 CURL::libcurl)
