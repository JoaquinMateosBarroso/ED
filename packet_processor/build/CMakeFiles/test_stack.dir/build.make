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
CMAKE_SOURCE_DIR = /home/joaquin/Escritorio/pruebas/packet_processor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/joaquin/Escritorio/pruebas/packet_processor/build

# Include any dependencies generated for this target.
include CMakeFiles/test_stack.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test_stack.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test_stack.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_stack.dir/flags.make

CMakeFiles/test_stack.dir/test_stack.cpp.o: CMakeFiles/test_stack.dir/flags.make
CMakeFiles/test_stack.dir/test_stack.cpp.o: ../test_stack.cpp
CMakeFiles/test_stack.dir/test_stack.cpp.o: CMakeFiles/test_stack.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joaquin/Escritorio/pruebas/packet_processor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_stack.dir/test_stack.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_stack.dir/test_stack.cpp.o -MF CMakeFiles/test_stack.dir/test_stack.cpp.o.d -o CMakeFiles/test_stack.dir/test_stack.cpp.o -c /home/joaquin/Escritorio/pruebas/packet_processor/test_stack.cpp

CMakeFiles/test_stack.dir/test_stack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_stack.dir/test_stack.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joaquin/Escritorio/pruebas/packet_processor/test_stack.cpp > CMakeFiles/test_stack.dir/test_stack.cpp.i

CMakeFiles/test_stack.dir/test_stack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_stack.dir/test_stack.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joaquin/Escritorio/pruebas/packet_processor/test_stack.cpp -o CMakeFiles/test_stack.dir/test_stack.cpp.s

# Object files for target test_stack
test_stack_OBJECTS = \
"CMakeFiles/test_stack.dir/test_stack.cpp.o"

# External object files for target test_stack
test_stack_EXTERNAL_OBJECTS =

test_stack: CMakeFiles/test_stack.dir/test_stack.cpp.o
test_stack: CMakeFiles/test_stack.dir/build.make
test_stack: CMakeFiles/test_stack.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/joaquin/Escritorio/pruebas/packet_processor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_stack"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_stack.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_stack.dir/build: test_stack
.PHONY : CMakeFiles/test_stack.dir/build

CMakeFiles/test_stack.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_stack.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_stack.dir/clean

CMakeFiles/test_stack.dir/depend:
	cd /home/joaquin/Escritorio/pruebas/packet_processor/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joaquin/Escritorio/pruebas/packet_processor /home/joaquin/Escritorio/pruebas/packet_processor /home/joaquin/Escritorio/pruebas/packet_processor/build /home/joaquin/Escritorio/pruebas/packet_processor/build /home/joaquin/Escritorio/pruebas/packet_processor/build/CMakeFiles/test_stack.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_stack.dir/depend

