# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /Library/Frameworks/Python.framework/Versions/3.7/lib/python3.7/site-packages/cmake/data/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Library/Frameworks/Python.framework/Versions/3.7/lib/python3.7/site-packages/cmake/data/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic

# Include any dependencies generated for this target.
include lib/Alembic/AbcGeom/Tests/CMakeFiles/AbcGeom_PointsTest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/Alembic/AbcGeom/Tests/CMakeFiles/AbcGeom_PointsTest.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/Alembic/AbcGeom/Tests/CMakeFiles/AbcGeom_PointsTest.dir/progress.make

# Include the compile flags for this target's objects.
include lib/Alembic/AbcGeom/Tests/CMakeFiles/AbcGeom_PointsTest.dir/flags.make

lib/Alembic/AbcGeom/Tests/CMakeFiles/AbcGeom_PointsTest.dir/PointsTest.cpp.o: lib/Alembic/AbcGeom/Tests/CMakeFiles/AbcGeom_PointsTest.dir/flags.make
lib/Alembic/AbcGeom/Tests/CMakeFiles/AbcGeom_PointsTest.dir/PointsTest.cpp.o: /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/Tests/PointsTest.cpp
lib/Alembic/AbcGeom/Tests/CMakeFiles/AbcGeom_PointsTest.dir/PointsTest.cpp.o: lib/Alembic/AbcGeom/Tests/CMakeFiles/AbcGeom_PointsTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/Alembic/AbcGeom/Tests/CMakeFiles/AbcGeom_PointsTest.dir/PointsTest.cpp.o"
	cd /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/AbcGeom/Tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/Alembic/AbcGeom/Tests/CMakeFiles/AbcGeom_PointsTest.dir/PointsTest.cpp.o -MF CMakeFiles/AbcGeom_PointsTest.dir/PointsTest.cpp.o.d -o CMakeFiles/AbcGeom_PointsTest.dir/PointsTest.cpp.o -c /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/Tests/PointsTest.cpp

lib/Alembic/AbcGeom/Tests/CMakeFiles/AbcGeom_PointsTest.dir/PointsTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AbcGeom_PointsTest.dir/PointsTest.cpp.i"
	cd /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/AbcGeom/Tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/Tests/PointsTest.cpp > CMakeFiles/AbcGeom_PointsTest.dir/PointsTest.cpp.i

lib/Alembic/AbcGeom/Tests/CMakeFiles/AbcGeom_PointsTest.dir/PointsTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AbcGeom_PointsTest.dir/PointsTest.cpp.s"
	cd /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/AbcGeom/Tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/Tests/PointsTest.cpp -o CMakeFiles/AbcGeom_PointsTest.dir/PointsTest.cpp.s

# Object files for target AbcGeom_PointsTest
AbcGeom_PointsTest_OBJECTS = \
"CMakeFiles/AbcGeom_PointsTest.dir/PointsTest.cpp.o"

# External object files for target AbcGeom_PointsTest
AbcGeom_PointsTest_EXTERNAL_OBJECTS =

lib/Alembic/AbcGeom/Tests/AbcGeom_PointsTest: lib/Alembic/AbcGeom/Tests/CMakeFiles/AbcGeom_PointsTest.dir/PointsTest.cpp.o
lib/Alembic/AbcGeom/Tests/AbcGeom_PointsTest: lib/Alembic/AbcGeom/Tests/CMakeFiles/AbcGeom_PointsTest.dir/build.make
lib/Alembic/AbcGeom/Tests/AbcGeom_PointsTest: lib/Alembic/libAlembic.a
lib/Alembic/AbcGeom/Tests/AbcGeom_PointsTest: /usr/local/lib/libImath-3_1.29.4.0.dylib
lib/Alembic/AbcGeom/Tests/AbcGeom_PointsTest: lib/Alembic/AbcGeom/Tests/CMakeFiles/AbcGeom_PointsTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable AbcGeom_PointsTest"
	cd /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/AbcGeom/Tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AbcGeom_PointsTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/Alembic/AbcGeom/Tests/CMakeFiles/AbcGeom_PointsTest.dir/build: lib/Alembic/AbcGeom/Tests/AbcGeom_PointsTest
.PHONY : lib/Alembic/AbcGeom/Tests/CMakeFiles/AbcGeom_PointsTest.dir/build

lib/Alembic/AbcGeom/Tests/CMakeFiles/AbcGeom_PointsTest.dir/clean:
	cd /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/AbcGeom/Tests && $(CMAKE_COMMAND) -P CMakeFiles/AbcGeom_PointsTest.dir/cmake_clean.cmake
.PHONY : lib/Alembic/AbcGeom/Tests/CMakeFiles/AbcGeom_PointsTest.dir/clean

lib/Alembic/AbcGeom/Tests/CMakeFiles/AbcGeom_PointsTest.dir/depend:
	cd /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/AbcGeom/Tests /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/AbcGeom/Tests /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/AbcGeom/Tests/CMakeFiles/AbcGeom_PointsTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/Alembic/AbcGeom/Tests/CMakeFiles/AbcGeom_PointsTest.dir/depend

