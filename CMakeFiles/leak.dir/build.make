# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/nakhoadl/workspace/foodtiny/native

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nakhoadl/workspace/foodtiny/native

# Utility rule file for leak.

# Include the progress variables for this target.
include CMakeFiles/leak.dir/progress.make

CMakeFiles/leak:
	valgrind --track-origins=yes --error-exitcode=2 --leak-check=full ./native_test

leak: CMakeFiles/leak
leak: CMakeFiles/leak.dir/build.make

.PHONY : leak

# Rule to build all files generated by this target.
CMakeFiles/leak.dir/build: leak

.PHONY : CMakeFiles/leak.dir/build

CMakeFiles/leak.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/leak.dir/cmake_clean.cmake
.PHONY : CMakeFiles/leak.dir/clean

CMakeFiles/leak.dir/depend:
	cd /home/nakhoadl/workspace/foodtiny/native && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nakhoadl/workspace/foodtiny/native /home/nakhoadl/workspace/foodtiny/native /home/nakhoadl/workspace/foodtiny/native /home/nakhoadl/workspace/foodtiny/native /home/nakhoadl/workspace/foodtiny/native/CMakeFiles/leak.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/leak.dir/depend

