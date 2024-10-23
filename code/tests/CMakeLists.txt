cmake_minimum_required(VERSION 3.20)

# Set the project name
project(depaAlgoTests)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find GTest
find_package(GTest REQUIRED)

# Include directories
include_directories(${GTEST_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/inc)

# Include common settings
include(${CMAKE_SOURCE_DIR}/common.cmake)

# List all test source files explicitly
set(TEST_SOURCES
    ${CMAKE_SOURCE_DIR}/tests/temp.cpp
    ${CMAKE_SOURCE_DIR}/tests/tests.cpp
    # ${CMAKE_SOURCE_DIR}/tests/ArtistTest.cpp
    # ${CMAKE_SOURCE_DIR}/tests/ArtistParserTest.cpp
    # ${CMAKE_SOURCE_DIR}/tests/CollisionHandlerTest.cpp
    # ${CMAKE_SOURCE_DIR}/tests/ControllerTest.cpp
    # ${CMAKE_SOURCE_DIR}/tests/FileHandlerTest.cpp
    # ${CMAKE_SOURCE_DIR}/tests/FileLoaderTest.cpp
    # ${CMAKE_SOURCE_DIR}/tests/GridParserTest.cpp
    # ${CMAKE_SOURCE_DIR}/tests/InputTest.cpp
    # ${CMAKE_SOURCE_DIR}/tests/LevelDataTest.cpp
    # ${CMAKE_SOURCE_DIR}/tests/MainTest.cpp
    # ${CMAKE_SOURCE_DIR}/tests/MementoTest.cpp
    # ${CMAKE_SOURCE_DIR}/tests/MementoManagerTest.cpp
    # ${CMAKE_SOURCE_DIR}/tests/ModelTest.cpp
    # ${CMAKE_SOURCE_DIR}/tests/PathfinderTest.cpp
    # ${CMAKE_SOURCE_DIR}/tests/PollingTUITest.cpp
    # ${CMAKE_SOURCE_DIR}/tests/QuadtreeTest.cpp
    # ${CMAKE_SOURCE_DIR}/tests/RendererTest.cpp
    # ${CMAKE_SOURCE_DIR}/tests/TileTest.cpp
    # ${CMAKE_SOURCE_DIR}/tests/TileFactoryTest.cpp
    # ${CMAKE_SOURCE_DIR}/tests/TileNodeTest.cpp
    # ${CMAKE_SOURCE_DIR}/tests/ViewTest.cpp
)

# Add the test executable
add_executable(${PROJECT_NAME} ${TEST_SOURCES})

# Link GTest libraries
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::GTest GTest::Main)

# Add custom target to run the tests
add_custom_target(run_tests
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMENT "Running the tests"
)