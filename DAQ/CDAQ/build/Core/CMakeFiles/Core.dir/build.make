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
include Core/CMakeFiles/Core.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Core/CMakeFiles/Core.dir/compiler_depend.make

# Include the progress variables for this target.
include Core/CMakeFiles/Core.dir/progress.make

# Include the compile flags for this target's objects.
include Core/CMakeFiles/Core.dir/flags.make

Core/CMakeFiles/Core.dir/Source/VMEManager.cpp.o: Core/CMakeFiles/Core.dir/flags.make
Core/CMakeFiles/Core.dir/Source/VMEManager.cpp.o: ../Core/Source/VMEManager.cpp
Core/CMakeFiles/Core.dir/Source/VMEManager.cpp.o: Core/CMakeFiles/Core.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daq/DAQ-ZERO/DAQ/CDAQ/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Core/CMakeFiles/Core.dir/Source/VMEManager.cpp.o"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Core/CMakeFiles/Core.dir/Source/VMEManager.cpp.o -MF CMakeFiles/Core.dir/Source/VMEManager.cpp.o.d -o CMakeFiles/Core.dir/Source/VMEManager.cpp.o -c /home/daq/DAQ-ZERO/DAQ/CDAQ/Core/Source/VMEManager.cpp

Core/CMakeFiles/Core.dir/Source/VMEManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Core.dir/Source/VMEManager.cpp.i"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daq/DAQ-ZERO/DAQ/CDAQ/Core/Source/VMEManager.cpp > CMakeFiles/Core.dir/Source/VMEManager.cpp.i

Core/CMakeFiles/Core.dir/Source/VMEManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Core.dir/Source/VMEManager.cpp.s"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daq/DAQ-ZERO/DAQ/CDAQ/Core/Source/VMEManager.cpp -o CMakeFiles/Core.dir/Source/VMEManager.cpp.s

Core/CMakeFiles/Core.dir/Source/ADCManager.cpp.o: Core/CMakeFiles/Core.dir/flags.make
Core/CMakeFiles/Core.dir/Source/ADCManager.cpp.o: ../Core/Source/ADCManager.cpp
Core/CMakeFiles/Core.dir/Source/ADCManager.cpp.o: Core/CMakeFiles/Core.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daq/DAQ-ZERO/DAQ/CDAQ/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object Core/CMakeFiles/Core.dir/Source/ADCManager.cpp.o"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Core/CMakeFiles/Core.dir/Source/ADCManager.cpp.o -MF CMakeFiles/Core.dir/Source/ADCManager.cpp.o.d -o CMakeFiles/Core.dir/Source/ADCManager.cpp.o -c /home/daq/DAQ-ZERO/DAQ/CDAQ/Core/Source/ADCManager.cpp

Core/CMakeFiles/Core.dir/Source/ADCManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Core.dir/Source/ADCManager.cpp.i"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daq/DAQ-ZERO/DAQ/CDAQ/Core/Source/ADCManager.cpp > CMakeFiles/Core.dir/Source/ADCManager.cpp.i

Core/CMakeFiles/Core.dir/Source/ADCManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Core.dir/Source/ADCManager.cpp.s"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daq/DAQ-ZERO/DAQ/CDAQ/Core/Source/ADCManager.cpp -o CMakeFiles/Core.dir/Source/ADCManager.cpp.s

Core/CMakeFiles/Core.dir/Source/ADCManager1730.cpp.o: Core/CMakeFiles/Core.dir/flags.make
Core/CMakeFiles/Core.dir/Source/ADCManager1730.cpp.o: ../Core/Source/ADCManager1730.cpp
Core/CMakeFiles/Core.dir/Source/ADCManager1730.cpp.o: Core/CMakeFiles/Core.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daq/DAQ-ZERO/DAQ/CDAQ/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object Core/CMakeFiles/Core.dir/Source/ADCManager1730.cpp.o"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Core/CMakeFiles/Core.dir/Source/ADCManager1730.cpp.o -MF CMakeFiles/Core.dir/Source/ADCManager1730.cpp.o.d -o CMakeFiles/Core.dir/Source/ADCManager1730.cpp.o -c /home/daq/DAQ-ZERO/DAQ/CDAQ/Core/Source/ADCManager1730.cpp

Core/CMakeFiles/Core.dir/Source/ADCManager1730.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Core.dir/Source/ADCManager1730.cpp.i"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daq/DAQ-ZERO/DAQ/CDAQ/Core/Source/ADCManager1730.cpp > CMakeFiles/Core.dir/Source/ADCManager1730.cpp.i

Core/CMakeFiles/Core.dir/Source/ADCManager1730.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Core.dir/Source/ADCManager1730.cpp.s"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daq/DAQ-ZERO/DAQ/CDAQ/Core/Source/ADCManager1730.cpp -o CMakeFiles/Core.dir/Source/ADCManager1730.cpp.s

Core/CMakeFiles/Core.dir/Source/ScopeManager.cpp.o: Core/CMakeFiles/Core.dir/flags.make
Core/CMakeFiles/Core.dir/Source/ScopeManager.cpp.o: ../Core/Source/ScopeManager.cpp
Core/CMakeFiles/Core.dir/Source/ScopeManager.cpp.o: Core/CMakeFiles/Core.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daq/DAQ-ZERO/DAQ/CDAQ/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object Core/CMakeFiles/Core.dir/Source/ScopeManager.cpp.o"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Core/CMakeFiles/Core.dir/Source/ScopeManager.cpp.o -MF CMakeFiles/Core.dir/Source/ScopeManager.cpp.o.d -o CMakeFiles/Core.dir/Source/ScopeManager.cpp.o -c /home/daq/DAQ-ZERO/DAQ/CDAQ/Core/Source/ScopeManager.cpp

Core/CMakeFiles/Core.dir/Source/ScopeManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Core.dir/Source/ScopeManager.cpp.i"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daq/DAQ-ZERO/DAQ/CDAQ/Core/Source/ScopeManager.cpp > CMakeFiles/Core.dir/Source/ScopeManager.cpp.i

Core/CMakeFiles/Core.dir/Source/ScopeManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Core.dir/Source/ScopeManager.cpp.s"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daq/DAQ-ZERO/DAQ/CDAQ/Core/Source/ScopeManager.cpp -o CMakeFiles/Core.dir/Source/ScopeManager.cpp.s

Core/CMakeFiles/Core.dir/Source/StorageManager.cpp.o: Core/CMakeFiles/Core.dir/flags.make
Core/CMakeFiles/Core.dir/Source/StorageManager.cpp.o: ../Core/Source/StorageManager.cpp
Core/CMakeFiles/Core.dir/Source/StorageManager.cpp.o: Core/CMakeFiles/Core.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daq/DAQ-ZERO/DAQ/CDAQ/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object Core/CMakeFiles/Core.dir/Source/StorageManager.cpp.o"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Core/CMakeFiles/Core.dir/Source/StorageManager.cpp.o -MF CMakeFiles/Core.dir/Source/StorageManager.cpp.o.d -o CMakeFiles/Core.dir/Source/StorageManager.cpp.o -c /home/daq/DAQ-ZERO/DAQ/CDAQ/Core/Source/StorageManager.cpp

Core/CMakeFiles/Core.dir/Source/StorageManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Core.dir/Source/StorageManager.cpp.i"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daq/DAQ-ZERO/DAQ/CDAQ/Core/Source/StorageManager.cpp > CMakeFiles/Core.dir/Source/StorageManager.cpp.i

Core/CMakeFiles/Core.dir/Source/StorageManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Core.dir/Source/StorageManager.cpp.s"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daq/DAQ-ZERO/DAQ/CDAQ/Core/Source/StorageManager.cpp -o CMakeFiles/Core.dir/Source/StorageManager.cpp.s

Core/CMakeFiles/Core.dir/Source/SlowcontrolManager.cpp.o: Core/CMakeFiles/Core.dir/flags.make
Core/CMakeFiles/Core.dir/Source/SlowcontrolManager.cpp.o: ../Core/Source/SlowcontrolManager.cpp
Core/CMakeFiles/Core.dir/Source/SlowcontrolManager.cpp.o: Core/CMakeFiles/Core.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daq/DAQ-ZERO/DAQ/CDAQ/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object Core/CMakeFiles/Core.dir/Source/SlowcontrolManager.cpp.o"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Core/CMakeFiles/Core.dir/Source/SlowcontrolManager.cpp.o -MF CMakeFiles/Core.dir/Source/SlowcontrolManager.cpp.o.d -o CMakeFiles/Core.dir/Source/SlowcontrolManager.cpp.o -c /home/daq/DAQ-ZERO/DAQ/CDAQ/Core/Source/SlowcontrolManager.cpp

Core/CMakeFiles/Core.dir/Source/SlowcontrolManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Core.dir/Source/SlowcontrolManager.cpp.i"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daq/DAQ-ZERO/DAQ/CDAQ/Core/Source/SlowcontrolManager.cpp > CMakeFiles/Core.dir/Source/SlowcontrolManager.cpp.i

Core/CMakeFiles/Core.dir/Source/SlowcontrolManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Core.dir/Source/SlowcontrolManager.cpp.s"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daq/DAQ-ZERO/DAQ/CDAQ/Core/Source/SlowcontrolManager.cpp -o CMakeFiles/Core.dir/Source/SlowcontrolManager.cpp.s

Core/CMakeFiles/Core.dir/Source/ADCManager1720.cpp.o: Core/CMakeFiles/Core.dir/flags.make
Core/CMakeFiles/Core.dir/Source/ADCManager1720.cpp.o: ../Core/Source/ADCManager1720.cpp
Core/CMakeFiles/Core.dir/Source/ADCManager1720.cpp.o: Core/CMakeFiles/Core.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daq/DAQ-ZERO/DAQ/CDAQ/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object Core/CMakeFiles/Core.dir/Source/ADCManager1720.cpp.o"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Core/CMakeFiles/Core.dir/Source/ADCManager1720.cpp.o -MF CMakeFiles/Core.dir/Source/ADCManager1720.cpp.o.d -o CMakeFiles/Core.dir/Source/ADCManager1720.cpp.o -c /home/daq/DAQ-ZERO/DAQ/CDAQ/Core/Source/ADCManager1720.cpp

Core/CMakeFiles/Core.dir/Source/ADCManager1720.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Core.dir/Source/ADCManager1720.cpp.i"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daq/DAQ-ZERO/DAQ/CDAQ/Core/Source/ADCManager1720.cpp > CMakeFiles/Core.dir/Source/ADCManager1720.cpp.i

Core/CMakeFiles/Core.dir/Source/ADCManager1720.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Core.dir/Source/ADCManager1720.cpp.s"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daq/DAQ-ZERO/DAQ/CDAQ/Core/Source/ADCManager1720.cpp -o CMakeFiles/Core.dir/Source/ADCManager1720.cpp.s

Core/CMakeFiles/Core.dir/Source/ADCManager1724.cpp.o: Core/CMakeFiles/Core.dir/flags.make
Core/CMakeFiles/Core.dir/Source/ADCManager1724.cpp.o: ../Core/Source/ADCManager1724.cpp
Core/CMakeFiles/Core.dir/Source/ADCManager1724.cpp.o: Core/CMakeFiles/Core.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daq/DAQ-ZERO/DAQ/CDAQ/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object Core/CMakeFiles/Core.dir/Source/ADCManager1724.cpp.o"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Core/CMakeFiles/Core.dir/Source/ADCManager1724.cpp.o -MF CMakeFiles/Core.dir/Source/ADCManager1724.cpp.o.d -o CMakeFiles/Core.dir/Source/ADCManager1724.cpp.o -c /home/daq/DAQ-ZERO/DAQ/CDAQ/Core/Source/ADCManager1724.cpp

Core/CMakeFiles/Core.dir/Source/ADCManager1724.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Core.dir/Source/ADCManager1724.cpp.i"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daq/DAQ-ZERO/DAQ/CDAQ/Core/Source/ADCManager1724.cpp > CMakeFiles/Core.dir/Source/ADCManager1724.cpp.i

Core/CMakeFiles/Core.dir/Source/ADCManager1724.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Core.dir/Source/ADCManager1724.cpp.s"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daq/DAQ-ZERO/DAQ/CDAQ/Core/Source/ADCManager1724.cpp -o CMakeFiles/Core.dir/Source/ADCManager1724.cpp.s

Core/CMakeFiles/Core.dir/Source/DCManager.cpp.o: Core/CMakeFiles/Core.dir/flags.make
Core/CMakeFiles/Core.dir/Source/DCManager.cpp.o: ../Core/Source/DCManager.cpp
Core/CMakeFiles/Core.dir/Source/DCManager.cpp.o: Core/CMakeFiles/Core.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daq/DAQ-ZERO/DAQ/CDAQ/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object Core/CMakeFiles/Core.dir/Source/DCManager.cpp.o"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Core/CMakeFiles/Core.dir/Source/DCManager.cpp.o -MF CMakeFiles/Core.dir/Source/DCManager.cpp.o.d -o CMakeFiles/Core.dir/Source/DCManager.cpp.o -c /home/daq/DAQ-ZERO/DAQ/CDAQ/Core/Source/DCManager.cpp

Core/CMakeFiles/Core.dir/Source/DCManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Core.dir/Source/DCManager.cpp.i"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daq/DAQ-ZERO/DAQ/CDAQ/Core/Source/DCManager.cpp > CMakeFiles/Core.dir/Source/DCManager.cpp.i

Core/CMakeFiles/Core.dir/Source/DCManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Core.dir/Source/DCManager.cpp.s"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daq/DAQ-ZERO/DAQ/CDAQ/Core/Source/DCManager.cpp -o CMakeFiles/Core.dir/Source/DCManager.cpp.s

# Object files for target Core
Core_OBJECTS = \
"CMakeFiles/Core.dir/Source/VMEManager.cpp.o" \
"CMakeFiles/Core.dir/Source/ADCManager.cpp.o" \
"CMakeFiles/Core.dir/Source/ADCManager1730.cpp.o" \
"CMakeFiles/Core.dir/Source/ScopeManager.cpp.o" \
"CMakeFiles/Core.dir/Source/StorageManager.cpp.o" \
"CMakeFiles/Core.dir/Source/SlowcontrolManager.cpp.o" \
"CMakeFiles/Core.dir/Source/ADCManager1720.cpp.o" \
"CMakeFiles/Core.dir/Source/ADCManager1724.cpp.o" \
"CMakeFiles/Core.dir/Source/DCManager.cpp.o"

# External object files for target Core
Core_EXTERNAL_OBJECTS =

lib/libCore.a: Core/CMakeFiles/Core.dir/Source/VMEManager.cpp.o
lib/libCore.a: Core/CMakeFiles/Core.dir/Source/ADCManager.cpp.o
lib/libCore.a: Core/CMakeFiles/Core.dir/Source/ADCManager1730.cpp.o
lib/libCore.a: Core/CMakeFiles/Core.dir/Source/ScopeManager.cpp.o
lib/libCore.a: Core/CMakeFiles/Core.dir/Source/StorageManager.cpp.o
lib/libCore.a: Core/CMakeFiles/Core.dir/Source/SlowcontrolManager.cpp.o
lib/libCore.a: Core/CMakeFiles/Core.dir/Source/ADCManager1720.cpp.o
lib/libCore.a: Core/CMakeFiles/Core.dir/Source/ADCManager1724.cpp.o
lib/libCore.a: Core/CMakeFiles/Core.dir/Source/DCManager.cpp.o
lib/libCore.a: Core/CMakeFiles/Core.dir/build.make
lib/libCore.a: Core/CMakeFiles/Core.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/daq/DAQ-ZERO/DAQ/CDAQ/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX static library ../lib/libCore.a"
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core && $(CMAKE_COMMAND) -P CMakeFiles/Core.dir/cmake_clean_target.cmake
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Core.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Core/CMakeFiles/Core.dir/build: lib/libCore.a
.PHONY : Core/CMakeFiles/Core.dir/build

Core/CMakeFiles/Core.dir/clean:
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core && $(CMAKE_COMMAND) -P CMakeFiles/Core.dir/cmake_clean.cmake
.PHONY : Core/CMakeFiles/Core.dir/clean

Core/CMakeFiles/Core.dir/depend:
	cd /home/daq/DAQ-ZERO/DAQ/CDAQ/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/daq/DAQ-ZERO/DAQ/CDAQ /home/daq/DAQ-ZERO/DAQ/CDAQ/Core /home/daq/DAQ-ZERO/DAQ/CDAQ/build /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core /home/daq/DAQ-ZERO/DAQ/CDAQ/build/Core/CMakeFiles/Core.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Core/CMakeFiles/Core.dir/depend

