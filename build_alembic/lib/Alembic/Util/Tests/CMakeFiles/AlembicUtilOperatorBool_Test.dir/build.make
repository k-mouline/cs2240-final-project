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
include lib/Alembic/Util/Tests/CMakeFiles/AlembicUtilOperatorBool_Test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/Alembic/Util/Tests/CMakeFiles/AlembicUtilOperatorBool_Test.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/Alembic/Util/Tests/CMakeFiles/AlembicUtilOperatorBool_Test.dir/progress.make

# Include the compile flags for this target's objects.
include lib/Alembic/Util/Tests/CMakeFiles/AlembicUtilOperatorBool_Test.dir/flags.make

lib/Alembic/Util/Tests/CMakeFiles/AlembicUtilOperatorBool_Test.dir/OperatorBoolTest.cpp.o: lib/Alembic/Util/Tests/CMakeFiles/AlembicUtilOperatorBool_Test.dir/flags.make
lib/Alembic/Util/Tests/CMakeFiles/AlembicUtilOperatorBool_Test.dir/OperatorBoolTest.cpp.o: /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Util/Tests/OperatorBoolTest.cpp
lib/Alembic/Util/Tests/CMakeFiles/AlembicUtilOperatorBool_Test.dir/OperatorBoolTest.cpp.o: lib/Alembic/Util/Tests/CMakeFiles/AlembicUtilOperatorBool_Test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/Alembic/Util/Tests/CMakeFiles/AlembicUtilOperatorBool_Test.dir/OperatorBoolTest.cpp.o"
	cd /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/Util/Tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/Alembic/Util/Tests/CMakeFiles/AlembicUtilOperatorBool_Test.dir/OperatorBoolTest.cpp.o -MF CMakeFiles/AlembicUtilOperatorBool_Test.dir/OperatorBoolTest.cpp.o.d -o CMakeFiles/AlembicUtilOperatorBool_Test.dir/OperatorBoolTest.cpp.o -c /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Util/Tests/OperatorBoolTest.cpp

lib/Alembic/Util/Tests/CMakeFiles/AlembicUtilOperatorBool_Test.dir/OperatorBoolTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AlembicUtilOperatorBool_Test.dir/OperatorBoolTest.cpp.i"
	cd /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/Util/Tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Util/Tests/OperatorBoolTest.cpp > CMakeFiles/AlembicUtilOperatorBool_Test.dir/OperatorBoolTest.cpp.i

lib/Alembic/Util/Tests/CMakeFiles/AlembicUtilOperatorBool_Test.dir/OperatorBoolTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AlembicUtilOperatorBool_Test.dir/OperatorBoolTest.cpp.s"
	cd /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/Util/Tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Util/Tests/OperatorBoolTest.cpp -o CMakeFiles/AlembicUtilOperatorBool_Test.dir/OperatorBoolTest.cpp.s

# Object files for target AlembicUtilOperatorBool_Test
AlembicUtilOperatorBool_Test_OBJECTS = \
"CMakeFiles/AlembicUtilOperatorBool_Test.dir/OperatorBoolTest.cpp.o"

# External object files for target AlembicUtilOperatorBool_Test
AlembicUtilOperatorBool_Test_EXTERNAL_OBJECTS =

lib/Alembic/Util/Tests/AlembicUtilOperatorBool_Test: lib/Alembic/Util/Tests/CMakeFiles/AlembicUtilOperatorBool_Test.dir/OperatorBoolTest.cpp.o
lib/Alembic/Util/Tests/AlembicUtilOperatorBool_Test: lib/Alembic/Util/Tests/CMakeFiles/AlembicUtilOperatorBool_Test.dir/build.make
lib/Alembic/Util/Tests/AlembicUtilOperatorBool_Test: lib/Alembic/libAlembic.a
lib/Alembic/Util/Tests/AlembicUtilOperatorBool_Test: /usr/local/lib/libImath-3_1.29.4.0.dylib
lib/Alembic/Util/Tests/AlembicUtilOperatorBool_Test: lib/Alembic/Util/Tests/CMakeFiles/AlembicUtilOperatorBool_Test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable AlembicUtilOperatorBool_Test"
	cd /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/Util/Tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AlembicUtilOperatorBool_Test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/Alembic/Util/Tests/CMakeFiles/AlembicUtilOperatorBool_Test.dir/build: lib/Alembic/Util/Tests/AlembicUtilOperatorBool_Test
.PHONY : lib/Alembic/Util/Tests/CMakeFiles/AlembicUtilOperatorBool_Test.dir/build

lib/Alembic/Util/Tests/CMakeFiles/AlembicUtilOperatorBool_Test.dir/clean:
	cd /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/Util/Tests && $(CMAKE_COMMAND) -P CMakeFiles/AlembicUtilOperatorBool_Test.dir/cmake_clean.cmake
.PHONY : lib/Alembic/Util/Tests/CMakeFiles/AlembicUtilOperatorBool_Test.dir/clean

lib/Alembic/Util/Tests/CMakeFiles/AlembicUtilOperatorBool_Test.dir/depend:
	cd /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/lib/Alembic/Util/Tests /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/Util/Tests /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/lib/Alembic/Util/Tests/CMakeFiles/AlembicUtilOperatorBool_Test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/Alembic/Util/Tests/CMakeFiles/AlembicUtilOperatorBool_Test.dir/depend

