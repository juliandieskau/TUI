# ftxui-starter

CMakeList and main() method based on ftxui-starter:  
Minimal starter project using the [FTXUI library](https://github.com/ArthurSonzogni/ftxui)

# rosbridge

https://github.com/antoniocoratelli/rosbridge_client_cpp/tree/v2018/ rosbridge_client_cpp as ros-bridge library. (Currently error trying to include in CMakeLists.txt)

# VSCode Dev Container:

install [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) extension 
press F1 ">Dev Containers: Open Folder in Container" 
and select root folder (that contains .devcontainer)


# Dev Environment (alternatively)

start Docker Desktop / Docker Engine service
open tui project directory in Visual Studio Code
accept pop-up from VSC to run project in Dev Container: C++

# Build instructions

~~~bash
mkdir build
cd build
cmake ..
~~~

Since it fails in this step, execution instruction not included^.
see CMakeFiles/ for error log

# Terminal output for cmake

[variant] Loaded new set of variants <br>
[kit] Successfully loaded 2 kits from /home/vscode/.local/share/CMakeTools/cmake-tools-kits.json<br>
[proc] Executing command: /usr/bin/cmake --version<br>
[proc] Executing command: /usr/bin/gcc -v<br>
[main] Configuring project: tui <br>
[proc] Executing command: /usr/bin/cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++ -S/workspaces/tui -B/workspaces/tui/build -G Ninja<br>
[cmake] Not searching for unused variables given on the command line.<br>
[cmake] -- The CXX compiler identification is GNU 10.2.1<br>
[cmake] -- Detecting CXX compiler ABI info<br>
[cmake] -- Detecting CXX compiler ABI info - done<br>
[cmake] -- Check for working CXX compiler: /usr/bin/g++ - skipped<br>
[cmake] -- Detecting CXX compile features<br>
[cmake] -- Detecting CXX compile features - done<br>
[cmake] -- Looking for C++ include pthread.h<br>
[cmake] -- Looking for C++ include pthread.h - found<br>
[cmake] -- Performing Test CMAKE_HAVE_LIBC_PTHREAD<br>
[cmake] -- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Failed<br>
[cmake] -- Looking for pthread_create in pthreads<br>
[cmake] -- Looking for pthread_create in pthreads - not found<br>
[cmake] -- Looking for pthread_create in pthread<br>
[cmake] -- Looking for pthread_create in pthread - found<br>
[cmake] -- Found Threads: TRUE  <br>
[cmake] -- clang-tidy not found.<br>
[cmake] -- ftxui_set_options screen<br>
[cmake] -- ftxui_set_options dom<br>
[cmake] -- ftxui_set_options component<br>
[cmake] -- Could NOT find Doxygen (missing: DOXYGEN_EXECUTABLE) <br>
[cmake] Doxygen need to be installed to generate the doxygen documentation<br>
[cmake] -- The C compiler identification is GNU 10.2.1<br>
[cmake] -- Detecting C compiler ABI info<br>
[cmake] -- Detecting C compiler ABI info - done<br>
[cmake] -- Check for working C compiler: /usr/bin/gcc - skipped<br>
[cmake] -- Detecting C compile features<br>
[cmake] -- Detecting C compile features - done<br>
[cmake] CMake Error at build/_deps/rosbridge_client_cpp-src/CMakeLists.txt:40 (add_library):<br>
[cmake]   add_library cannot create target "rosbridge_client_cpp" because another
[cmake]   target with the same name already exists.  The existing target is a shared
[cmake]   library created in source directory
[cmake]   "/workspaces/tui/build/_deps/rosbridge_client_cpp-src".  See documentation
[cmake]   for policy CMP0002 for more details.<br>
[cmake] 
[cmake] 
[cmake] CMake Error at build/_deps/rosbridge_client_cpp-src/CMakeLists.txt:43 (target_link_libraries):<br>
[cmake]   Attempt to add link library "pthread" to target "rosbridge_client_cpp"
[cmake]   which is not built in this directory.<br>
[cmake] 
[cmake]   This is allowed only when policy CMP0079 is set to NEW.<br>
[cmake] 
[cmake] 
[cmake] CMake Error at build/_deps/rosbridge_client_cpp-src/CMakeLists.txt:51 (add_executable):<br>
[cmake]   add_executable cannot create target "rosbridge_client_cpp_examples" because
[cmake]   another target with the same name already exists.  The existing target is
[cmake]   an executable created in source directory
[cmake]   "/workspaces/tui/build/_deps/rosbridge_client_cpp-src".  See documentation
[cmake]   for policy CMP0002 for more details.<br>
[cmake] 
[cmake] 
[cmake] CMake Error at build/_deps/rosbridge_client_cpp-src/CMakeLists.txt:54 (target_link_libraries):<br>
[cmake]   Attempt to add link library "rosbridge_client_cpp" to target
[cmake]   "rosbridge_client_cpp_examples" which is not built in this directory.<br>
[cmake] 
[cmake]   This is allowed only when policy CMP0079 is set to NEW.<br>
[cmake] 
[cmake] 
[cmake] CMake Error at build/_deps/rosbridge_client_cpp-src/CMakeLists.txt:67 (add_executable):<br>
[cmake]   add_executable cannot create target "rosbridge_client_cpp_unit_tests"
[cmake]   because another target with the same name already exists.  The existing
[cmake]   target is an executable created in source directory
[cmake]   "/workspaces/tui/build/_deps/rosbridge_client_cpp-src".  See documentation
[cmake]   for policy CMP0002 for more details.<br>
[cmake] 
[cmake] 
[cmake] CMake Error at build/_deps/rosbridge_client_cpp-src/CMakeLists.txt:72 (target_link_libraries):<br>
[cmake]   Attempt to add link library "rosbridge_client_cpp" to target
[cmake]   "rosbridge_client_cpp_unit_tests" which is not built in this directory.<br>
[cmake] 
[cmake]   This is allowed only when policy CMP0079 is set to NEW.<br>
[cmake] 
[cmake] 
[cmake] CMake Error at build/_deps/rosbridge_client_cpp-src/CMakeLists.txt:96 (add_custom_target):<br>
[cmake]   add_custom_target cannot create target "rosbridge_client_cpp_files" because
[cmake]   another target with the same name already exists.  The existing target is a
[cmake]   custom target created in source directory
[cmake]   "/workspaces/tui/build/_deps/rosbridge_client_cpp-src".  See documentation
[cmake]   for policy CMP0002 for more details.<br>
[cmake] 
[cmake] <br>
[cmake] -- Configuring incomplete, errors occurred!
[cmake] See also "/workspaces/tui/build/CMakeFiles/CMakeOutput.log".<br>
[cmake] See also "/workspaces/tui/build/CMakeFiles/CMakeError.log".<br>
[proc] The command: /usr/bin/cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++ -S/workspaces/tui -B/workspaces/tui/build -G Ninja exited with code: 1<br>