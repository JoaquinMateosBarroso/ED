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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/i22mabaj/Desktop/dos_detector-open_addressing/CMakeFiles/CMakeTmp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/i22mabaj/Desktop/dos_detector-open_addressing/CMakeFiles/CMakeTmp

# Include any dependencies generated for this target.
include CMakeFiles/cmTC_aff35.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cmTC_aff35.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cmTC_aff35.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cmTC_aff35.dir/flags.make

CMakeFiles/cmTC_aff35.dir/CMakeCCompilerABI.c.o: CMakeFiles/cmTC_aff35.dir/flags.make
CMakeFiles/cmTC_aff35.dir/CMakeCCompilerABI.c.o: /usr/local/share/cmake-3.22/Modules/CMakeCCompilerABI.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --progress-dir=/home/i22mabaj/Desktop/dos_detector-open_addressing/CMakeFiles/CMakeTmp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/cmTC_aff35.dir/CMakeCCompilerABI.c.o"
	/usr/local/opt/gcc-5.3.0-64/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cmTC_aff35.dir/CMakeCCompilerABI.c.o -c /usr/local/share/cmake-3.22/Modules/CMakeCCompilerABI.c

CMakeFiles/cmTC_aff35.dir/CMakeCCompilerABI.c.i: cmake_force
	@echo "Preprocessing C source to CMakeFiles/cmTC_aff35.dir/CMakeCCompilerABI.c.i"
	/usr/local/opt/gcc-5.3.0-64/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /usr/local/share/cmake-3.22/Modules/CMakeCCompilerABI.c > CMakeFiles/cmTC_aff35.dir/CMakeCCompilerABI.c.i

CMakeFiles/cmTC_aff35.dir/CMakeCCompilerABI.c.s: cmake_force
	@echo "Compiling C source to assembly CMakeFiles/cmTC_aff35.dir/CMakeCCompilerABI.c.s"
	/usr/local/opt/gcc-5.3.0-64/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /usr/local/share/cmake-3.22/Modules/CMakeCCompilerABI.c -o CMakeFiles/cmTC_aff35.dir/CMakeCCompilerABI.c.s

# Object files for target cmTC_aff35
cmTC_aff35_OBJECTS = \
"CMakeFiles/cmTC_aff35.dir/CMakeCCompilerABI.c.o"

# External object files for target cmTC_aff35
cmTC_aff35_EXTERNAL_OBJECTS =

cmTC_aff35: CMakeFiles/cmTC_aff35.dir/CMakeCCompilerABI.c.o
cmTC_aff35: CMakeFiles/cmTC_aff35.dir/build.make
cmTC_aff35: CMakeFiles/cmTC_aff35.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --progress-dir=/home/i22mabaj/Desktop/dos_detector-open_addressing/CMakeFiles/CMakeTmp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable cmTC_aff35"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cmTC_aff35.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cmTC_aff35.dir/build: cmTC_aff35
.PHONY : CMakeFiles/cmTC_aff35.dir/build

CMakeFiles/cmTC_aff35.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cmTC_aff35.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cmTC_aff35.dir/clean

CMakeFiles/cmTC_aff35.dir/depend:
	cd /home/i22mabaj/Desktop/dos_detector-open_addressing/CMakeFiles/CMakeTmp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/i22mabaj/Desktop/dos_detector-open_addressing/CMakeFiles/CMakeTmp /home/i22mabaj/Desktop/dos_detector-open_addressing/CMakeFiles/CMakeTmp /home/i22mabaj/Desktop/dos_detector-open_addressing/CMakeFiles/CMakeTmp /home/i22mabaj/Desktop/dos_detector-open_addressing/CMakeFiles/CMakeTmp /home/i22mabaj/Desktop/dos_detector-open_addressing/CMakeFiles/CMakeTmp/CMakeFiles/cmTC_aff35.dir/DependInfo.cmake
.PHONY : CMakeFiles/cmTC_aff35.dir/depend
