# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /mnt/c/Users/26409/x226luo/project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/26409/x226luo/project/build

# Include any dependencies generated for this target.
include minisat/CMakeFiles/minisat_core.dir/depend.make

# Include the progress variables for this target.
include minisat/CMakeFiles/minisat_core.dir/progress.make

# Include the compile flags for this target's objects.
include minisat/CMakeFiles/minisat_core.dir/flags.make

minisat/CMakeFiles/minisat_core.dir/minisat/core/Main.cc.o: minisat/CMakeFiles/minisat_core.dir/flags.make
minisat/CMakeFiles/minisat_core.dir/minisat/core/Main.cc.o: ../minisat/minisat/core/Main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/26409/x226luo/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object minisat/CMakeFiles/minisat_core.dir/minisat/core/Main.cc.o"
	cd /mnt/c/Users/26409/x226luo/project/build/minisat && /bin/x86_64-linux-gnu-g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minisat_core.dir/minisat/core/Main.cc.o -c /mnt/c/Users/26409/x226luo/project/minisat/minisat/core/Main.cc

minisat/CMakeFiles/minisat_core.dir/minisat/core/Main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minisat_core.dir/minisat/core/Main.cc.i"
	cd /mnt/c/Users/26409/x226luo/project/build/minisat && /bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/26409/x226luo/project/minisat/minisat/core/Main.cc > CMakeFiles/minisat_core.dir/minisat/core/Main.cc.i

minisat/CMakeFiles/minisat_core.dir/minisat/core/Main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minisat_core.dir/minisat/core/Main.cc.s"
	cd /mnt/c/Users/26409/x226luo/project/build/minisat && /bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/26409/x226luo/project/minisat/minisat/core/Main.cc -o CMakeFiles/minisat_core.dir/minisat/core/Main.cc.s

# Object files for target minisat_core
minisat_core_OBJECTS = \
"CMakeFiles/minisat_core.dir/minisat/core/Main.cc.o"

# External object files for target minisat_core
minisat_core_EXTERNAL_OBJECTS =

minisat/minisat_core: minisat/CMakeFiles/minisat_core.dir/minisat/core/Main.cc.o
minisat/minisat_core: minisat/CMakeFiles/minisat_core.dir/build.make
minisat/minisat_core: minisat/libminisat.a
minisat/minisat_core: /usr/lib/x86_64-linux-gnu/libz.so
minisat/minisat_core: minisat/CMakeFiles/minisat_core.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/26409/x226luo/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable minisat_core"
	cd /mnt/c/Users/26409/x226luo/project/build/minisat && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/minisat_core.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
minisat/CMakeFiles/minisat_core.dir/build: minisat/minisat_core

.PHONY : minisat/CMakeFiles/minisat_core.dir/build

minisat/CMakeFiles/minisat_core.dir/clean:
	cd /mnt/c/Users/26409/x226luo/project/build/minisat && $(CMAKE_COMMAND) -P CMakeFiles/minisat_core.dir/cmake_clean.cmake
.PHONY : minisat/CMakeFiles/minisat_core.dir/clean

minisat/CMakeFiles/minisat_core.dir/depend:
	cd /mnt/c/Users/26409/x226luo/project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/26409/x226luo/project /mnt/c/Users/26409/x226luo/project/minisat /mnt/c/Users/26409/x226luo/project/build /mnt/c/Users/26409/x226luo/project/build/minisat /mnt/c/Users/26409/x226luo/project/build/minisat/CMakeFiles/minisat_core.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : minisat/CMakeFiles/minisat_core.dir/depend

