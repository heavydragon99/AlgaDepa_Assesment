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

# Add the executable
add_executable(depaAlgo ${SOURCES})

# Set build type to Debug by default
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Specify compiler flags for debug configuration
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")