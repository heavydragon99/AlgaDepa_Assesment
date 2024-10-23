cmake_minimum_required(VERSION 3.20)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find and link GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Include directories for the main project
include_directories(${CMAKE_SOURCE_DIR}/inc)

# List all test source files explicitly
set(TEST_SOURCES
    ${CMAKE_SOURCE_DIR}/tests/test_ITileBehavior.cpp
    ${CMAKE_SOURCE_DIR}/tests/tests.cpp
    # Add other test files as needed
)

# Add the test executable
add_executable(${PROJECT_TESTS} ${TEST_SOURCES} ${SRC_FILES})

# Link GTest libraries
target_link_libraries(${PROJECT_TESTS} PRIVATE ${PROJECT_LIB} GTest::GTest GTest::Main tinyxml2 ${CURL_LIBRARIES} ${SDL2_LIBRARIES})


# Add custom target to run the tests
add_custom_target(run_tests
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}_tests
    DEPENDS ${PROJECT_NAME}_tests
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMENT "Running the tests"
)
