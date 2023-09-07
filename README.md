# ECTS TUI
[TOC]

## Build instructions
```bash
./build.sh
```

## Run instructions

### open build folder
from TUI directory 
```bash
cd build
```

### start ects-tui with command line arguments
0: ects-tui provides the option to be started without arguments and will default to localhost:9090 <br>
```bash
./ects-tui
```
1: you can specify the ip as the first argument and the port will default to 9090 <br>
```bash
./ects-tui 127.0.0.1
```
2: you can specify both ip and port in that order as command line arguments <br>
```bash
./ects-tui 127.0.0.1 9090
```

## Developement instructions

### VSCode Dev Container:
install [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) extension <br>
press F1 ">Dev Containers: Open Folder in Container" <br>
and select root folder (that contains .devcontainer)

### Dev Environment (alternatively)
start Docker Desktop / Docker Engine service <br>
open tui project directory in Visual Studio Code <br>
accept pop-up from VSC to run project in Dev Container: C++


### Used Libraries

<b>ftxui-starter</b><br>
CMakeList and main() method based on ftxui-starter:  <br>
Minimal starter project using the [FTXUI library](https://github.com/ArthurSonzogni/ftxui)<br>
<br>
<b>rosbridge_client_cpp</b><br>
[Rosbridge Client](https://github.com/antoniocoratelli/rosbridge_client_cpp/tree/v2018/) as ros-bridge library. <br>
Fixed forked version in [GitLab](https://git.scc.kit.edu/pse-robot-monitoring/rosbridge_client_cpp.git)

### How to develop a new plugin
