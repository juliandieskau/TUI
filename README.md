# ftxui-starter

CMakeList and main() method based on ftxui-starter:  
Minimal starter project using the [FTXUI library](https://github.com/ArthurSonzogni/ftxui)

# rosbridge

[Rosbridge Client](https://github.com/antoniocoratelli/rosbridge_client_cpp/tree/v2018/) rosbridge_client_cpp as ros-bridge library. (Currently error trying to include in CMakeLists.txt)

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
~~~bash
[variant] Loaded new set of variants
[kit] Successfully loaded 2 kits from /home/vscode/.local/share/CMakeTools/cmake-tools-kits.json
[proc] Executing command: /usr/bin/cmake --version
[proc] Executing command: /usr/bin/gcc -v
[main] Configuring project: tui 
[proc] Executing command: /usr/bin/cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++ -S/workspaces/tui -B/workspaces/tui/build -G Ninja
[cmake] Not searching for unused variables given on the command line.
[cmake] -- The CXX compiler identification is GNU 10.2.1
[cmake] -- Detecting CXX compiler ABI info
[cmake] -- Detecting CXX compiler ABI info - done
[cmake] -- Check for working CXX compiler: /usr/bin/g++ - skipped
[cmake] -- Detecting CXX compile features
[cmake] -- Detecting CXX compile features - done
[cmake] -- Looking for C++ include pthread.h
[cmake] -- Looking for C++ include pthread.h - found
[cmake] -- Performing Test CMAKE_HAVE_LIBC_PTHREAD
[cmake] -- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Failed
[cmake] -- Looking for pthread_create in pthreads
[cmake] -- Looking for pthread_create in pthreads - not found
[cmake] -- Looking for pthread_create in pthread
[cmake] -- Looking for pthread_create in pthread - found
[cmake] -- Found Threads: TRUE  
[cmake] -- clang-tidy not found.
[cmake] -- ftxui_set_options screen
[cmake] -- ftxui_set_options dom
[cmake] -- ftxui_set_options component
[cmake] -- Could NOT find Doxygen (missing: DOXYGEN_EXECUTABLE) 
[cmake] Doxygen need to be installed to generate the doxygen documentation
[cmake] -- The C compiler identification is GNU 10.2.1
[cmake] -- Detecting C compiler ABI info
[cmake] -- Detecting C compiler ABI info - done
[cmake] -- Check for working C compiler: /usr/bin/gcc - skipped
[cmake] -- Detecting C compile features
[cmake] -- Detecting C compile features - done
[cmake] CMake Error at build/_deps/rosbridge_client_cpp-src/CMakeLists.txt:40 (add_library):
[cmake]   add_library cannot create target "rosbridge_client_cpp" because another
[cmake]   target with the same name already exists.  The existing target is a shared
[cmake]   library created in source directory
[cmake]   "/workspaces/tui/build/_deps/rosbridge_client_cpp-src".  See documentation
[cmake]   for policy CMP0002 for more details.
[cmake] 
[cmake] 
[cmake] CMake Error at build/_deps/rosbridge_client_cpp-src/CMakeLists.txt:43 (target_link_libraries):
[cmake]   Attempt to add link library "pthread" to target "rosbridge_client_cpp"
[cmake]   which is not built in this directory.
[cmake] 
[cmake]   This is allowed only when policy CMP0079 is set to NEW.
[cmake] 
[cmake] 
[cmake] CMake Error at build/_deps/rosbridge_client_cpp-src/CMakeLists.txt:51 (add_executable):
[cmake]   add_executable cannot create target "rosbridge_client_cpp_examples" because
[cmake]   another target with the same name already exists.  The existing target is
[cmake]   an executable created in source directory
[cmake]   "/workspaces/tui/build/_deps/rosbridge_client_cpp-src".  See documentation
[cmake]   for policy CMP0002 for more details.
[cmake] 
[cmake] 
[cmake] CMake Error at build/_deps/rosbridge_client_cpp-src/CMakeLists.txt:54 (target_link_libraries):
[cmake]   Attempt to add link library "rosbridge_client_cpp" to target
[cmake]   "rosbridge_client_cpp_examples" which is not built in this directory.
[cmake] 
[cmake]   This is allowed only when policy CMP0079 is set to NEW.
[cmake] 
[cmake] 
[cmake] CMake Error at build/_deps/rosbridge_client_cpp-src/CMakeLists.txt:67 (add_executable):
[cmake]   add_executable cannot create target "rosbridge_client_cpp_unit_tests"
[cmake]   because another target with the same name already exists.  The existing
[cmake]   target is an executable created in source directory
[cmake]   "/workspaces/tui/build/_deps/rosbridge_client_cpp-src".  See documentation
[cmake]   for policy CMP0002 for more details.
[cmake] 
[cmake] 
[cmake] CMake Error at build/_deps/rosbridge_client_cpp-src/CMakeLists.txt:72 (target_link_libraries):
[cmake]   Attempt to add link library "rosbridge_client_cpp" to target
[cmake]   "rosbridge_client_cpp_unit_tests" which is not built in this directory.
[cmake] 
[cmake]   This is allowed only when policy CMP0079 is set to NEW.
[cmake] 
[cmake] 
[cmake] CMake Error at build/_deps/rosbridge_client_cpp-src/CMakeLists.txt:96 (add_custom_target):
[cmake]   add_custom_target cannot create target "rosbridge_client_cpp_files" because
[cmake]   another target with the same name already exists.  The existing target is a
[cmake]   custom target created in source directory
[cmake]   "/workspaces/tui/build/_deps/rosbridge_client_cpp-src".  See documentation
[cmake]   for policy CMP0002 for more details.
[cmake] 
[cmake
[cmake] -- Configuring incomplete, errors occurred!
[cmake] See also "/workspaces/tui/build/CMakeFiles/CMakeOutput.log".
[cmake] See also "/workspaces/tui/build/CMakeFiles/CMakeError.log".
[proc] The command: /usr/bin/cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++ -S/workspaces/tui -B/workspaces/tui/build -G Ninja exited with code: 1
~~~