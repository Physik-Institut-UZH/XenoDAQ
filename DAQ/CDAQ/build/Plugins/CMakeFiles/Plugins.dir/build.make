# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_SOURCE_DIR = /home/daq/DAQ-ZERO/DAQ/CDAQ

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/daq/DAQ-ZERO/DAQ/CDAQ/build

# Include any dependencies generated for this target.
include Plugins/CMakeFiles/Plugins.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Plugins/CMakeFiles/Plugins.dir/compiler_depend.make

# Include the progress variables for this target.
include Plugins/CMakeFiles/Plugins.dir/progress.make

# Include the compile flags for this target's objects.
include Plugins/CMakeFiles/Plugins.dir/flags.make

Plugins/CMakeFiles/Plugins.dir/Source/common.cpp.o: Plugins/CMakeFiles/Plugins.dir/flags.make
Plugins/CMakeFiles/Plugins.dir/Source/common.cpp.o: ../Plugins/Source/common.cpp
Plugins/CMakeFiles/Plugins.dir/Source/common.cpp.o: Plugins/CMakeFiles/Plugins.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daq/DAQ-ZERO/DAQ/CDAQ/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Plugins/CMakeFiles/Plugins.dir/Source/common.cpp.o"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Plugins && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Plugins/CMakeFiles/Plugins.dir/Source/common.cpp.o -MF CMakeFiles/Plugins.dir/Source/common.cpp.o.d -o CMakeFiles/Plugins.dir/Source/common.cpp.o -c /home/daq/DAQ-ZERO/DAQ/CDAQ/Plugins/Source/common.cpp

Plugins/CMakeFiles/Plugins.dir/Source/common.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Plugins.dir/Source/common.cpp.i"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Plugins && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daq/DAQ-ZERO/DAQ/CDAQ/Plugins/Source/common.cpp > CMakeFiles/Plugins.dir/Source/common.cpp.i

Plugins/CMakeFiles/Plugins.dir/Source/common.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Plugins.dir/Source/common.cpp.s"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Plugins && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daq/DAQ-ZERO/DAQ/CDAQ/Plugins/Source/common.cpp -o CMakeFiles/Plugins.dir/Source/common.cpp.s

Plugins/CMakeFiles/Plugins.dir/Source/keyb.cpp.o: Plugins/CMakeFiles/Plugins.dir/flags.make
Plugins/CMakeFiles/Plugins.dir/Source/keyb.cpp.o: ../Plugins/Source/keyb.cpp
Plugins/CMakeFiles/Plugins.dir/Source/keyb.cpp.o: Plugins/CMakeFiles/Plugins.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daq/DAQ-ZERO/DAQ/CDAQ/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object Plugins/CMakeFiles/Plugins.dir/Source/keyb.cpp.o"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Plugins && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Plugins/CMakeFiles/Plugins.dir/Source/keyb.cpp.o -MF CMakeFiles/Plugins.dir/Source/keyb.cpp.o.d -o CMakeFiles/Plugins.dir/Source/keyb.cpp.o -c /home/daq/DAQ-ZERO/DAQ/CDAQ/Plugins/Source/keyb.cpp

Plugins/CMakeFiles/Plugins.dir/Source/keyb.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Plugins.dir/Source/keyb.cpp.i"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Plugins && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daq/DAQ-ZERO/DAQ/CDAQ/Plugins/Source/keyb.cpp > CMakeFiles/Plugins.dir/Source/keyb.cpp.i

Plugins/CMakeFiles/Plugins.dir/Source/keyb.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Plugins.dir/Source/keyb.cpp.s"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Plugins && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daq/DAQ-ZERO/DAQ/CDAQ/Plugins/Source/keyb.cpp -o CMakeFiles/Plugins.dir/Source/keyb.cpp.s

Plugins/CMakeFiles/Plugins.dir/Source/xmlParser.cpp.o: Plugins/CMakeFiles/Plugins.dir/flags.make
Plugins/CMakeFiles/Plugins.dir/Source/xmlParser.cpp.o: ../Plugins/Source/xmlParser.cpp
Plugins/CMakeFiles/Plugins.dir/Source/xmlParser.cpp.o: Plugins/CMakeFiles/Plugins.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daq/DAQ-ZERO/DAQ/CDAQ/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object Plugins/CMakeFiles/Plugins.dir/Source/xmlParser.cpp.o"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Plugins && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Plugins/CMakeFiles/Plugins.dir/Source/xmlParser.cpp.o -MF CMakeFiles/Plugins.dir/Source/xmlParser.cpp.o.d -o CMakeFiles/Plugins.dir/Source/xmlParser.cpp.o -c /home/daq/DAQ-ZERO/DAQ/CDAQ/Plugins/Source/xmlParser.cpp

Plugins/CMakeFiles/Plugins.dir/Source/xmlParser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Plugins.dir/Source/xmlParser.cpp.i"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Plugins && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daq/DAQ-ZERO/DAQ/CDAQ/Plugins/Source/xmlParser.cpp > CMakeFiles/Plugins.dir/Source/xmlParser.cpp.i

Plugins/CMakeFiles/Plugins.dir/Source/xmlParser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Plugins.dir/Source/xmlParser.cpp.s"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Plugins && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daq/DAQ-ZERO/DAQ/CDAQ/Plugins/Source/xmlParser.cpp -o CMakeFiles/Plugins.dir/Source/xmlParser.cpp.s

# Object files for target Plugins
Plugins_OBJECTS = \
"CMakeFiles/Plugins.dir/Source/common.cpp.o" \
"CMakeFiles/Plugins.dir/Source/keyb.cpp.o" \
"CMakeFiles/Plugins.dir/Source/xmlParser.cpp.o"

# External object files for target Plugins
Plugins_EXTERNAL_OBJECTS =

lib/libPlugins.a: Plugins/CMakeFiles/Plugins.dir/Source/common.cpp.o
lib/libPlugins.a: Plugins/CMakeFiles/Plugins.dir/Source/keyb.cpp.o
lib/libPlugins.a: Plugins/CMakeFiles/Plugins.dir/Source/xmlParser.cpp.o
lib/libPlugins.a: Plugins/CMakeFiles/Plugins.dir/build.make
lib/libPlugins.a: Plugins/CMakeFiles/Plugins.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/daq/DAQ-ZERO/DAQ/CDAQ/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library ../lib/libPlugins.a"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Plugins && $(CMAKE_COMMAND) -P CMakeFiles/Plugins.dir/cmake_clean_target.cmake
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Plugins && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Plugins.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Plugins/CMakeFiles/Plugins.dir/build: lib/libPlugins.a
.PHONY : Plugins/CMakeFiles/Plugins.dir/build

Plugins/CMakeFiles/Plugins.dir/clean:
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Plugins && $(CMAKE_COMMAND) -P CMakeFiles/Plugins.dir/cmake_clean.cmake
.PHONY : Plugins/CMakeFiles/Plugins.dir/clean

Plugins/CMakeFiles/Plugins.dir/depend:
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/daq/DAQ-ZERO/DAQ/CDAQ /home/daq/DAQ-ZERO/DAQ/CDAQ/Plugins /home/daq/DAQ-ZERO/DAQ/CDAQ/build /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Plugins /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Plugins/CMakeFiles/Plugins.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Plugins/CMakeFiles/Plugins.dir/depend

