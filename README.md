# ftxui-starter

CMakeList and main() method based on ftxui-starter:  
Minimal starter project using the [FTXUI library](https://github.com/ArthurSonzogni/ftxui)

# VSCode Dev Container:

install [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) extension
press F1 ">Dev Containers: Open Folder in Container"
and select root folder (that contains .devcontainer)


# Build instructions:

~~~bash
mkdir build
cd build
cmake ..
make -j
cd ../target
./ftxui-starter
~~~

if it fails on 'Could NOT find Boost': 
[install Boost](https://stackoverflow.com/questions/19029175/installing-boost-in-debian-for-codeblocks)

# Ver&auml;nderungen zum Entwurf:

# ftxui-starter

CMakeList and main() method based on ftxui-starter:  
Minimal starter project using the [FTXUI library](https://github.com/ArthurSonzogni/ftxui)

# rosbridge

https://github.com/antoniocoratelli/rosbridge_client_cpp/tree/v2018/ rosbridge_client_cpp as ros-bridge library. (Currently error trying to include in CMakeLists.txt)

# Dev Environment

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

# Ver&auml;nderungen zum Entwurf

/ none so far
