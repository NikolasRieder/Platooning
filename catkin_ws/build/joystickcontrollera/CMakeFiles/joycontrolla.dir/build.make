# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/ubuntu/catkin_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/catkin_ws/build

# Include any dependencies generated for this target.
include joystickcontrollera/CMakeFiles/joycontrolla.dir/depend.make

# Include the progress variables for this target.
include joystickcontrollera/CMakeFiles/joycontrolla.dir/progress.make

# Include the compile flags for this target's objects.
include joystickcontrollera/CMakeFiles/joycontrolla.dir/flags.make

joystickcontrollera/CMakeFiles/joycontrolla.dir/src/joycontrolla.cpp.o: joystickcontrollera/CMakeFiles/joycontrolla.dir/flags.make
joystickcontrollera/CMakeFiles/joycontrolla.dir/src/joycontrolla.cpp.o: /home/ubuntu/catkin_ws/src/joystickcontrollera/src/joycontrolla.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object joystickcontrollera/CMakeFiles/joycontrolla.dir/src/joycontrolla.cpp.o"
	cd /home/ubuntu/catkin_ws/build/joystickcontrollera && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/joycontrolla.dir/src/joycontrolla.cpp.o -c /home/ubuntu/catkin_ws/src/joystickcontrollera/src/joycontrolla.cpp

joystickcontrollera/CMakeFiles/joycontrolla.dir/src/joycontrolla.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/joycontrolla.dir/src/joycontrolla.cpp.i"
	cd /home/ubuntu/catkin_ws/build/joystickcontrollera && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/catkin_ws/src/joystickcontrollera/src/joycontrolla.cpp > CMakeFiles/joycontrolla.dir/src/joycontrolla.cpp.i

joystickcontrollera/CMakeFiles/joycontrolla.dir/src/joycontrolla.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/joycontrolla.dir/src/joycontrolla.cpp.s"
	cd /home/ubuntu/catkin_ws/build/joystickcontrollera && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/catkin_ws/src/joystickcontrollera/src/joycontrolla.cpp -o CMakeFiles/joycontrolla.dir/src/joycontrolla.cpp.s

joystickcontrollera/CMakeFiles/joycontrolla.dir/src/joycontrolla.cpp.o.requires:

.PHONY : joystickcontrollera/CMakeFiles/joycontrolla.dir/src/joycontrolla.cpp.o.requires

joystickcontrollera/CMakeFiles/joycontrolla.dir/src/joycontrolla.cpp.o.provides: joystickcontrollera/CMakeFiles/joycontrolla.dir/src/joycontrolla.cpp.o.requires
	$(MAKE) -f joystickcontrollera/CMakeFiles/joycontrolla.dir/build.make joystickcontrollera/CMakeFiles/joycontrolla.dir/src/joycontrolla.cpp.o.provides.build
.PHONY : joystickcontrollera/CMakeFiles/joycontrolla.dir/src/joycontrolla.cpp.o.provides

joystickcontrollera/CMakeFiles/joycontrolla.dir/src/joycontrolla.cpp.o.provides.build: joystickcontrollera/CMakeFiles/joycontrolla.dir/src/joycontrolla.cpp.o


# Object files for target joycontrolla
joycontrolla_OBJECTS = \
"CMakeFiles/joycontrolla.dir/src/joycontrolla.cpp.o"

# External object files for target joycontrolla
joycontrolla_EXTERNAL_OBJECTS =

/home/ubuntu/catkin_ws/devel/lib/joystickcontrollera/joycontrolla: joystickcontrollera/CMakeFiles/joycontrolla.dir/src/joycontrolla.cpp.o
/home/ubuntu/catkin_ws/devel/lib/joystickcontrollera/joycontrolla: joystickcontrollera/CMakeFiles/joycontrolla.dir/build.make
/home/ubuntu/catkin_ws/devel/lib/joystickcontrollera/joycontrolla: /opt/ros/kinetic/lib/libroscpp.so
/home/ubuntu/catkin_ws/devel/lib/joystickcontrollera/joycontrolla: /usr/lib/arm-linux-gnueabihf/libboost_filesystem.so
/home/ubuntu/catkin_ws/devel/lib/joystickcontrollera/joycontrolla: /usr/lib/arm-linux-gnueabihf/libboost_signals.so
/home/ubuntu/catkin_ws/devel/lib/joystickcontrollera/joycontrolla: /opt/ros/kinetic/lib/librosconsole.so
/home/ubuntu/catkin_ws/devel/lib/joystickcontrollera/joycontrolla: /opt/ros/kinetic/lib/librosconsole_log4cxx.so
/home/ubuntu/catkin_ws/devel/lib/joystickcontrollera/joycontrolla: /opt/ros/kinetic/lib/librosconsole_backend_interface.so
/home/ubuntu/catkin_ws/devel/lib/joystickcontrollera/joycontrolla: /usr/lib/arm-linux-gnueabihf/liblog4cxx.so
/home/ubuntu/catkin_ws/devel/lib/joystickcontrollera/joycontrolla: /usr/lib/arm-linux-gnueabihf/libboost_regex.so
/home/ubuntu/catkin_ws/devel/lib/joystickcontrollera/joycontrolla: /opt/ros/kinetic/lib/libxmlrpcpp.so
/home/ubuntu/catkin_ws/devel/lib/joystickcontrollera/joycontrolla: /opt/ros/kinetic/lib/libroscpp_serialization.so
/home/ubuntu/catkin_ws/devel/lib/joystickcontrollera/joycontrolla: /opt/ros/kinetic/lib/librostime.so
/home/ubuntu/catkin_ws/devel/lib/joystickcontrollera/joycontrolla: /opt/ros/kinetic/lib/libcpp_common.so
/home/ubuntu/catkin_ws/devel/lib/joystickcontrollera/joycontrolla: /usr/lib/arm-linux-gnueabihf/libboost_system.so
/home/ubuntu/catkin_ws/devel/lib/joystickcontrollera/joycontrolla: /usr/lib/arm-linux-gnueabihf/libboost_thread.so
/home/ubuntu/catkin_ws/devel/lib/joystickcontrollera/joycontrolla: /usr/lib/arm-linux-gnueabihf/libboost_chrono.so
/home/ubuntu/catkin_ws/devel/lib/joystickcontrollera/joycontrolla: /usr/lib/arm-linux-gnueabihf/libboost_date_time.so
/home/ubuntu/catkin_ws/devel/lib/joystickcontrollera/joycontrolla: /usr/lib/arm-linux-gnueabihf/libboost_atomic.so
/home/ubuntu/catkin_ws/devel/lib/joystickcontrollera/joycontrolla: /usr/lib/arm-linux-gnueabihf/libpthread.so
/home/ubuntu/catkin_ws/devel/lib/joystickcontrollera/joycontrolla: /usr/lib/arm-linux-gnueabihf/libconsole_bridge.so
/home/ubuntu/catkin_ws/devel/lib/joystickcontrollera/joycontrolla: joystickcontrollera/CMakeFiles/joycontrolla.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/ubuntu/catkin_ws/devel/lib/joystickcontrollera/joycontrolla"
	cd /home/ubuntu/catkin_ws/build/joystickcontrollera && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/joycontrolla.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
joystickcontrollera/CMakeFiles/joycontrolla.dir/build: /home/ubuntu/catkin_ws/devel/lib/joystickcontrollera/joycontrolla

.PHONY : joystickcontrollera/CMakeFiles/joycontrolla.dir/build

joystickcontrollera/CMakeFiles/joycontrolla.dir/requires: joystickcontrollera/CMakeFiles/joycontrolla.dir/src/joycontrolla.cpp.o.requires

.PHONY : joystickcontrollera/CMakeFiles/joycontrolla.dir/requires

joystickcontrollera/CMakeFiles/joycontrolla.dir/clean:
	cd /home/ubuntu/catkin_ws/build/joystickcontrollera && $(CMAKE_COMMAND) -P CMakeFiles/joycontrolla.dir/cmake_clean.cmake
.PHONY : joystickcontrollera/CMakeFiles/joycontrolla.dir/clean

joystickcontrollera/CMakeFiles/joycontrolla.dir/depend:
	cd /home/ubuntu/catkin_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/catkin_ws/src /home/ubuntu/catkin_ws/src/joystickcontrollera /home/ubuntu/catkin_ws/build /home/ubuntu/catkin_ws/build/joystickcontrollera /home/ubuntu/catkin_ws/build/joystickcontrollera/CMakeFiles/joycontrolla.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : joystickcontrollera/CMakeFiles/joycontrolla.dir/depend

