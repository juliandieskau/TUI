# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /workspaces/tui

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspaces/tui/build

# Include any dependencies generated for this target.
include _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_color_info_palette256.dir/depend.make

# Include the progress variables for this target.
include _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_color_info_palette256.dir/progress.make

# Include the compile flags for this target's objects.
include _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_color_info_palette256.dir/flags.make

_deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_color_info_palette256.dir/color_info_palette256.cpp.o: _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_color_info_palette256.dir/flags.make
_deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_color_info_palette256.dir/color_info_palette256.cpp.o: _deps/ftxui-src/examples/dom/color_info_palette256.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/tui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_color_info_palette256.dir/color_info_palette256.cpp.o"
	cd /workspaces/tui/build/_deps/ftxui-build/examples/dom && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ftxui_example_color_info_palette256.dir/color_info_palette256.cpp.o -c /workspaces/tui/build/_deps/ftxui-src/examples/dom/color_info_palette256.cpp

_deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_color_info_palette256.dir/color_info_palette256.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ftxui_example_color_info_palette256.dir/color_info_palette256.cpp.i"
	cd /workspaces/tui/build/_deps/ftxui-build/examples/dom && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/tui/build/_deps/ftxui-src/examples/dom/color_info_palette256.cpp > CMakeFiles/ftxui_example_color_info_palette256.dir/color_info_palette256.cpp.i

_deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_color_info_palette256.dir/color_info_palette256.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ftxui_example_color_info_palette256.dir/color_info_palette256.cpp.s"
	cd /workspaces/tui/build/_deps/ftxui-build/examples/dom && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/tui/build/_deps/ftxui-src/examples/dom/color_info_palette256.cpp -o CMakeFiles/ftxui_example_color_info_palette256.dir/color_info_palette256.cpp.s

# Object files for target ftxui_example_color_info_palette256
ftxui_example_color_info_palette256_OBJECTS = \
"CMakeFiles/ftxui_example_color_info_palette256.dir/color_info_palette256.cpp.o"

# External object files for target ftxui_example_color_info_palette256
ftxui_example_color_info_palette256_EXTERNAL_OBJECTS =

_deps/ftxui-build/examples/dom/ftxui_example_color_info_palette256: _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_color_info_palette256.dir/color_info_palette256.cpp.o
_deps/ftxui-build/examples/dom/ftxui_example_color_info_palette256: _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_color_info_palette256.dir/build.make
_deps/ftxui-build/examples/dom/ftxui_example_color_info_palette256: _deps/ftxui-build/libftxui-dom.a
_deps/ftxui-build/examples/dom/ftxui_example_color_info_palette256: _deps/ftxui-build/libftxui-screen.a
_deps/ftxui-build/examples/dom/ftxui_example_color_info_palette256: _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_color_info_palette256.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/workspaces/tui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ftxui_example_color_info_palette256"
	cd /workspaces/tui/build/_deps/ftxui-build/examples/dom && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ftxui_example_color_info_palette256.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
_deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_color_info_palette256.dir/build: _deps/ftxui-build/examples/dom/ftxui_example_color_info_palette256

.PHONY : _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_color_info_palette256.dir/build

_deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_color_info_palette256.dir/clean:
	cd /workspaces/tui/build/_deps/ftxui-build/examples/dom && $(CMAKE_COMMAND) -P CMakeFiles/ftxui_example_color_info_palette256.dir/cmake_clean.cmake
.PHONY : _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_color_info_palette256.dir/clean

_deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_color_info_palette256.dir/depend:
	cd /workspaces/tui/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/tui /workspaces/tui/build/_deps/ftxui-src/examples/dom /workspaces/tui/build /workspaces/tui/build/_deps/ftxui-build/examples/dom /workspaces/tui/build/_deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_color_info_palette256.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_color_info_palette256.dir/depend

