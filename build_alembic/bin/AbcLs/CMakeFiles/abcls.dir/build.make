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
include bin/AbcLs/CMakeFiles/abcls.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include bin/AbcLs/CMakeFiles/abcls.dir/compiler_depend.make

# Include the progress variables for this target.
include bin/AbcLs/CMakeFiles/abcls.dir/progress.make

# Include the compile flags for this target's objects.
include bin/AbcLs/CMakeFiles/abcls.dir/flags.make

bin/AbcLs/CMakeFiles/abcls.dir/AbcLs.cpp.o: bin/AbcLs/CMakeFiles/abcls.dir/flags.make
bin/AbcLs/CMakeFiles/abcls.dir/AbcLs.cpp.o: /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/bin/AbcLs/AbcLs.cpp
bin/AbcLs/CMakeFiles/abcls.dir/AbcLs.cpp.o: bin/AbcLs/CMakeFiles/abcls.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object bin/AbcLs/CMakeFiles/abcls.dir/AbcLs.cpp.o"
	cd /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/bin/AbcLs && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT bin/AbcLs/CMakeFiles/abcls.dir/AbcLs.cpp.o -MF CMakeFiles/abcls.dir/AbcLs.cpp.o.d -o CMakeFiles/abcls.dir/AbcLs.cpp.o -c /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/bin/AbcLs/AbcLs.cpp

bin/AbcLs/CMakeFiles/abcls.dir/AbcLs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/abcls.dir/AbcLs.cpp.i"
	cd /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/bin/AbcLs && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/bin/AbcLs/AbcLs.cpp > CMakeFiles/abcls.dir/AbcLs.cpp.i

bin/AbcLs/CMakeFiles/abcls.dir/AbcLs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/abcls.dir/AbcLs.cpp.s"
	cd /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/bin/AbcLs && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/bin/AbcLs/AbcLs.cpp -o CMakeFiles/abcls.dir/AbcLs.cpp.s

# Object files for target abcls
abcls_OBJECTS = \
"CMakeFiles/abcls.dir/AbcLs.cpp.o"

# External object files for target abcls
abcls_EXTERNAL_OBJECTS =

bin/AbcLs/abcls: bin/AbcLs/CMakeFiles/abcls.dir/AbcLs.cpp.o
bin/AbcLs/abcls: bin/AbcLs/CMakeFiles/abcls.dir/build.make
bin/AbcLs/abcls: lib/Alembic/libAlembic.a
bin/AbcLs/abcls: /usr/local/lib/libImath-3_1.29.4.0.dylib
bin/AbcLs/abcls: bin/AbcLs/CMakeFiles/abcls.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable abcls"
	cd /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/bin/AbcLs && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/abcls.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bin/AbcLs/CMakeFiles/abcls.dir/build: bin/AbcLs/abcls
.PHONY : bin/AbcLs/CMakeFiles/abcls.dir/build

bin/AbcLs/CMakeFiles/abcls.dir/clean:
	cd /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/bin/AbcLs && $(CMAKE_COMMAND) -P CMakeFiles/abcls.dir/cmake_clean.cmake
.PHONY : bin/AbcLs/CMakeFiles/abcls.dir/clean

bin/AbcLs/CMakeFiles/abcls.dir/depend:
	cd /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/alembic/bin/AbcLs /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/bin/AbcLs /Users/brandondiaz/Downloads/CS/cs2240/cs2240-final-project/build_alembic/bin/AbcLs/CMakeFiles/abcls.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bin/AbcLs/CMakeFiles/abcls.dir/depend

