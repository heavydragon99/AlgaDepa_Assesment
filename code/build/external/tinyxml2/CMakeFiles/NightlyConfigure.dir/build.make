# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/seger/projects/dpa/code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/seger/projects/dpa/code/build

# Utility rule file for NightlyConfigure.

# Include any custom commands dependencies for this target.
include external/tinyxml2/CMakeFiles/NightlyConfigure.dir/compiler_depend.make

# Include the progress variables for this target.
include external/tinyxml2/CMakeFiles/NightlyConfigure.dir/progress.make

external/tinyxml2/CMakeFiles/NightlyConfigure:
	cd /home/seger/projects/dpa/code/build/external/tinyxml2 && /usr/bin/ctest -D NightlyConfigure

NightlyConfigure: external/tinyxml2/CMakeFiles/NightlyConfigure
NightlyConfigure: external/tinyxml2/CMakeFiles/NightlyConfigure.dir/build.make
.PHONY : NightlyConfigure

# Rule to build all files generated by this target.
external/tinyxml2/CMakeFiles/NightlyConfigure.dir/build: NightlyConfigure
.PHONY : external/tinyxml2/CMakeFiles/NightlyConfigure.dir/build

external/tinyxml2/CMakeFiles/NightlyConfigure.dir/clean:
	cd /home/seger/projects/dpa/code/build/external/tinyxml2 && $(CMAKE_COMMAND) -P CMakeFiles/NightlyConfigure.dir/cmake_clean.cmake
.PHONY : external/tinyxml2/CMakeFiles/NightlyConfigure.dir/clean

external/tinyxml2/CMakeFiles/NightlyConfigure.dir/depend:
	cd /home/seger/projects/dpa/code/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/seger/projects/dpa/code /home/seger/projects/dpa/code/external/tinyxml2 /home/seger/projects/dpa/code/build /home/seger/projects/dpa/code/build/external/tinyxml2 /home/seger/projects/dpa/code/build/external/tinyxml2/CMakeFiles/NightlyConfigure.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : external/tinyxml2/CMakeFiles/NightlyConfigure.dir/depend

