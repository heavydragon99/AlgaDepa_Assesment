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

# Add an option to set the build type to Debug
# option(DEBUG_BUILD "Build with debug information" OFF)

# Specify compiler flags for debug configuration if DEBUG_BUILD is ON
# if(DEBUG_BUILD)
  set(CMAKE_BUILD_TYPE Debug)
  set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
# endif()

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Find the CURL package
find_package(CURL REQUIRED)

add_subdirectory(external/tinyxml2)

# Add the executable
add_executable(depaAlgo ${SOURCES})

target_link_libraries(depaAlgo PRIVATE tinyxml2 CURL::libcurl ${SDL2_LIBRARIES})

# Add a custom target to run Valgrind
add_custom_target(valgrind
    COMMAND valgrind --leak-check=full --track-origins=yes --show-reachable=yes $<TARGET_FILE:depaAlgo>
    DEPENDS depaAlgo
    COMMENT "Running Valgrind to check for memory leaks"
)