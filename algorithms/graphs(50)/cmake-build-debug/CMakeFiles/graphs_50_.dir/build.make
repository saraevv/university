# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.2.5\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.2.5\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\university\algorithms\graphs(50)

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\university\algorithms\graphs(50)\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/graphs_50_.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/graphs_50_.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/graphs_50_.dir/flags.make

CMakeFiles/graphs_50_.dir/main.cpp.obj: CMakeFiles/graphs_50_.dir/flags.make
CMakeFiles/graphs_50_.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\university\algorithms\graphs(50)\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/graphs_50_.dir/main.cpp.obj"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\graphs_50_.dir\main.cpp.obj -c E:\university\algorithms\graphs(50)\main.cpp

CMakeFiles/graphs_50_.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/graphs_50_.dir/main.cpp.i"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\university\algorithms\graphs(50)\main.cpp > CMakeFiles\graphs_50_.dir\main.cpp.i

CMakeFiles/graphs_50_.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/graphs_50_.dir/main.cpp.s"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\university\algorithms\graphs(50)\main.cpp -o CMakeFiles\graphs_50_.dir\main.cpp.s

# Object files for target graphs_50_
graphs_50__OBJECTS = \
"CMakeFiles/graphs_50_.dir/main.cpp.obj"

# External object files for target graphs_50_
graphs_50__EXTERNAL_OBJECTS =

graphs_50_.exe: CMakeFiles/graphs_50_.dir/main.cpp.obj
graphs_50_.exe: CMakeFiles/graphs_50_.dir/build.make
graphs_50_.exe: CMakeFiles/graphs_50_.dir/linklibs.rsp
graphs_50_.exe: CMakeFiles/graphs_50_.dir/objects1.rsp
graphs_50_.exe: CMakeFiles/graphs_50_.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\university\algorithms\graphs(50)\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable graphs_50_.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\graphs_50_.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/graphs_50_.dir/build: graphs_50_.exe

.PHONY : CMakeFiles/graphs_50_.dir/build

CMakeFiles/graphs_50_.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\graphs_50_.dir\cmake_clean.cmake
.PHONY : CMakeFiles/graphs_50_.dir/clean

CMakeFiles/graphs_50_.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\university\algorithms\graphs(50) E:\university\algorithms\graphs(50) E:\university\algorithms\graphs(50)\cmake-build-debug E:\university\algorithms\graphs(50)\cmake-build-debug E:\university\algorithms\graphs(50)\cmake-build-debug\CMakeFiles\graphs_50_.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/graphs_50_.dir/depend

