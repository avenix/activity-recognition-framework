# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.14.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.14.3/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/avenix/Desktop/xcode-googletest-master/Dependencies/gtest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/avenix/Desktop/xcode-googletest-master/Dependencies/gtest/gtestOut

# Include any dependencies generated for this target.
include CMakeFiles/sample10_unittest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sample10_unittest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sample10_unittest.dir/flags.make

CMakeFiles/sample10_unittest.dir/samples/sample10_unittest.cc.o: CMakeFiles/sample10_unittest.dir/flags.make
CMakeFiles/sample10_unittest.dir/samples/sample10_unittest.cc.o: ../samples/sample10_unittest.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/avenix/Desktop/xcode-googletest-master/Dependencies/gtest/gtestOut/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sample10_unittest.dir/samples/sample10_unittest.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sample10_unittest.dir/samples/sample10_unittest.cc.o -c /Users/avenix/Desktop/xcode-googletest-master/Dependencies/gtest/samples/sample10_unittest.cc

CMakeFiles/sample10_unittest.dir/samples/sample10_unittest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sample10_unittest.dir/samples/sample10_unittest.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/avenix/Desktop/xcode-googletest-master/Dependencies/gtest/samples/sample10_unittest.cc > CMakeFiles/sample10_unittest.dir/samples/sample10_unittest.cc.i

CMakeFiles/sample10_unittest.dir/samples/sample10_unittest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sample10_unittest.dir/samples/sample10_unittest.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/avenix/Desktop/xcode-googletest-master/Dependencies/gtest/samples/sample10_unittest.cc -o CMakeFiles/sample10_unittest.dir/samples/sample10_unittest.cc.s

# Object files for target sample10_unittest
sample10_unittest_OBJECTS = \
"CMakeFiles/sample10_unittest.dir/samples/sample10_unittest.cc.o"

# External object files for target sample10_unittest
sample10_unittest_EXTERNAL_OBJECTS =

sample10_unittest: CMakeFiles/sample10_unittest.dir/samples/sample10_unittest.cc.o
sample10_unittest: CMakeFiles/sample10_unittest.dir/build.make
sample10_unittest: lib/libgtest.a
sample10_unittest: CMakeFiles/sample10_unittest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/avenix/Desktop/xcode-googletest-master/Dependencies/gtest/gtestOut/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sample10_unittest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sample10_unittest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sample10_unittest.dir/build: sample10_unittest

.PHONY : CMakeFiles/sample10_unittest.dir/build

CMakeFiles/sample10_unittest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sample10_unittest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sample10_unittest.dir/clean

CMakeFiles/sample10_unittest.dir/depend:
	cd /Users/avenix/Desktop/xcode-googletest-master/Dependencies/gtest/gtestOut && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/avenix/Desktop/xcode-googletest-master/Dependencies/gtest /Users/avenix/Desktop/xcode-googletest-master/Dependencies/gtest /Users/avenix/Desktop/xcode-googletest-master/Dependencies/gtest/gtestOut /Users/avenix/Desktop/xcode-googletest-master/Dependencies/gtest/gtestOut /Users/avenix/Desktop/xcode-googletest-master/Dependencies/gtest/gtestOut/CMakeFiles/sample10_unittest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sample10_unittest.dir/depend

