# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_SOURCE_DIR = /home/aliya/programming/cpp/RRIP-cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aliya/programming/cpp/RRIP-cpp/build

# Include any dependencies generated for this target.
include lib/ideal_cache/CMakeFiles/ideal_cache.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/ideal_cache/CMakeFiles/ideal_cache.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/ideal_cache/CMakeFiles/ideal_cache.dir/progress.make

# Include the compile flags for this target's objects.
include lib/ideal_cache/CMakeFiles/ideal_cache.dir/flags.make

lib/ideal_cache/CMakeFiles/ideal_cache.dir/ideal_cache.cpp.o: lib/ideal_cache/CMakeFiles/ideal_cache.dir/flags.make
lib/ideal_cache/CMakeFiles/ideal_cache.dir/ideal_cache.cpp.o: /home/aliya/programming/cpp/RRIP-cpp/lib/ideal_cache/ideal_cache.cpp
lib/ideal_cache/CMakeFiles/ideal_cache.dir/ideal_cache.cpp.o: lib/ideal_cache/CMakeFiles/ideal_cache.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aliya/programming/cpp/RRIP-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/ideal_cache/CMakeFiles/ideal_cache.dir/ideal_cache.cpp.o"
	cd /home/aliya/programming/cpp/RRIP-cpp/build/lib/ideal_cache && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/ideal_cache/CMakeFiles/ideal_cache.dir/ideal_cache.cpp.o -MF CMakeFiles/ideal_cache.dir/ideal_cache.cpp.o.d -o CMakeFiles/ideal_cache.dir/ideal_cache.cpp.o -c /home/aliya/programming/cpp/RRIP-cpp/lib/ideal_cache/ideal_cache.cpp

lib/ideal_cache/CMakeFiles/ideal_cache.dir/ideal_cache.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ideal_cache.dir/ideal_cache.cpp.i"
	cd /home/aliya/programming/cpp/RRIP-cpp/build/lib/ideal_cache && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aliya/programming/cpp/RRIP-cpp/lib/ideal_cache/ideal_cache.cpp > CMakeFiles/ideal_cache.dir/ideal_cache.cpp.i

lib/ideal_cache/CMakeFiles/ideal_cache.dir/ideal_cache.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ideal_cache.dir/ideal_cache.cpp.s"
	cd /home/aliya/programming/cpp/RRIP-cpp/build/lib/ideal_cache && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aliya/programming/cpp/RRIP-cpp/lib/ideal_cache/ideal_cache.cpp -o CMakeFiles/ideal_cache.dir/ideal_cache.cpp.s

# Object files for target ideal_cache
ideal_cache_OBJECTS = \
"CMakeFiles/ideal_cache.dir/ideal_cache.cpp.o"

# External object files for target ideal_cache
ideal_cache_EXTERNAL_OBJECTS =

lib/ideal_cache/libideal_cache.a: lib/ideal_cache/CMakeFiles/ideal_cache.dir/ideal_cache.cpp.o
lib/ideal_cache/libideal_cache.a: lib/ideal_cache/CMakeFiles/ideal_cache.dir/build.make
lib/ideal_cache/libideal_cache.a: lib/ideal_cache/CMakeFiles/ideal_cache.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/aliya/programming/cpp/RRIP-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libideal_cache.a"
	cd /home/aliya/programming/cpp/RRIP-cpp/build/lib/ideal_cache && $(CMAKE_COMMAND) -P CMakeFiles/ideal_cache.dir/cmake_clean_target.cmake
	cd /home/aliya/programming/cpp/RRIP-cpp/build/lib/ideal_cache && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ideal_cache.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/ideal_cache/CMakeFiles/ideal_cache.dir/build: lib/ideal_cache/libideal_cache.a
.PHONY : lib/ideal_cache/CMakeFiles/ideal_cache.dir/build

lib/ideal_cache/CMakeFiles/ideal_cache.dir/clean:
	cd /home/aliya/programming/cpp/RRIP-cpp/build/lib/ideal_cache && $(CMAKE_COMMAND) -P CMakeFiles/ideal_cache.dir/cmake_clean.cmake
.PHONY : lib/ideal_cache/CMakeFiles/ideal_cache.dir/clean

lib/ideal_cache/CMakeFiles/ideal_cache.dir/depend:
	cd /home/aliya/programming/cpp/RRIP-cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aliya/programming/cpp/RRIP-cpp /home/aliya/programming/cpp/RRIP-cpp/lib/ideal_cache /home/aliya/programming/cpp/RRIP-cpp/build /home/aliya/programming/cpp/RRIP-cpp/build/lib/ideal_cache /home/aliya/programming/cpp/RRIP-cpp/build/lib/ideal_cache/CMakeFiles/ideal_cache.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/ideal_cache/CMakeFiles/ideal_cache.dir/depend

