# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.2.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Owner\Desktop\GRAFIKA-PROJEKT\Grafika\ppgso

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Owner\Desktop\GRAFIKA-PROJEKT\Grafika\ppgso\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/task4_bezier.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/task4_bezier.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/task4_bezier.dir/flags.make

CMakeFiles/task4_bezier.dir/src/task4_bezier/task4_bezier.cpp.obj: CMakeFiles/task4_bezier.dir/flags.make
CMakeFiles/task4_bezier.dir/src/task4_bezier/task4_bezier.cpp.obj: CMakeFiles/task4_bezier.dir/includes_CXX.rsp
CMakeFiles/task4_bezier.dir/src/task4_bezier/task4_bezier.cpp.obj: ../src/task4_bezier/task4_bezier.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Owner\Desktop\GRAFIKA-PROJEKT\Grafika\ppgso\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/task4_bezier.dir/src/task4_bezier/task4_bezier.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\task4_bezier.dir\src\task4_bezier\task4_bezier.cpp.obj -c C:\Users\Owner\Desktop\GRAFIKA-PROJEKT\Grafika\ppgso\src\task4_bezier\task4_bezier.cpp

CMakeFiles/task4_bezier.dir/src/task4_bezier/task4_bezier.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/task4_bezier.dir/src/task4_bezier/task4_bezier.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Owner\Desktop\GRAFIKA-PROJEKT\Grafika\ppgso\src\task4_bezier\task4_bezier.cpp > CMakeFiles\task4_bezier.dir\src\task4_bezier\task4_bezier.cpp.i

CMakeFiles/task4_bezier.dir/src/task4_bezier/task4_bezier.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/task4_bezier.dir/src/task4_bezier/task4_bezier.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Owner\Desktop\GRAFIKA-PROJEKT\Grafika\ppgso\src\task4_bezier\task4_bezier.cpp -o CMakeFiles\task4_bezier.dir\src\task4_bezier\task4_bezier.cpp.s

# Object files for target task4_bezier
task4_bezier_OBJECTS = \
"CMakeFiles/task4_bezier.dir/src/task4_bezier/task4_bezier.cpp.obj"

# External object files for target task4_bezier
task4_bezier_EXTERNAL_OBJECTS =

task4_bezier.exe: CMakeFiles/task4_bezier.dir/src/task4_bezier/task4_bezier.cpp.obj
task4_bezier.exe: CMakeFiles/task4_bezier.dir/build.make
task4_bezier.exe: libppgso.a
task4_bezier.exe: libshaders.a
task4_bezier.exe: ../dependencies/lib/mingw/libglfw3.a
task4_bezier.exe: ../dependencies/lib/mingw/libglew32.a
task4_bezier.exe: CMakeFiles/task4_bezier.dir/linklibs.rsp
task4_bezier.exe: CMakeFiles/task4_bezier.dir/objects1.rsp
task4_bezier.exe: CMakeFiles/task4_bezier.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Owner\Desktop\GRAFIKA-PROJEKT\Grafika\ppgso\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable task4_bezier.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\task4_bezier.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/task4_bezier.dir/build: task4_bezier.exe

.PHONY : CMakeFiles/task4_bezier.dir/build

CMakeFiles/task4_bezier.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\task4_bezier.dir\cmake_clean.cmake
.PHONY : CMakeFiles/task4_bezier.dir/clean

CMakeFiles/task4_bezier.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Owner\Desktop\GRAFIKA-PROJEKT\Grafika\ppgso C:\Users\Owner\Desktop\GRAFIKA-PROJEKT\Grafika\ppgso C:\Users\Owner\Desktop\GRAFIKA-PROJEKT\Grafika\ppgso\cmake-build-debug C:\Users\Owner\Desktop\GRAFIKA-PROJEKT\Grafika\ppgso\cmake-build-debug C:\Users\Owner\Desktop\GRAFIKA-PROJEKT\Grafika\ppgso\cmake-build-debug\CMakeFiles\task4_bezier.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/task4_bezier.dir/depend
