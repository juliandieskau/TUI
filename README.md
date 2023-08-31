# ECTS TUI
[TOC]

## Setup project

### VSCode Dev Container:
install [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) extension <br>
press F1 ">Dev Containers: Open Folder in Container" <br>
and select root folder (that contains .devcontainer)

### Dev Environment (alternatively)
start Docker Desktop / Docker Engine service <br>
open tui project directory in Visual Studio Code <br>
accept pop-up from VSC to run project in Dev Container: C++

## Build instructions
```bash
mkdir build
cd build
cmake -S ../ -B .
make
```

## Test run project (Ubuntu 20.04)
### setup
Update cmake to the newest version. <br>
Install [ROS Noetic](http://wiki.ros.org/noetic/Installation/Ubuntu) <br>
```bash
apt-get update && apt-get install -y ros-noetic-desktop-full ros-noetic-rosbridge-server ros-noetic-catkin gdb iproute2 wireless-tools neovim 
```

### terminal preparation
For every terminal opened for the Backend, run in directory Backend/
```bash
source devel/setup.bash
source devel/local_setup.bash
```

### launch backend
```bash
git submodule update --recursive --init
```

Build and run the backend with roscore and rosbridge:
```bash
catkin_make && roslaunch ects ects.launch config:=/workspace/ects_config.json
```

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

## Used Libraries

### ftxui-starter
CMakeList and main() method based on ftxui-starter:  
Minimal starter project using the [FTXUI library](https://github.com/ArthurSonzogni/ftxui)

### rosbridge
[Rosbridge Client](https://github.com/antoniocoratelli/rosbridge_client_cpp/tree/v2018/) as ros-bridge library. <br>
Fixed forked version in [GitLab](https://git.scc.kit.edu/pse-robot-monitoring/rosbridge_client_cpp.git)


# TODO
use VSCode Plugin [Todo Tree](https://marketplace.visualstudio.com/items?itemName=Gruntfuggly.todo-tree) for listing them inside the code
## TODO now
- [ ] UNIT TESTS
- [ ] Error Handling

## TODO testing phase
<<<<<<< Updated upstream
- [ ] Documentation for Methods, Classes, Members (-> Entwurf)
=======
- [x] Code Style/ descriptive Names
- [ ] Documentation for Methods, Classes, Members (-> Entwurf)
- [x] nicely looking newlines and data representation
- [ ] farben descriptive grün->rot
>>>>>>> Stashed changes

# settings file
- default backend address and port
- color scheme of the console window
- open/closed plugin windows 
- 
