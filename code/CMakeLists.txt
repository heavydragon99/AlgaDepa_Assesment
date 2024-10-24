cmake_minimum_required(VERSION 3.20)

# Set the project name
project(depaAlgo)

set(PROJECT_LIB ${PROJECT_NAME}_Lib)
set(PROJECT_TESTS ${PROJECT_NAME}_tests)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ensure the bin directory exists
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add source and include directories
include_directories(${PROJECT_SOURCE_DIR}/inc)
add_subdirectory(tests)

# Add subdirectory for TinyXML2
add_subdirectory(${CMAKE_SOURCE_DIR}/external/tinyxml2)

# Find SDL2 and CURL
find_package(SDL2 REQUIRED)
find_package(CURL REQUIRED)

# Include SDL2 and CURL directories
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${CURL_INCLUDE_DIRS})

# List all source files explicitly
set(SRC_FILES
    ${CMAKE_SOURCE_DIR}/src/Artist.cpp
    ${CMAKE_SOURCE_DIR}/src/ArtistParser.cpp
    ${CMAKE_SOURCE_DIR}/src/CollisionHandler.cpp
    ${CMAKE_SOURCE_DIR}/src/Controller.cpp
    ${CMAKE_SOURCE_DIR}/src/FileHandler.cpp
    ${CMAKE_SOURCE_DIR}/src/FileLoader.cpp
    ${CMAKE_SOURCE_DIR}/src/GridParser.cpp
    ${CMAKE_SOURCE_DIR}/src/IArtistParser.cpp
    ${CMAKE_SOURCE_DIR}/src/IFileLoader.cpp
    ${CMAKE_SOURCE_DIR}/src/IGridParser.cpp
    ${CMAKE_SOURCE_DIR}/src/Input.cpp
    ${CMAKE_SOURCE_DIR}/src/InputStructs.cpp
    ${CMAKE_SOURCE_DIR}/src/ITileState.cpp
    ${CMAKE_SOURCE_DIR}/src/LevelData.cpp
    ${CMAKE_SOURCE_DIR}/src/Memento.cpp
    ${CMAKE_SOURCE_DIR}/src/MementoManager.cpp
    ${CMAKE_SOURCE_DIR}/src/Model.cpp
    ${CMAKE_SOURCE_DIR}/src/Pathfinder.cpp
    ${CMAKE_SOURCE_DIR}/src/PollingTUI.cpp
    ${CMAKE_SOURCE_DIR}/src/Quadtree.cpp
    ${CMAKE_SOURCE_DIR}/src/Renderer.cpp
    ${CMAKE_SOURCE_DIR}/src/Tile.cpp
    ${CMAKE_SOURCE_DIR}/src/TileFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/TileNode.cpp
    ${CMAKE_SOURCE_DIR}/src/View.cpp
)

# Create a library from the source files
add_library(${PROJECT_LIB} STATIC ${SRC_FILES})

# Link libraries against own library
target_link_libraries(${PROJECT_LIB} PRIVATE tinyxml2 ${CURL_LIBRARIES} ${SDL2_LIBRARIES})

# Define executable for main application
add_executable(${PROJECT_NAME} src/Main.cpp)

# Link libraries against application
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_LIB})

# Enable testing
enable_testing()

# Add custom target to run the main program
add_custom_target(run
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMENT "Running the main program"
)

# Add custom target to run Valgrind
add_custom_target(run_valgrind
COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --gen-suppressions=all --suppressions=${CMAKE_SOURCE_DIR}/valgrind.supp ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} 
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMENT "Running Valgrind to check for memory leaks"
)

# Add custom target to run the program with debug information
add_custom_target(run_debug
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMENT "Running the main program with debug information"
)

# Option to enable debug mode
option(ENABLE_DEBUG "Enable debug mode" OFF)

if(ENABLE_DEBUG)
    # Set build type to Debug if not already set
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Debug)
    endif()
    # Add debug flags
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
endif()