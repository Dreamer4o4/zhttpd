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
CMAKE_SOURCE_DIR = /home/zh/Downloads/zhttpd

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zh/Downloads/zhttpd/build

# Include any dependencies generated for this target.
include src/CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/main.dir/flags.make

src/CMakeFiles/main.dir/test/main.cpp.o: src/CMakeFiles/main.dir/flags.make
src/CMakeFiles/main.dir/test/main.cpp.o: ../src/test/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zh/Downloads/zhttpd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/main.dir/test/main.cpp.o"
	cd /home/zh/Downloads/zhttpd/build/src && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/test/main.cpp.o -c /home/zh/Downloads/zhttpd/src/test/main.cpp

src/CMakeFiles/main.dir/test/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/test/main.cpp.i"
	cd /home/zh/Downloads/zhttpd/build/src && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zh/Downloads/zhttpd/src/test/main.cpp > CMakeFiles/main.dir/test/main.cpp.i

src/CMakeFiles/main.dir/test/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/test/main.cpp.s"
	cd /home/zh/Downloads/zhttpd/build/src && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zh/Downloads/zhttpd/src/test/main.cpp -o CMakeFiles/main.dir/test/main.cpp.s

src/CMakeFiles/main.dir/base/Acceptor.cpp.o: src/CMakeFiles/main.dir/flags.make
src/CMakeFiles/main.dir/base/Acceptor.cpp.o: ../src/base/Acceptor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zh/Downloads/zhttpd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/main.dir/base/Acceptor.cpp.o"
	cd /home/zh/Downloads/zhttpd/build/src && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/base/Acceptor.cpp.o -c /home/zh/Downloads/zhttpd/src/base/Acceptor.cpp

src/CMakeFiles/main.dir/base/Acceptor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/base/Acceptor.cpp.i"
	cd /home/zh/Downloads/zhttpd/build/src && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zh/Downloads/zhttpd/src/base/Acceptor.cpp > CMakeFiles/main.dir/base/Acceptor.cpp.i

src/CMakeFiles/main.dir/base/Acceptor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/base/Acceptor.cpp.s"
	cd /home/zh/Downloads/zhttpd/build/src && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zh/Downloads/zhttpd/src/base/Acceptor.cpp -o CMakeFiles/main.dir/base/Acceptor.cpp.s

src/CMakeFiles/main.dir/base/Channel.cpp.o: src/CMakeFiles/main.dir/flags.make
src/CMakeFiles/main.dir/base/Channel.cpp.o: ../src/base/Channel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zh/Downloads/zhttpd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/main.dir/base/Channel.cpp.o"
	cd /home/zh/Downloads/zhttpd/build/src && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/base/Channel.cpp.o -c /home/zh/Downloads/zhttpd/src/base/Channel.cpp

src/CMakeFiles/main.dir/base/Channel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/base/Channel.cpp.i"
	cd /home/zh/Downloads/zhttpd/build/src && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zh/Downloads/zhttpd/src/base/Channel.cpp > CMakeFiles/main.dir/base/Channel.cpp.i

src/CMakeFiles/main.dir/base/Channel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/base/Channel.cpp.s"
	cd /home/zh/Downloads/zhttpd/build/src && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zh/Downloads/zhttpd/src/base/Channel.cpp -o CMakeFiles/main.dir/base/Channel.cpp.s

src/CMakeFiles/main.dir/base/Epoll.cpp.o: src/CMakeFiles/main.dir/flags.make
src/CMakeFiles/main.dir/base/Epoll.cpp.o: ../src/base/Epoll.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zh/Downloads/zhttpd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/main.dir/base/Epoll.cpp.o"
	cd /home/zh/Downloads/zhttpd/build/src && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/base/Epoll.cpp.o -c /home/zh/Downloads/zhttpd/src/base/Epoll.cpp

src/CMakeFiles/main.dir/base/Epoll.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/base/Epoll.cpp.i"
	cd /home/zh/Downloads/zhttpd/build/src && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zh/Downloads/zhttpd/src/base/Epoll.cpp > CMakeFiles/main.dir/base/Epoll.cpp.i

src/CMakeFiles/main.dir/base/Epoll.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/base/Epoll.cpp.s"
	cd /home/zh/Downloads/zhttpd/build/src && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zh/Downloads/zhttpd/src/base/Epoll.cpp -o CMakeFiles/main.dir/base/Epoll.cpp.s

src/CMakeFiles/main.dir/base/EventLoop.cpp.o: src/CMakeFiles/main.dir/flags.make
src/CMakeFiles/main.dir/base/EventLoop.cpp.o: ../src/base/EventLoop.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zh/Downloads/zhttpd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/main.dir/base/EventLoop.cpp.o"
	cd /home/zh/Downloads/zhttpd/build/src && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/base/EventLoop.cpp.o -c /home/zh/Downloads/zhttpd/src/base/EventLoop.cpp

src/CMakeFiles/main.dir/base/EventLoop.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/base/EventLoop.cpp.i"
	cd /home/zh/Downloads/zhttpd/build/src && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zh/Downloads/zhttpd/src/base/EventLoop.cpp > CMakeFiles/main.dir/base/EventLoop.cpp.i

src/CMakeFiles/main.dir/base/EventLoop.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/base/EventLoop.cpp.s"
	cd /home/zh/Downloads/zhttpd/build/src && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zh/Downloads/zhttpd/src/base/EventLoop.cpp -o CMakeFiles/main.dir/base/EventLoop.cpp.s

src/CMakeFiles/main.dir/base/Log.cpp.o: src/CMakeFiles/main.dir/flags.make
src/CMakeFiles/main.dir/base/Log.cpp.o: ../src/base/Log.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zh/Downloads/zhttpd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/CMakeFiles/main.dir/base/Log.cpp.o"
	cd /home/zh/Downloads/zhttpd/build/src && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/base/Log.cpp.o -c /home/zh/Downloads/zhttpd/src/base/Log.cpp

src/CMakeFiles/main.dir/base/Log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/base/Log.cpp.i"
	cd /home/zh/Downloads/zhttpd/build/src && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zh/Downloads/zhttpd/src/base/Log.cpp > CMakeFiles/main.dir/base/Log.cpp.i

src/CMakeFiles/main.dir/base/Log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/base/Log.cpp.s"
	cd /home/zh/Downloads/zhttpd/build/src && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zh/Downloads/zhttpd/src/base/Log.cpp -o CMakeFiles/main.dir/base/Log.cpp.s

src/CMakeFiles/main.dir/base/RequestAndResponse.cpp.o: src/CMakeFiles/main.dir/flags.make
src/CMakeFiles/main.dir/base/RequestAndResponse.cpp.o: ../src/base/RequestAndResponse.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zh/Downloads/zhttpd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/CMakeFiles/main.dir/base/RequestAndResponse.cpp.o"
	cd /home/zh/Downloads/zhttpd/build/src && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/base/RequestAndResponse.cpp.o -c /home/zh/Downloads/zhttpd/src/base/RequestAndResponse.cpp

src/CMakeFiles/main.dir/base/RequestAndResponse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/base/RequestAndResponse.cpp.i"
	cd /home/zh/Downloads/zhttpd/build/src && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zh/Downloads/zhttpd/src/base/RequestAndResponse.cpp > CMakeFiles/main.dir/base/RequestAndResponse.cpp.i

src/CMakeFiles/main.dir/base/RequestAndResponse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/base/RequestAndResponse.cpp.s"
	cd /home/zh/Downloads/zhttpd/build/src && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zh/Downloads/zhttpd/src/base/RequestAndResponse.cpp -o CMakeFiles/main.dir/base/RequestAndResponse.cpp.s

src/CMakeFiles/main.dir/base/Socket.cpp.o: src/CMakeFiles/main.dir/flags.make
src/CMakeFiles/main.dir/base/Socket.cpp.o: ../src/base/Socket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zh/Downloads/zhttpd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/CMakeFiles/main.dir/base/Socket.cpp.o"
	cd /home/zh/Downloads/zhttpd/build/src && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/base/Socket.cpp.o -c /home/zh/Downloads/zhttpd/src/base/Socket.cpp

src/CMakeFiles/main.dir/base/Socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/base/Socket.cpp.i"
	cd /home/zh/Downloads/zhttpd/build/src && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zh/Downloads/zhttpd/src/base/Socket.cpp > CMakeFiles/main.dir/base/Socket.cpp.i

src/CMakeFiles/main.dir/base/Socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/base/Socket.cpp.s"
	cd /home/zh/Downloads/zhttpd/build/src && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zh/Downloads/zhttpd/src/base/Socket.cpp -o CMakeFiles/main.dir/base/Socket.cpp.s

src/CMakeFiles/main.dir/base/TcpServer.cpp.o: src/CMakeFiles/main.dir/flags.make
src/CMakeFiles/main.dir/base/TcpServer.cpp.o: ../src/base/TcpServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zh/Downloads/zhttpd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object src/CMakeFiles/main.dir/base/TcpServer.cpp.o"
	cd /home/zh/Downloads/zhttpd/build/src && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/base/TcpServer.cpp.o -c /home/zh/Downloads/zhttpd/src/base/TcpServer.cpp

src/CMakeFiles/main.dir/base/TcpServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/base/TcpServer.cpp.i"
	cd /home/zh/Downloads/zhttpd/build/src && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zh/Downloads/zhttpd/src/base/TcpServer.cpp > CMakeFiles/main.dir/base/TcpServer.cpp.i

src/CMakeFiles/main.dir/base/TcpServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/base/TcpServer.cpp.s"
	cd /home/zh/Downloads/zhttpd/build/src && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zh/Downloads/zhttpd/src/base/TcpServer.cpp -o CMakeFiles/main.dir/base/TcpServer.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/test/main.cpp.o" \
"CMakeFiles/main.dir/base/Acceptor.cpp.o" \
"CMakeFiles/main.dir/base/Channel.cpp.o" \
"CMakeFiles/main.dir/base/Epoll.cpp.o" \
"CMakeFiles/main.dir/base/EventLoop.cpp.o" \
"CMakeFiles/main.dir/base/Log.cpp.o" \
"CMakeFiles/main.dir/base/RequestAndResponse.cpp.o" \
"CMakeFiles/main.dir/base/Socket.cpp.o" \
"CMakeFiles/main.dir/base/TcpServer.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

../main: src/CMakeFiles/main.dir/test/main.cpp.o
../main: src/CMakeFiles/main.dir/base/Acceptor.cpp.o
../main: src/CMakeFiles/main.dir/base/Channel.cpp.o
../main: src/CMakeFiles/main.dir/base/Epoll.cpp.o
../main: src/CMakeFiles/main.dir/base/EventLoop.cpp.o
../main: src/CMakeFiles/main.dir/base/Log.cpp.o
../main: src/CMakeFiles/main.dir/base/RequestAndResponse.cpp.o
../main: src/CMakeFiles/main.dir/base/Socket.cpp.o
../main: src/CMakeFiles/main.dir/base/TcpServer.cpp.o
../main: src/CMakeFiles/main.dir/build.make
../main: src/CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zh/Downloads/zhttpd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable ../../main"
	cd /home/zh/Downloads/zhttpd/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/main.dir/build: ../main

.PHONY : src/CMakeFiles/main.dir/build

src/CMakeFiles/main.dir/clean:
	cd /home/zh/Downloads/zhttpd/build/src && $(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/main.dir/clean

src/CMakeFiles/main.dir/depend:
	cd /home/zh/Downloads/zhttpd/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zh/Downloads/zhttpd /home/zh/Downloads/zhttpd/src /home/zh/Downloads/zhttpd/build /home/zh/Downloads/zhttpd/build/src /home/zh/Downloads/zhttpd/build/src/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/main.dir/depend

