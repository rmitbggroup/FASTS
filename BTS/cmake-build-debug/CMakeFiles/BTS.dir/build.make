# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/songsong945/CLionProjects/BTS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/songsong945/CLionProjects/BTS/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/BTS.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/BTS.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BTS.dir/flags.make

CMakeFiles/BTS.dir/BTS.cpp.o: CMakeFiles/BTS.dir/flags.make
CMakeFiles/BTS.dir/BTS.cpp.o: ../BTS.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/songsong945/CLionProjects/BTS/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/BTS.dir/BTS.cpp.o"
	/usr/local/Cellar/gcc@9/9.3.0/bin/g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BTS.dir/BTS.cpp.o -c /Users/songsong945/CLionProjects/BTS/BTS.cpp

CMakeFiles/BTS.dir/BTS.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BTS.dir/BTS.cpp.i"
	/usr/local/Cellar/gcc@9/9.3.0/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/songsong945/CLionProjects/BTS/BTS.cpp > CMakeFiles/BTS.dir/BTS.cpp.i

CMakeFiles/BTS.dir/BTS.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BTS.dir/BTS.cpp.s"
	/usr/local/Cellar/gcc@9/9.3.0/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/songsong945/CLionProjects/BTS/BTS.cpp -o CMakeFiles/BTS.dir/BTS.cpp.s

# Object files for target BTS
BTS_OBJECTS = \
"CMakeFiles/BTS.dir/BTS.cpp.o"

# External object files for target BTS
BTS_EXTERNAL_OBJECTS =

BTS: CMakeFiles/BTS.dir/BTS.cpp.o
BTS: CMakeFiles/BTS.dir/build.make
BTS: CMakeFiles/BTS.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/songsong945/CLionProjects/BTS/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable BTS"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BTS.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BTS.dir/build: BTS

.PHONY : CMakeFiles/BTS.dir/build

CMakeFiles/BTS.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BTS.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BTS.dir/clean

CMakeFiles/BTS.dir/depend:
	cd /Users/songsong945/CLionProjects/BTS/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/songsong945/CLionProjects/BTS /Users/songsong945/CLionProjects/BTS /Users/songsong945/CLionProjects/BTS/cmake-build-debug /Users/songsong945/CLionProjects/BTS/cmake-build-debug /Users/songsong945/CLionProjects/BTS/cmake-build-debug/CMakeFiles/BTS.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/BTS.dir/depend

