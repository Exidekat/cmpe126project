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
CMAKE_SOURCE_DIR = /home/neal/cmpe126project/cmpe126project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/neal/cmpe126project/cmpe126project

# Include any dependencies generated for this target.
include CMakeFiles/cmpe126project.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cmpe126project.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cmpe126project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cmpe126project.dir/flags.make

CMakeFiles/cmpe126project.dir/main.cpp.o: CMakeFiles/cmpe126project.dir/flags.make
CMakeFiles/cmpe126project.dir/main.cpp.o: main.cpp
CMakeFiles/cmpe126project.dir/main.cpp.o: CMakeFiles/cmpe126project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/neal/cmpe126project/cmpe126project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cmpe126project.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cmpe126project.dir/main.cpp.o -MF CMakeFiles/cmpe126project.dir/main.cpp.o.d -o CMakeFiles/cmpe126project.dir/main.cpp.o -c /home/neal/cmpe126project/cmpe126project/main.cpp

CMakeFiles/cmpe126project.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cmpe126project.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/neal/cmpe126project/cmpe126project/main.cpp > CMakeFiles/cmpe126project.dir/main.cpp.i

CMakeFiles/cmpe126project.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cmpe126project.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/neal/cmpe126project/cmpe126project/main.cpp -o CMakeFiles/cmpe126project.dir/main.cpp.s

# Object files for target cmpe126project
cmpe126project_OBJECTS = \
"CMakeFiles/cmpe126project.dir/main.cpp.o"

# External object files for target cmpe126project
cmpe126project_EXTERNAL_OBJECTS =

cmpe126project: CMakeFiles/cmpe126project.dir/main.cpp.o
cmpe126project: CMakeFiles/cmpe126project.dir/build.make
cmpe126project: CMakeFiles/cmpe126project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/neal/cmpe126project/cmpe126project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cmpe126project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cmpe126project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cmpe126project.dir/build: cmpe126project
.PHONY : CMakeFiles/cmpe126project.dir/build

CMakeFiles/cmpe126project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cmpe126project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cmpe126project.dir/clean

CMakeFiles/cmpe126project.dir/depend:
	cd /home/neal/cmpe126project/cmpe126project && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/neal/cmpe126project/cmpe126project /home/neal/cmpe126project/cmpe126project /home/neal/cmpe126project/cmpe126project /home/neal/cmpe126project/cmpe126project /home/neal/cmpe126project/cmpe126project/CMakeFiles/cmpe126project.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cmpe126project.dir/depend
