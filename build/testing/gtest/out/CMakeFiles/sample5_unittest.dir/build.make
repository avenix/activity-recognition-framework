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
include CMakeFiles/sample5_unittest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sample5_unittest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sample5_unittest.dir/flags.make

CMakeFiles/sample5_unittest.dir/samples/sample5_unittest.cc.o: CMakeFiles/sample5_unittest.dir/flags.make
CMakeFiles/sample5_unittest.dir/samples/sample5_unittest.cc.o: ../samples/sample5_unittest.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/avenix/Desktop/xcode-googletest-master/Dependencies/gtest/gtestOut/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sample5_unittest.dir/samples/sample5_unittest.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sample5_unittest.dir/samples/sample5_unittest.cc.o -c /Users/avenix/Desktop/xcode-googletest-master/Dependencies/gtest/samples/sample5_unittest.cc

CMakeFiles/sample5_unittest.dir/samples/sample5_unittest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sample5_unittest.dir/samples/sample5_unittest.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/avenix/Desktop/xcode-googletest-master/Dependencies/gtest/samples/sample5_unittest.cc > CMakeFiles/sample5_unittest.dir/samples/sample5_unittest.cc.i

CMakeFiles/sample5_unittest.dir/samples/sample5_unittest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sample5_unittest.dir/samples/sample5_unittest.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/avenix/Desktop/xcode-googletest-master/Dependencies/gtest/samples/sample5_unittest.cc -o CMakeFiles/sample5_unittest.dir/samples/sample5_unittest.cc.s

CMakeFiles/sample5_unittest.dir/samples/sample1.cc.o: CMakeFiles/sample5_unittest.dir/flags.make
CMakeFiles/sample5_unittest.dir/samples/sample1.cc.o: ../samples/sample1.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/avenix/Desktop/xcode-googletest-master/Dependencies/gtest/gtestOut/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/sample5_unittest.dir/samples/sample1.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sample5_unittest.dir/samples/sample1.cc.o -c /Users/avenix/Desktop/xcode-googletest-master/Dependencies/gtest/samples/sample1.cc

CMakeFiles/sample5_unittest.dir/samples/sample1.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sample5_unittest.dir/samples/sample1.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/avenix/Desktop/xcode-googletest-master/Dependencies/gtest/samples/sample1.cc > CMakeFiles/sample5_unittest.dir/samples/sample1.cc.i

CMakeFiles/sample5_unittest.dir/samples/sample1.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sample5_unittest.dir/samples/sample1.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/avenix/Desktop/xcode-googletest-master/Dependencies/gtest/samples/sample1.cc -o CMakeFiles/sample5_unittest.dir/samples/sample1.cc.s

# Object files for target sample5_unittest
sample5_unittest_OBJECTS = \
"CMakeFiles/sample5_unittest.dir/samples/sample5_unittest.cc.o" \
"CMakeFiles/sample5_unittest.dir/samples/sample1.cc.o"

# External object files for target sample5_unittest
sample5_unittest_EXTERNAL_OBJECTS =

sample5_unittest: CMakeFiles/sample5_unittest.dir/samples/sample5_unittest.cc.o
sample5_unittest: CMakeFiles/sample5_unittest.dir/samples/sample1.cc.o
sample5_unittest: CMakeFiles/sample5_unittest.dir/build.make
sample5_unittest: lib/libgtest_main.a
sample5_unittest: lib/libgtest.a
sample5_unittest: CMakeFiles/sample5_unittest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/avenix/Desktop/xcode-googletest-master/Dependencies/gtest/gtestOut/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable sample5_unittest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sample5_unittest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sample5_unittest.dir/build: sample5_unittest

.PHONY : CMakeFiles/sample5_unittest.dir/build

CMakeFiles/sample5_unittest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sample5_unittest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sample5_unittest.dir/clean

CMakeFiles/sample5_unittest.dir/depend:
	cd /Users/avenix/Desktop/xcode-googletest-master/Dependencies/gtest/gtestOut && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/avenix/Desktop/xcode-googletest-master/Dependencies/gtest /Users/avenix/Desktop/xcode-googletest-master/Dependencies/gtest /Users/avenix/Desktop/xcode-googletest-master/Dependencies/gtest/gtestOut /Users/avenix/Desktop/xcode-googletest-master/Dependencies/gtest/gtestOut /Users/avenix/Desktop/xcode-googletest-master/Dependencies/gtest/gtestOut/CMakeFiles/sample5_unittest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sample5_unittest.dir/depend

