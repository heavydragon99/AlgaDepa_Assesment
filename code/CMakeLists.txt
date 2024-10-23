cmake_minimum_required(VERSION 3.20)

# Set the project name
project(depaAlgo)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ensure the bin directory exists
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include common settings
include(${CMAKE_SOURCE_DIR}/common.cmake)

# Find SDL2
find_package(SDL2 REQUIRED)

# Find the CURL package
find_package(CURL REQUIRED)

# Add subdirectory for TinyXML2
add_subdirectory(${CMAKE_SOURCE_DIR}/external/tinyxml2)

# Add the executable
add_executable(${PROJECT_NAME} ${MAIN_SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/inc ${SDL2_INCLUDE_DIRS})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE tinyxml2 CURL::libcurl ${SDL2_LIBRARIES})

# Add subdirectory for tests
add_subdirectory(tests)

# Add custom target to run the main program
add_custom_target(run
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMENT "Running the main program"
)

# Add custom target to run Valgrind
add_custom_target(run_valgrind
    COMMAND valgrind --leak-check=full --show-leak-kinds=all ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} # --track-origins=yes 
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